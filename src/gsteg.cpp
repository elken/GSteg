#include "gsteg.h"
#include <gtkmm.h>
#include <iostream>
#include <fstream>

GSteg::GSteg() : gsteg_box(Gtk::ORIENTATION_VERTICAL)
{
    //Default gubbins:
    set_title("GSteg");
    set_default_size(500, 500);
    add(gsteg_box); 
  
    //Define the actions:
    gsteg_ag = Gio::SimpleActionGroup::create();
  
    gsteg_ag->add_action("open",    sigc::mem_fun(*this, &GSteg::on_action_file_open));
    gsteg_ag->add_action("quit",    sigc::mem_fun(*this, &GSteg::on_action_file_quit));
    gsteg_ag->add_action("encode",  sigc::mem_fun(*this, &GSteg::on_action_encode));
    gsteg_ag->add_action("decode",  sigc::mem_fun(*this, &GSteg::on_action_decode));
    gsteg_ag->add_action("about",   sigc::mem_fun(*this, &GSteg::on_action_help_about));
  
    insert_action_group("gsteg", gsteg_ag);

    this->add_events(Gdk::KEY_PRESS_MASK);
    this->signal_key_release_event().connect(sigc::mem_fun(*this, &GSteg::on_key_release));

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
                            "<attribute name='accel'>&lt;Primary&gt;o</attribute>"
                        "</item>"
                   "</section>"
                   "<section>"
                        "<item>"
                            "<attribute name='label' translatable='yes'>_Quit</attribute>"
                            "<attribute name='action'>gsteg.quit</attribute>"
                            "<attribute name='accel'>&lt;Primary&gt;q</attribute>"
                        "</item>"
                    "</section>"
            "</submenu>"
            "<submenu>"
                "<attribute name='label' translatable='yes'>_Encode</attribute>"
                    "<section>"
                        "<item>"
                            "<attribute name='label' translatable='yes'>_Encode</attribute>"
                            "<attribute name='action'>gsteg.encode</attribute>"
                            "<attribute name='accel'>&lt;Primary&gt;e</attribute>"
                        "</item>"
                    "</section>"
            "</submenu>"
            "<submenu>"
                "<attribute name='label' translatable='yes'>_Decode</attribute>"
                    "<section>"
                        "<item>"
                            "<attribute name='label' translatable='yes'>_Decode</attribute>"
                            "<attribute name='action'>gsteg.decode</attribute>"
                            "<attribute name='accel'>&lt;Primary&gt;d</attribute>"
                        "</item>"
                    "</section>"
            "</submenu>"
            "<submenu>"
                "<attribute name='label' translatable='yes'>_Help</attribute>"
                    "<item>"
                        "<attribute name='label' translatable='yes'>_About</attribute>"
                        "<attribute name='action'>gsteg.about</attribute>"
                        "<attribute name='accel'>F1</attribute>"
                    "</item>"
            "</submenu>"
    "</menu>";
    try
    {
        gsteg_ui->add_from_string(ui_info);
    }
    catch(const Glib::Error& ex)
    {
        msgBox("Unable to load UI", "The UI string is invalid. Correct and try again.", "UI Error", Gtk::MESSAGE_ERROR);
    }

    //Get the menubar:
    Glib::RefPtr<Gio::Menu> gmenu = Glib::RefPtr<Gio::Menu>::cast_dynamic(gsteg_ui->get_object("gsteg_menu"));
  
    if(!gmenu)
    {
        msgBox("Unable to load menu from UI", "Unable to read the menu, or the menu failed to initialize.", "UI Error", Gtk::MESSAGE_ERROR);
    } 

    gsteg_menu = new Gtk::MenuBar(gmenu);
  
    //Create and add empty image to window:
    gsteg_image = Gtk::manage(new Gtk::Image());

    //Create and allocate txt_in:
    gsteg_txt_in = Gtk::manage(new Gtk::TextView());
    gsteg_txt_in->set_wrap_mode(Gtk::WRAP_CHAR);
    gsteg_txt_in->set_buffer(gsteg_txt_buf);

    //Create the ScrolledWindow to stop TextView auto-resizing:
    gsteg_txt_no_scroll = Gtk::manage(new Gtk::ScrolledWindow());
    gsteg_txt_no_scroll->add(*gsteg_txt_in);

    //Create the ScrolledWindow to stop Image auto-resizing:
    gsteg_img_no_scroll = Gtk::manage(new Gtk::ScrolledWindow());
    gsteg_img_no_scroll->add(*gsteg_image);

    //AboutDialog gubbins:
    gsteg_about.set_logo_icon_name("help-about");
    gsteg_about.set_program_name("GSteg");
    gsteg_about.set_version("1.0");
    gsteg_about.set_copyright("Ellis Kenyo");
    gsteg_about.set_comments("GSteg is an application for embedding text within an image.");
    gsteg_about.set_license_type(Gtk::LICENSE_BSD);
    gsteg_about.set_website("http://www.elken.github.io/GSteg");

    //Add widgets to the window:
    gsteg_box.pack_start(*gsteg_menu, Gtk::PACK_SHRINK);
    gsteg_box.pack_start(*gsteg_img_no_scroll, true, true);
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
                if(!image_in.is_open())
                {
                    gsteg_image->set(dialog.get_filename());
                    image_in.open(dialog.get_filename().c_str());
                    image_in.seekg(10);
                    headerEnd = image_in.peek();
                    image_in.seekg(0, std::ios::end);
                    const std::streampos size = image_in.tellg();
                    std::cerr << size;
                    header = new char[headerEnd];
                    dSize = int(size)-headerEnd;
                    eBuf = new char [dSize];

                    image_in.seekg(0, std::ios::beg);
                    image_in.read(header, headerEnd);
                    image_in.seekg(headerEnd);
                    image_in.read(eBuf, int(size)-headerEnd);
                }
                else
                {
                    msgBox("Unable to load image", "The file you selected is unable to be read. Please check and try again", "File error", Gtk::MESSAGE_ERROR);
                }
            }
                break;
            default:
                break;
        }
}

void GSteg::on_action_file_quit()
{
  hide();
}

void GSteg::on_action_encode()
{
    if(image_in.is_open())
    {
        Gtk::FileChooserDialog dialog(("Save Image"), Gtk::FILE_CHOOSER_ACTION_SAVE);
        dialog.add_button(Gtk::Stock::SAVE, Gtk::RESPONSE_ACCEPT);
        dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);

        Glib::RefPtr<Gtk::FileFilter> filter = Gtk::FileFilter::create();
        filter->add_pixbuf_formats();
        filter->set_name("Images");
        dialog.add_filter (filter);

        const int response = dialog.run();
        dialog.hide();
 
        switch(response)
        {
            case Gtk::RESPONSE_ACCEPT:
            {
                image_out.open(dialog.get_filename().c_str());
                std::cerr << header[10] << std::endl << header[9] << std::endl;
                if(image_out.is_open())
                {
                    image_out.write(header, headerEnd);
                    image_out << char(3);
                    image_out.write(reinterpret_cast<const char*>(gsteg_txt_in->get_buffer()->get_text().c_str()), gsteg_txt_in->get_buffer()->get_char_count());
                    image_out << char(7);
                    image_out.write(eBuf, dSize);
                    image_in.close();
                    image_out.close();
                    delete[] eBuf;            
                }
                else
                {
                    msgBox("Error saving image", "Unable to save this, please try again.", "Save error", Gtk::MESSAGE_ERROR);
                }
            }
                break;
            default:
               break; 
        }
    }
    else
    {
        msgBox("Unable to load image", "The file you selected is unable to be read. Please check and try again", "File error", Gtk::MESSAGE_ERROR);
    }
}

void GSteg::on_action_decode()
{
    if(image_in.is_open())
    {
        image_in.seekg(0, std::ios::end);
        image_in.seekg(headerEnd+1);

        for(int i=0;image_in.peek()!=char(7);i++)
        {
            otBuf += char(image_in.get());
        }

        msgBox("The decoded text reads: ", otBuf, "Decoded", Gtk::MESSAGE_INFO);
        image_in.close();
    }
    else
    {
        msgBox("Unable to load image", "The file you selected is unable to be read. Please check and try again", "File error", Gtk::MESSAGE_ERROR);
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

bool GSteg::on_key_release(GdkEventKey* event)
{
   if((event->keyval == GDK_KEY_o) && (event->state &(GDK_SHIFT_MASK | GDK_CONTROL_MASK | GDK_MOD1_MASK)) == GDK_CONTROL_MASK)    
   {
       on_action_file_open();
       return true;
   }
   else if((event->keyval == GDK_KEY_q) && (event->state &(GDK_SHIFT_MASK | GDK_CONTROL_MASK | GDK_MOD1_MASK)) == GDK_CONTROL_MASK)
   {
       on_action_file_quit();
       return true;
   }
   else if((event->keyval == GDK_KEY_e) && (event->state &(GDK_SHIFT_MASK | GDK_CONTROL_MASK | GDK_MOD1_MASK)) == GDK_CONTROL_MASK)
   {
       on_action_encode();
       return true;
   }
   else if((event->keyval == GDK_KEY_d) && (event->state &(GDK_SHIFT_MASK | GDK_CONTROL_MASK | GDK_MOD1_MASK)) == GDK_CONTROL_MASK)
   {
       on_action_decode();
       return true;
   }
   else if(event->keyval == GDK_KEY_F1)
   {
       on_action_help_about();
       return true;
   }
}

void GSteg::msgBox(Glib::ustring pstr, Glib::ustring sstr, Glib::ustring title, Gtk::MessageType mt)
{
    gsteg_message_box = (new Gtk::MessageDialog(pstr, false, mt, Gtk::BUTTONS_OK)); 
    gsteg_message_box->set_title(title);
    gsteg_message_box->set_secondary_text(sstr);
    int response = gsteg_message_box->run();

    switch(response)
    {
        case Gtk::RESPONSE_OK:
        {
            gsteg_message_box->hide();
        }
            break;
        default:
            break;
    }
}
