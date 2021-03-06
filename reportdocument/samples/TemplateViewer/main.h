#ifndef __main__
#define __main__

// main wxWidgets header file
#include <wx/wx.h>
// gui classes generated by wxFormBuilder
#include "gui.h"
#include "wx/report/reportdocument.h"

////////////////////////////////////////////////////////////////////////////////
// application class declaration 
////////////////////////////////////////////////////////////////////////////////

class MainApp : public wxApp
{
	public:
		virtual bool OnInit();
};

// declare global static function wxGetApp()
DECLARE_APP(MainApp)

wxPrintData g_printData;

////////////////////////////////////////////////////////////////////////////////
// main application frame declaration 
////////////////////////////////////////////////////////////////////////////////

class MainFrame : public MainFrameBase
{
	public:
		MainFrame( wxWindow *parent );
		virtual ~MainFrame();
		wxReportDocument prt;
		
protected:
		void DrawPage();
		
		// protected event handlers
		virtual void OnCloseFrame( wxCloseEvent& event );
		virtual void OnOpen( wxCommandEvent& event );
		virtual void OnPrint( wxCommandEvent& event );
		virtual void OnPreview( wxCommandEvent& event );
		virtual void OnExitClick( wxCommandEvent& event );
		virtual void OnPageNumber( wxSpinEvent& event );
		virtual void OnPageNumber( wxCommandEvent& event );
		virtual void OnPageSetup( wxCommandEvent& event );
		virtual void OnPaint( wxPaintEvent& event );
};

#endif //__main__