#include "gsteg.h"
#include <gtkmm.h>
#include <iostream>
#include <fstream>

GSteg::GSteg() : gsteg_box(Gtk::ORIENTATION_VERTICAL)
{
    //Default gubbins:
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
  
    //Create and allocate the builder:
    Glib::RefPtr<Gtk::Builder> gsteg_ui = Gtk::Builder::create();
    Glib::ustring ui_info = 
    "<interface>"
        "<menu id='gsteg_menu'>"
            "<submenu>"
                "<attribute name='label' translatable='yes'>_File</attribute>"
                    "<section>"
                        "<item>"
                            "<attribute name='label' translatable='yes'>_Open</attribute>"
                            "<attribute name='action'>gsteg.open</attribute>"
                        "</item>"
                        "<item>"
                            "<attribute name='label' translatable='yes'>_Save As</attribute>"
                            "<attribute name='action'>gsteg.saveas</attribute>"
                        "</item>"
                    "</section>"
                    "<section>"
                        "<item>"
                            "<attribute name='label' translatable='yes'>_Quit</attribute>"
                            "<attribute name='action'>gsteg.quit</attribute>"
                        "</item>"
                    "</section>"
            "</submenu>"
            "<submenu>"
                "<attribute name='label' translatable='yes'>_Encode</attribute>"
                    "<section>"
                        "<item>"
                            "<attribute name='label' translatable='yes'>_Encode</attribute>"
                            "<attribute name='action'>gsteg.encode</attribute>"
                        "</item>"
                    "</section>"
            "</submenu>"
            "<submenu>"
                "<attribute name='label' translatable='yes'>_Decode</attribute>"
                    "<section>"
                        "<item>"
                            "<attribute name='label' translatable='yes'>_Decode</attribute>"
                            "<attribute name='action'>gsteg.decode</attribute>"
                        "</item>"
                    "</section>"
            "</submenu>"
            "<submenu>"
                "<attribute name='label' translatable='yes'>_Help</attribute>"
                    "<item>"
                        "<attribute name='label' translatable='yes'>_About</attribute>"
                        "<attribute name='action'>gsteg.about</attribute>"
                    "</item>"
            "</submenu>"
    "</menu>";
    try
    {
        gsteg_ui->add_from_string(ui_info);
    }
    catch(const Glib::Error& ex)
    {
        std::cerr << "Unable to construct menus from ui file. Check for existence." <<  ex.what();
    }
  
    //Get the menubar:
    Glib::RefPtr<Gio::Menu> gmenu = Glib::RefPtr<Gio::Menu>::cast_dynamic(gsteg_ui->get_object("gsteg_menu"));
  
    if(!gmenu)
    {
        g_warning("gmenu not found");
    } 

    Gtk::MenuBar* gsteg_menu = new Gtk::MenuBar(gmenu);
  
    //Create and add empty image to window:
    gsteg_image = Gtk::manage(new Gtk::Image());

    //Create and allocate txt_in:
    gsteg_txt_in = Gtk::manage(new Gtk::TextView());
    gsteg_txt_in->set_wrap_mode(Gtk::WRAP_CHAR);
    gsteg_txt_in->set_buffer(gsteg_txt_buf);

    //Create the ScrolledWindow to stop TextView auto-resizing:
    gsteg_txt_no_scroll = Gtk::manage(new Gtk::ScrolledWindow());
    gsteg_txt_no_scroll->add(*gsteg_txt_in);

    //AboutDialog gubbins:
    gsteg_about.set_logo_icon_name("help-about");
    gsteg_about.set_program_name("GSteg");
    gsteg_about.set_version("1.0");
    gsteg_about.set_copyright("Ellis Kenyo");
    gsteg_about.set_comments("GSteg is an application for embedding text within an image.");
    gsteg_about.set_license_type(Gtk::LICENSE_BSD);

    gsteg_about.set_website("http://www.elken.github.io/GSteg");
    gsteg_about.set_website_label("Homepage");

    //Add widgets to the window:
    gsteg_box.pack_start(*gsteg_menu, Gtk::PACK_SHRINK);
    gsteg_box.pack_start(*gsteg_image, true, true);
    gsteg_box.pack_start(*gsteg_txt_no_scroll, true, true);

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
                image_in.open(dialog.get_filename().c_str());
                if(image_in.is_open())
                {
                    image_in.seekg(0, std::ios::end);
                    const std::streampos size = image_in.tellg();
                    header = new char[54];
                    eBuf = new char [sizeof(int(size)-54)];

                    image_in.seekg(0, std::ios::beg);
                    image_in.read(header, 54);
                    image_in.seekg(54);
                    image_in.read(eBuf, int(size)-54);
                }
                else
                {
                    std::cout << "Fail" << std::endl;
                }
            }
                break;
            default:
                break;
        }
}

void GSteg::on_action_file_saveas()
{
    
    Gtk::FileChooserDialog dialog("Save Image", Gtk::FILE_CHOOSER_ACTION_SAVE);
    dialog.add_button(Gtk::Stock::SAVE, Gtk::RESPONSE_ACCEPT);
    dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);

    Glib::RefPtr<Gtk::FileFilter> filter = Gtk::FileFilter::create();
    filter->add_pixbuf_formats();
    filter->set_name("Images");
    dialog.add_filter(filter);

    const int response = dialog.run();
    dialog.hide();

    switch(response)
    {
        case Gtk::RESPONSE_ACCEPT:
            {
            }
    }

}

void GSteg::on_action_file_quit()
{
  hide();
}

void GSteg::on_action_encode()
{
    Glib::ustring str = gsteg_txt_in->get_buffer()->get_text();
    itBuf = reinterpret_cast<const char*>(str.c_str());

    if(image_in.is_open())
    {
        std::ofstream o("out.bmp", std::ios::binary);
        if(o.bad() == true)
        {
            o << " " << std::endl;
            o.close();
        }
        o.write(header, 54);
        o << char(3);
        o.write(itBuf, gsteg_txt_in->get_buffer()->get_char_count());
        o << char(7);
        o.write(eBuf, sizeof(eBuf));
        o.close();
        image_in.close();
        delete[] eBuf, itBuf; 
    }
    else
    {
        std::cout << "Fail: loading image on encode action." << std::endl;
    }
}

void GSteg::on_action_decode()
{
    if(image_in.is_open())
    {
        image_in.seekg(0, std::ios::end);
        std::streampos size = image_in.tellg();
        image_in.seekg(55);
        char* otBuf = new char[int(size)-54];

        for(int i=0;image_in.peek()!=char(7);i++)
        {
            otBuf[i] = image_in.get();
        }

        Glib::ustring str = otBuf;
        delete[] otBuf;

        gsteg_txt_in->get_buffer()->set_text(str);
        image_in.close();
    }
    else
    {
        std::cout << "Fail: Image load on decode action." << std::endl;
    }
}

void GSteg::on_action_help_about()
{
    int response = gsteg_about.run();    
    switch (response)
    {
        case Gtk::RESPONSE_CANCEL:
        {
            gsteg_about.hide();
        }
            break;
        default:
            break;
    }
}
