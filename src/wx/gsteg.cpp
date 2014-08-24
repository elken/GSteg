#include "gsteg.h"

IMPLEMENT_APP(GSteg)

bool GSteg::OnInit()
{
    UI* gsteg = new UI(wxT("Test"), wxALIGN_CENTER_HORIZONTAL, wxALIGN_CENTER_VERTICAL, 1024, 800);
    gsteg->Show(true);
    return true;
}
