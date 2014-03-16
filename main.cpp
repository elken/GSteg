/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
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

Gtk::Image* image = 0;
Gtk::Box* box = Gtk::manage(new Gtk::Box());
static void on_open_image()
{
	Gtk::FileChooserDialog dialog("Open image", Gtk::FILE_CHOOSER_ACTION_OPEN);
	dialog.add_button (Gtk::Stock::OPEN, Gtk::RESPONSE_ACCEPT);
	dialog.add_button (Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);

	Glib::RefPtr<Gtk::FileFilter> filter = Gtk::FileFilter::create();
	filter->add_pixbuf_formats ();
	filter->set_name("Images");
	dialog.add_filter(filter);

        

	const int response = dialog.run();
	dialog.hide();

	switch(response)
	{
		case Gtk::RESPONSE_ACCEPT:
                {
                        Glib::RefPtr<Gdk::Pixbuf> pix = Gdk::Pixbuf::create_from_file(dialog.get_filename());
			image->set(pix->scale_simple(200, 100, Gdk::INTERP_BILINEAR));
                }
		default:
			break;
	}
}

   
int main (int argc, char *argv[])
{
	Gtk::Main kit(argc, argv);
        
	Gtk::Window main_win;
	main_win.set_title ("QSteg");

	box->set_orientation (Gtk::ORIENTATION_VERTICAL);
	box->set_spacing (6);
	main_win.add(*box);

	image = Gtk::manage (new Gtk::Image ());
	box->pack_start(*image, true, true);

	Gtk::Button* button = Gtk::manage (new Gtk::Button("Open image..."));
	button->signal_clicked ().connect(
	                                  sigc::ptr_fun(&on_open_image));
	box->pack_start(*button, false, false);

	main_win.show_all_children();
	kit.run(main_win);
	return 0;
}
