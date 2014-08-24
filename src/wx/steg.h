#ifndef STEG_H
#define STEG_H

#include <wx/wx.h>

class Steg
{
	wxString *m_pPath;

public:
	Steg();
	~Steg();
	wxString m_getFiletype(wxString *path);
};

#endif //STEG_H