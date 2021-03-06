/*
 *	wxOptionsDialog.h
 *	wxCURL
 *
 *	Created by Casey O'Donnell on Wed Jul 14 2004.
 *	Copyright (c) 2004 Casey O'Donnell. All rights reserved.
 *
 */

// wxOptionsDialog.h: interface for the wxOptionsDialog class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _WXOPTIONSDIALOG_H__INCLUDED_
#define _WXOPTIONSDIALOG_H__INCLUDED_

#include <wx/dialog.h>
#include <wx/textctrl.h>

class wxOptionsDialog : public wxDialog  
{
public:
	wxOptionsDialog(wxWindow* pParent);
	virtual ~wxOptionsDialog();

	// Event Handlers (These Functions Should NOT be Virtual)
	void OnOptions(wxCommandEvent& event);

protected:
	wxTextCtrl* m_pTextCtrl;
	wxTextCtrl* m_pHostCtrl;

	wxTextCtrl* m_pUserCtrl;
	wxTextCtrl* m_pPassCtrl;

	wxString	m_szDefaultUser;
	wxString	m_szDefaultPass;

private:
	DECLARE_CLASS(wxOptionsDialog)
	// any class wishing to process wxWindows events must use this macro
	DECLARE_EVENT_TABLE()
};

#endif // _WXOPTIONSDIALOG_H__INCLUDED_
