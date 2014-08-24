#include "wxsteg.h"
#include <iostream>
#include <sstream>
#include <wx/file.h>

#define ADDRESS drawPane->imgAddress(drawPane)

IMPLEMENT_APP(WxSteg)

bool WxSteg::OnInit()
{
	wxInitAllImageHandlers();
    UI* wxsteg = new UI(wxT("Test"), wxALIGN_CENTER_HORIZONTAL, wxALIGN_CENTER_VERTICAL, 1024, 800);
    
	drawPane = new wxImagePanel(wxsteg, wxT("C:/Users/Ed/Downloads/wxWidgets.png"), wxBITMAP_TYPE_PNG);
	

	wxLog::SetActiveTarget(new wxLogStderr());
	wxLogMessage(ADDRESS);

	sizer->Add(drawPane, 1, wxEXPAND);
	wxsteg->SetSizer(sizer);
	
	wxsteg->Show(true);
    return true;
}
