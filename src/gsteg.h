#ifndef GSTEG_H
#define GSTEG_H

#include <gtkmm.h>
#include <fstream>

class GSteg : public Gtk::Window
{
public:
    GSteg();
    ~GSteg();

private:
    //Signal handlers:
    void on_action_file_open();
    void on_action_file_saveas();
    void on_action_file_quit();
    void on_action_encode();
    void on_action_decode();
    void on_action_help_about();
    void on_action_help_about_close();
    void on_action_others();
    void on_action_toggle();    

    //Child widgets:
    Gtk::Box gsteg_box;
    Gtk::Image* gsteg_image;
    Gtk::TextView* gsteg_txt_in;
    Gtk::ScrolledWindow* gsteg_txt_no_scroll; 
    Gtk::AboutDialog gsteg_about;
    
    Glib::RefPtr<Gtk::Builder> gsteg_ui;
    Glib::RefPtr<Gio::SimpleActionGroup> gsteg_ag;  
    Glib::RefPtr<Gtk::TextBuffer> gsteg_txt_buf;

    //Misc variables
    std::string gsteg_image_path;   
    char* header;
    char* eBuf;
    const char* itBuf;
    const char* otBuf;

    //Stream objects
    std::fstream image_in;
};

#endif //GSTEG_H
