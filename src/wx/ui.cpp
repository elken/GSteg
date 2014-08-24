#include "ui.h"

BEGIN_EVENT_TABLE(UI, wxFrame)
    EVT_MENU(wxID_OPEN,     UI::OnOpen)
    EVT_MENU(wxID_SAVE,     UI::OnSave)
    EVT_MENU(wxID_SAVEAS,   UI::OnSaveAs)
    EVT_MENU(wxID_EXIT,     UI::OnExit)
    EVT_MENU(wxID_ENCODE,   UI::OnEncode)
    EVT_MENU(wxID_DECODE,   UI::OnDecode)
    EVT_MENU(wxID_ABOUT,    UI::OnAbout)
END_EVENT_TABLE()

UI::UI(const wxString& title, int xpos, int ypos, int w, int h) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(w, h))
{
    CreateBars(m_pMenuBar, m_pFileMenu, m_pEncodeMenu, m_pDecodeMenu, m_pHelpMenu);
}

UI::~UI(){}

void UI::CreateBars(wxMenuBar  *m_pMenuBar, wxMenu *m_pFileMenu, wxMenu *m_pEncodeMenu, wxMenu *m_pDecodeMenu, wxMenu *m_pHelpMenu)
{
        // Define & allocate menubar
        m_pMenuBar = new wxMenuBar();

        // File menu create & initialize
        m_pFileMenu = new wxMenu();
        m_pFileMenu->Append(wxID_OPEN, _T("&Open"), _T("Open an image for (en|de)coding"));
        m_pFileMenu->Append(wxID_SAVE, _T("&Save"), _T("Overwrite existing image"));
        m_pFileMenu->Append(wxID_SAVEAS, _T("&Save As"), _T("Save to new image"));
        m_pFileMenu->AppendSeparator();
        m_pFileMenu->Append(wxID_EXIT, _T("&Quit"), _T("Quit the application"));
        m_pMenuBar->Append(m_pFileMenu, _T("&File"));

        //Encode menu
        m_pEncodeMenu = new wxMenu();
        m_pEncodeMenu->Append(wxID_ENCODE, _T("&Encode"), _T("Start encoding process"));
        m_pMenuBar->Append(m_pEncodeMenu, _T("&Encode"));

        // Decode menu
        m_pDecodeMenu = new wxMenu();
        m_pDecodeMenu->Append(wxID_DECODE, _T("&Decode"), _T("Start decoding process"));
        m_pMenuBar->Append(m_pDecodeMenu, _T("&Decode"));
        
        // About/help menu
        m_pHelpMenu = new wxMenu();
        m_pHelpMenu->Append(wxID_ABOUT, _T("&About"), _T("Help information about the program"));
        m_pMenuBar->Append(m_pHelpMenu, _T("&Help"));

        // Create menubar & statusbar
        SetMenuBar(m_pMenuBar);
        CreateStatusBar(3);
}

void UI::OnOpen(wxCommandEvent &event)
{
	wxFileDialog *OpenDialog = new wxFileDialog(this, _T("Choose a file"), _(""), _(""), _("*.*"), wxFD_OPEN);
	if (OpenDialog->ShowModal() == wxID_OK)
	{
		wxString path = OpenDialog->GetPath();
		path.IsAscii() ?
			SetStatusText(_T("Loaded")) :
			SetStatusText(_T("Load Failed"));

	}
	OpenDialog->Close();
}

void UI::OnSave(wxCommandEvent &event)
{
    wxFileDialog *SaveDialog = new wxFileDialog(this, _T("Choose a file"), _(""), _(""), _("*.*"), wxFD_SAVE);
    if (SaveDialog->ShowModal() == wxID_OK)
    {
        wxString path = SaveDialog->GetPath();
        path.IsAscii() ?
            SetStatusText(_T("Saved")) :
            SetStatusText(_T("Save Failed"));

    }
    SaveDialog->Close();
}

void UI::OnSaveAs(wxCommandEvent &event)
{
    wxFileDialog *SaveAsDialog = new wxFileDialog(this, _T("Choose a file"), _(""), _(""), _("*.*"), wxFD_SAVE);
    if (SaveAsDialog->ShowModal() == wxID_OK)
    {
        wxString path = SaveAsDialog->GetPath();
        path.IsAscii() ?
            SetStatusText(_T("Saved")) :
            SetStatusText(_T("Save Failed"));

    }
    SaveAsDialog->Close();
}


void UI::OnEncode(wxCommandEvent &event)
{
    wxLogMessage(_T("TODO: Create encode functionality")); 
}

void UI::OnDecode(wxCommandEvent &event)
{
    wxLogMessage(_T("TODO: Create decode functionality")); 
}

void UI::OnAbout(wxCommandEvent &event)
{
    wxLogMessage(_T("TODO: Create an about window")); 
}

void UI::OnExit(wxCommandEvent &event)
{
   Close(false); 
}
