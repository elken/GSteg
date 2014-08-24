#ifndef UI_H
#define UI_H

#include <wx/wx.h>
#include "panel.h"

class UI : public wxFrame
{
public:
    UI(const wxString& title, int xpos, int ypos, int w, int h);
    ~UI();
    void CreateBars(wxMenuBar  *m_pMenuBar, wxMenu *m_pFileMenu, wxMenu *m_pEncodeMenu, wxMenu *m_pDecodeMenu, wxMenu *m_pHelpMenu);

    void OnOpen(wxCommandEvent &event);
    void OnSave(wxCommandEvent &event);
    void OnSaveAs(wxCommandEvent &event);
    void OnExit(wxCommandEvent &event);
    void OnEncode(wxCommandEvent &event);
    void OnDecode(wxCommandEvent &event);
    void OnAbout(wxCommandEvent &event);

    wxMenuBar  *m_pMenuBar;
    wxMenu     *m_pFileMenu;
    wxMenu     *m_pEncodeMenu;
    wxMenu     *m_pDecodeMenu;
    wxMenu     *m_pHelpMenu;

protected:
    DECLARE_EVENT_TABLE()

};

enum 
{
    wxID_ENCODE = 1,
    wxID_DECODE = 4
};

#endif //UI_H
