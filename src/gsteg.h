#ifndef ABOUT_H
#define ABOUT_H

#include <gtkmm.h>

class GSteg : public Gtk::Window
{
public:
  GSteg();
  virtual ~GSteg();

protected:
    void on_button_clicked();
    void on_about_dialog_response(int response_id); 

    Gtk::AboutDialog* gsteg_about;
    Gtk::Image* image_in;
    Gtk::Grid* gsteg_grid;
    Gtk::MenuBar* gsteg_menu; 
    Gtk::MenuItem* file_menuitem ,help_menuitem; 
    Gtk::Menu* file_menu, help_menu;
    Gtk::ImageMenuItem* open_item, save_item, saveas_item, quit_item, help_item;
    Gtk::Button* btn_encode, btn_decode;
    Gtk::Entry* txt_in;
    
    Gtk::AboutDialog gsteg_help;
    Gtk::Box* gsteg_helpbox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL));
    Gtk::ButtonBox* gsteg_close_area;
};

#endif 
