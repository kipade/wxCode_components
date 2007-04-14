/////////////////////////////////////////////////////////////////////////////
// Name:        thread.cpp
// Purpose:     wxCurlDownloadThread, wxCurlUploadThread
// Author:      Francesco Montorsi
// Created:     2007/04/14
// RCS-ID:      $Id$
// Copyright:   (c) 2007 Francesco Montorsi
// Licence:     wxWidgets licence
/////////////////////////////////////////////////////////////////////////////


// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

// includes
#ifndef WX_PRECOMP
    #include <wx/log.h>
#endif

#include <wx/wfstream.h>
#include <wx/filename.h>

#include "wx/curl/dthread.h"
#include "wx/curl/http.h"
#include "wx/curl/ftp.h"


// ---------------------
// wxCurlBaseThread
// ---------------------

/* static */
wxCurlProtocol wxCurlBaseThread::GetProtocolFromURL(const wxString &url)
{
    // I'm sure this check could be done in a better way...
    if (url.StartsWith(wxT("http:")) || url.StartsWith(wxT("https:")))
        return wxCP_HTTP;
    if (url.StartsWith(wxT("ftp:")) || url.StartsWith(wxT("ftps:")))
        return wxCP_FTP;
    return wxCP_INVALID;
}

/* static */
wxCurlBase *wxCurlBaseThread::CreateHandlerFor(wxCurlProtocol prot)
{
    switch (prot)
    {
        case wxCP_HTTP:
            return new wxCurlHTTP;
        case wxCP_FTP:
            return new wxCurlFTP;

        default:
            return NULL;
    }
}

wxCurlThreadError wxCurlBaseThread::SetURL(const wxString &url)
{
    wxCHECK_MSG(!IsAlive(), wxCTE_NO_RESOURCE, wxT("Cannot use this function after the tranfer has begun"));

    // which protocol is required by given url?
    wxCurlProtocol curr = GetProtocolFromURL(url);
    if (curr == wxCP_INVALID)
        return wxCTE_INVALID_PROTOCOL;

    if (curr != m_protocol)
    {
        m_protocol = curr;

        // we need to (re)create the m_pCurl object
        wxDELETE(m_pCurl);
        m_pCurl = CreateHandlerFor(m_protocol);
    }

    if (!m_pCurl || !m_pCurl->IsOk())
        return wxCTE_INVALID_PROTOCOL;

    // enable event sending (it's the only way the wxCurlDownloadThread user can
    // receive info about the progress of the transfer)
    m_pCurl->SetEvtHandler(GetEvtHandler(), GetId());
    m_pCurl->SetFlags(wxCURL_SEND_PROGRESS_EVENTS | wxCURL_SEND_BEGINEND_EVENTS);

    m_url = url;

    return wxCTE_NO_ERROR;
}

void wxCurlBaseThread::OnExit()
{
    wxLogDebug(wxT("wxCurlBaseThread - exiting"));
}

wxCurlThreadError wxCurlBaseThread::Wait()
{
    // Entry() returns 1 for success, 0 for failure
    bool ret = (bool)(wxThread::Wait() != 0);

    if (m_bAbort)
        return wxCTE_ABORTED;

    return ret ? wxCTE_NO_ERROR : wxCTE_CURL_ERROR;
}



// -----------------------------------
// wxCurlDownloadThreadOutputFilter
// -----------------------------------

size_t wxCurlDownloadThreadOutputFilter::OnSysWrite(const void *buffer, size_t bufsize)
{
    // VERY IMPORTANT: we need to call TestDestroy() on the associated
    //                 thread to make sure it can be paused/stopped (see wxThread docs)

    if (m_thread->TestDestroy())
    {
        // returning a size != bufsize we tell libcurl to stop the tranfer
        // and thus the wxCurlBase::Perform() call done (indirectly) by wxCurlDownloadThread::Entry()
        // will immediately complete and we'll exit the thread.
        // NOTE: we could also call wxThread::Exit() from here... but notifying libcurl
        //       of a "fake error" seems a better solution (allows libcurl to cleanup its internal)
        return (size_t)-1;
    }

    return m_stream->Write(buffer, bufsize).LastWrite();
}

// ---------------------
// wxCurlDownloadThread
// ---------------------

wxCurlThreadError wxCurlDownloadThread::SetOutputStream(wxOutputStream *out)
{
    wxCHECK_MSG(!IsAlive(), wxCTE_NO_RESOURCE, wxT("Cannot use this function after the transfer has begun"));

    if (!out)
    {
        if (!m_output)
        {
            // create a temporary file output stream
            // NOTE: by default we create a wxFileOutputStream and not e.g. a wxMemoryOutputStream
            //       because the downloaded file may be quite large and thus we don't want to
            //       eat lots of RAM. Also, the hard disk should be fast enough for any download.
            m_output.SetStream( new wxFileOutputStream(wxFileName::CreateTempFileName(wxT("download"))) );
            if (!m_output.IsOk())
                return wxCTE_NO_VALID_STREAM;
        }
    }
    else
    {
        m_output.SetStream(out);

        // the user-provided output stream must be valid
        if (!m_output.IsOk())
            return wxCTE_NO_VALID_STREAM;
    }

    return wxCTE_NO_ERROR;
}

wxCurlThreadError wxCurlDownloadThread::Download()
{
    wxCHECK_MSG(!IsAlive(), wxCTE_NO_RESOURCE, wxT("Cannot use this function after the transfer has begun"));

    // create & run this thread
    wxCurlThreadError ret;
    if ((ret=Create(wxCURL_THREAD_STACK_SIZE)) != wxCTE_NO_ERROR)
        return ret;
    if ((ret=Run()) != wxCTE_NO_ERROR)
        return ret;

    return wxCTE_NO_ERROR;
}

wxCurlThreadError wxCurlDownloadThread::Download(const wxString &url, wxOutputStream *out)
{
    wxCurlThreadError ret;

    if ((ret=SetURL(url)) != wxCTE_NO_ERROR)
        return ret;
    if ((ret=SetOutputStream(out)) != wxCTE_NO_ERROR)
        return ret;

    return Download();
}

void *wxCurlDownloadThread::Entry()
{
    if (!m_pCurl || !m_pCurl->IsOk() || !m_output.IsOk())
        return NULL;

    // NOTE: the TestDestroy() function will still be called in this thread
    //       context by the m_output's OnSysWrite function which in turn is
    //       called from libcurl whenever some new data arrives
    wxLogDebug(wxT("wxCurlDownloadThread - downloading from %s"), m_url.c_str());
    switch (m_protocol)
    {
        case wxCP_HTTP:
            return (void*)wx_static_cast(wxCurlHTTP*, m_pCurl)->Get(m_output, m_url);

        case wxCP_FTP:
            return (void*)wx_static_cast(wxCurlHTTP*, m_pCurl)->Get(m_output, m_url);
    }

    return NULL;
}



// -----------------------------------
// wxCurlUploadThreadInputFilter
// -----------------------------------

size_t wxCurlUploadThreadInputFilter::OnSysRead(void *buffer, size_t bufsize)
{
    // VERY IMPORTANT: we need to call TestDestroy() on the associated
    //                 thread to make sure it can be paused/stopped (see wxThread docs)

    if (m_thread->TestDestroy())
    {
        // returning a size != bufsize we tell libcurl to stop the tranfer
        // and thus the wxCurlBase::Perform() call done (indirectly) by wxCurlUploadThread::Entry()
        // will immediately complete and we'll exit the thread.
        // NOTE: we could also call wxThread::Exit() from here... but notifying libcurl
        //       of a "fake error" seems a better solution (allows libcurl to cleanup its internal)
        return (size_t)-1;
    }

    return m_stream->Read(buffer, bufsize).LastRead();
}


// ---------------------
// wxCurlUploadThread
// ---------------------

wxCurlThreadError wxCurlUploadThread::SetInputStream(wxInputStream *in)
{
    wxCHECK_MSG(!IsAlive(), wxCTE_NO_RESOURCE, wxT("Cannot use this function after the transfer has begun"));

    m_input.SetStream(in);

    // the user-provided input stream must be valid
    if (!m_input.IsOk())
        return wxCTE_NO_VALID_STREAM;

    return wxCTE_NO_ERROR;
}

wxCurlThreadError wxCurlUploadThread::Upload()
{
    wxCHECK_MSG(!IsAlive(), wxCTE_NO_RESOURCE, wxT("Cannot use this function after the tranfer has begun"));

    // create & run this thread
    wxCurlThreadError ret;
    if ((ret=Create(wxCURL_THREAD_STACK_SIZE)) != wxCTE_NO_ERROR)
        return ret;
    if ((ret=Run()) != wxCTE_NO_ERROR)
        return ret;

    return wxCTE_NO_ERROR;
}

wxCurlThreadError wxCurlUploadThread::Upload(const wxString &url, wxInputStream *in)
{
    wxCurlThreadError ret;

    if ((ret=SetURL(url)) != wxCTE_NO_ERROR)
        return ret;
    if ((ret=SetInputStream(in)) != wxCTE_NO_ERROR)
        return ret;

    return Upload();
}

void *wxCurlUploadThread::Entry()
{
    if (!m_pCurl || !m_pCurl->IsOk() || !m_input.IsOk())
        return NULL;

    // NOTE: the TestDestroy() function will still be called in this thread
    //       context by the m_output's OnSysWrite function which in turn is
    //       called from libcurl whenever some new data arrives
    wxLogDebug(wxT("wxCurlUploadThread - uploading to %s"), m_url.c_str());
    switch (m_protocol)
    {
        case wxCP_HTTP:
            return (void*)wx_static_cast(wxCurlHTTP*, m_pCurl)->Put(m_input, m_url);

        case wxCP_FTP:
            return (void*)wx_static_cast(wxCurlHTTP*, m_pCurl)->Put(m_input, m_url);
    }

    return NULL;
}
