#ifndef WXSTEG_H
#define WXSTEG_H

#include <wx/wx.h>
#include "ui.h"
#include "logger.h"

class WxSteg : public wxApp
{
	wxFrame			*frame;
	wxImagePanel	*drawPane;
	wxBoxSizer		*sizer	= new wxBoxSizer(wxHORIZONTAL);

public:
    virtual bool OnInit();
};

#endif //WXSTEG_H
