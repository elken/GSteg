/*
 * main.cc
 * Copyright (C) 2014 elken <elken.tdos@gmail.com>
 * 
 * image_viewer is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * image_viewer is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <gtkmm-3.0/gtkmm.h>
#include <iostream>
#define UI_FILE "gsteg.ui"

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

/*
int encode(const char* iBmp, const char* oBmp, const char* txt)
{
    std::ifstream i(iBmp, std::ios::binary | std::ios::ate), t(txt, std::ios::ate);
    std::ofstream o(oBmp, std::ios::binary);

    if(o.bad() == true)
    {
        o << " " << std::endl;
        o.close();
    }
    
    if(i.is_open() && o.is_open() && t.is_open())
    {
        const std::streampos iSize = i.tellg();
        const std::streampos tSize = t.tellg();
        char* header = new char [54];
        char* eBuf = new char [sizeof(int(iSize)-54)];
        char* tBuf = new char [tSize];

        i.seekg(0, std::ios::beg);
        t.seekg(0, std::ios::beg);
        i.read(header, 54);
        i.seekg(54);
        i.read(eBuf, int(iSize)-54);
        t.read(tBuf, tSize);
        o.write(header, 54);
        o << char(3);
        o.write(tBuf, tSize);
        o << char(7);
        o.write(eBuf, sizeof(eBuf));
        return 0;
    }
    else
    {
        std::cerr << "I am error." << std::endl;
        return 1;
    }
}

int decode(const char* iBmp)
{
    std::ifstream i(iBmp, std::ios::binary | std::ios::ate);

    if(i.is_open())
    {
        std::streampos iSize = i.tellg();
        i.seekg(55);
        char* tBuf = new char[int(iSize)-54];

        for(int j=0;i.peek()!=char(7);j++)
        {
            tBuf[j] = i.get();
        }

        for(int k=0;k<(int(iSize)-54);k++)
        {
            std::cout << tBuf[k];
        }

        return 0;
    }
    else
    {
        std::cerr << "I am error." << std::endl;
        return 1;
    }
}
*/
static void on_open_image()
{
//	Gtk::FileChooserDialog dialog("Open image", Gtk::FILE_CHOOSER_ACTION_OPEN);
//	dialog.add_button (Gtk::Stock::OPEN, Gtk::RESPONSE_ACCEPT);
//	dialog.add_button (Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
//
//	Glib::RefPtr<Gtk::FileFilter> filter = Gtk::FileFilter::create();
//	filter->add_pixbuf_formats ();
//	filter->set_name("Images");
//	dialog.add_filter(filter);
//
//	const int response = dialog.run();
//	dialog.hide();
//
//	switch(response)
//	{
//		case Gtk::RESPONSE_ACCEPT:
//                {
//                        Glib::RefPtr<Gdk::Pixbuf> pix = Gdk::Pixbuf::create_from_file(dialog.get_filename());
//			image_in->set(pix->scale_simple(200, 100, Gdk::INTERP_BILINEAR));
//                }
//		default:
//			break;
//	}
}

int main (int argc, char *argv[])
{
	Gtk::Main kit(argc, argv);
        
	Gtk::Window* gsteg_window;
        gsteg_help.set_can_focus(0);
        gsteg_help.set_type_hint(Gdk::WINDOW_TYPE_HINT_DIALOG);
        gsteg_help.set_program_name("GSteg");
        gsteg_help.set_version("v0.1");
        gsteg_help.set_comments("Application to embed text within an image, all sneaky like.");
        gsteg_help.set_website("http://www.github.com/elken/GSteg");
        gsteg_help.set_website_label("Homepage");
        gsteg_help.set_logo_icon_name("help-about");
        gsteg_help.set_license_type(Gtk::LICENSE_BSD);
    
        gsteg_help.show_all_children();
        kit.run(gsteg_help);
//        Glib::RefPtr<Gtk::Builder> gsteg_ui;
//        try
//        {
//            gsteg_ui = Gtk::Builder::create_from_file(UI_FILE);
//        }
//        catch (const Glib::FileError & ex)
//        {
//            std::cerr << ex.what() << std::endl;
//            return 1;
//        }
//
        //gsteg_ui->get_widget("gsteg_window", gsteg_window);
        //gsteg_ui->get_widget("gsteg_grid", gsteg_grid);
        //gsteg_ui->get_widget("help_item", help_item);
        
        //help_item->signal_activate().connect(sigc::mem_fun(*this, &help_item_activate_cb))


        //std::cerr << gsteg_window->get_title() << std::endl;
	//gsteg_window->show_all_children();
	//kit.run(*gsteg_window);
	return 0;
}
