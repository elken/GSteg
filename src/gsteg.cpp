#include "gsteg.h"
#include <gtkmm.h>
#include <iostream>

GSteg::GSteg() : gsteg_box(Gtk::ORIENTATION_VERTICAL)
{
    set_title("GSteg");
    set_default_size(200, 200);
  
    add(gsteg_box); 
  
    //Define the actions:
    gsteg_ag = Gio::SimpleActionGroup::create();
  
    gsteg_ag->add_action("open",    sigc::mem_fun(*this, &GSteg::on_action_file_open));
    gsteg_ag->add_action("saveas",  sigc::mem_fun(*this, &GSteg::on_action_file_saveas));
    gsteg_ag->add_action("quit",    sigc::mem_fun(*this, &GSteg::on_action_file_quit));
    gsteg_ag->add_action("encode",  sigc::mem_fun(*this, &GSteg::on_action_encode));
    gsteg_ag->add_action("decode",  sigc::mem_fun(*this, &GSteg::on_action_decode));
    gsteg_ag->add_action("about",   sigc::mem_fun(*this, &GSteg::on_action_help_about));
  
    insert_action_group("gsteg", gsteg_ag);
  
    //Define how the actions are presented in the menus and toolbars:
    Glib::RefPtr<Gtk::Builder> gsteg_ui = Gtk::Builder::create();
  
    try
    {
        gsteg_ui->add_from_file("gsteg.ui");
    }
    catch(const Glib::Error& ex)
    {
        std::cerr << "building menus failed: " <<  ex.what();
    }
  
    //Get the menubar:
    Glib::RefPtr<Gio::Menu> gmenu = Glib::RefPtr<Gio::Menu>::cast_dynamic(gsteg_ui->get_object("gsteg_menu"));
  
    if(!gmenu)
      g_warning("gmenu not found");
  
    Gtk::MenuBar* gsteg_menu = new Gtk::MenuBar(gmenu);
  
    //Create and add empty image to window:
    gsteg_image = Gtk::manage(new Gtk::Image());
  
    //Add the MenuBar to the window:
    gsteg_box.pack_start(*gsteg_menu, Gtk::PACK_SHRINK);
    gsteg_box.pack_start(*gsteg_image, true, true);
  
  
    show_all_children();
}

GSteg::~GSteg()
{
}

void GSteg::on_action_file_open()
{
        Gtk::FileChooserDialog dialog("Open image", Gtk::FILE_CHOOSER_ACTION_OPEN);
        dialog.add_button (Gtk::Stock::OPEN, Gtk::RESPONSE_ACCEPT);
        dialog.add_button (Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);

        Glib::RefPtr<Gtk::FileFilter> filter = Gtk::FileFilter::create();
        filter->add_pixbuf_formats();
        filter->set_name("Images");
        dialog.add_filter (filter);

        const int response = dialog.run();
        dialog.hide();
        
        switch (response)
        {
            case Gtk::RESPONSE_ACCEPT:
            {
                gsteg_image->set(dialog.get_filename());
                gsteg_image_path = dialog.get_filename();
            }
                break;
            default:
                break;
        }
}

void GSteg::on_action_file_saveas()
{
    std::cout << "File_saveas hit." << std::endl;
}

void GSteg::on_action_file_quit()
{
  hide();
}

void GSteg::on_action_encode()
{
 
}

void GSteg::on_action_decode()
{

}

void GSteg::on_action_help_about()
{
    std::cout << "Help_about hit." << std::endl;
    std::cout << gsteg_image_path << std::endl;
}
