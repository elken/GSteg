#include "wxsteg.h"

IMPLEMENT_APP(WxSteg)

bool WxSteg::OnInit()
{
    UI* wxsteg = new UI(wxT("Test"), wxALIGN_CENTER_HORIZONTAL, wxALIGN_CENTER_VERTICAL, 1024, 800);
    wxsteg->Show(true);
    return true;
}
