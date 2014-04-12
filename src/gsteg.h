#ifndef GSTEG_H
#define GSTEG_H

#include <gtkmm.h>

class GSteg : public Gtk::Window
{
public:
  GSteg();
  virtual ~GSteg();

private:
  //Signal handlers:
  void on_action_file_open();
  void on_action_file_saveas();
  void on_action_file_quit();
  void on_action_encode();
  void on_action_decode();
  void on_action_help_about();
  void on_action_others();
  void on_action_toggle();

  //Child widgets:
  Gtk::Box gsteg_box;
  Gtk::Image* gsteg_image;
  //Gtk::Entry* gsteg_txt_in;
  Gtk::TextView* gsteg_txt_in;
  Gtk::ScrolledWindow* txt_no_scroll;

  Glib::RefPtr<Gtk::Builder> gsteg_ui;
  Glib::RefPtr<Gio::SimpleActionGroup> gsteg_ag;

  //Misc variables
  std::string gsteg_image_path;
};

#endif //GSTEG_H