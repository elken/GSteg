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
    void on_action_file_quit();
    void on_action_encode();
    void on_action_decode();
    void on_action_help_about();

    bool on_key_release(GdkEventKey*);

    //Other functions
    void msgBox(Glib::ustring, Glib::ustring, Glib::ustring, Gtk::MessageType);

    //Child widgets:
    Gtk::Box gsteg_box;
    Gtk::Image* gsteg_image;
    Gtk::TextView* gsteg_txt_in;
    Gtk::ScrolledWindow* gsteg_txt_no_scroll; 
    Gtk::ScrolledWindow* gsteg_img_no_scroll;
    Gtk::AboutDialog gsteg_about;
    Gtk::MessageDialog* gsteg_message_box;
    Gtk::MenuBar* gsteg_menu;

    Glib::RefPtr<Gtk::Builder> gsteg_ui;
    Glib::RefPtr<Gio::SimpleActionGroup> gsteg_ag;  
    Glib::RefPtr<Gtk::TextBuffer> gsteg_txt_buf;

    //Misc variables
    char* header;
    char* eBuf;
    const char* itBuf;
    Glib::ustring otBuf;
    int dSize;
    int headerEnd;
    int eStart;
    int eEnd;

    //Stream objects
    std::ifstream image_in;
    std::ofstream image_out;
};

#endif //GSTEG_H
