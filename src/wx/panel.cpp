#include "panel.h"
#include <sstream>
#include <iostream>

BEGIN_EVENT_TABLE(wxImagePanel, wxPanel)
EVT_PAINT(wxImagePanel::paintEvent)
END_EVENT_TABLE()

// Load the file
wxImagePanel::wxImagePanel(wxFrame *parent, wxString file, wxBitmapType format) : wxPanel(parent)
{
	image.LoadFile(file, format);
	w = -1;
	h = -1;

	m_pAddr = reinterpret_cast<char *>(&image);
}

// Create an event to draw it
void wxImagePanel::paintEvent(wxPaintEvent & evt)
{
	wxPaintDC dc(this);
	render(dc);
}

// Actually draw it
void wxImagePanel::render(wxDC&  dc)
{
	dc.DrawBitmap(image, 0, 0, false);
}

// Get the address of image
wxString wxImagePanel::imgAddress(wxImagePanel *pane)
{
	std::stringstream out;
	out << std::hex << (int)pane->m_pAddr;
	wxString str = out.str();

	return str;
}