#include "gsteg.h"
#include <iostream>

GSteg::GSteg()
{
  set_title("GSteg");

  add(m_VBox);

  m_VBox.pack_start(m_Label);
  m_Label.set_line_wrap(true);
  m_Label.set_selectable(true);

  m_VBox.pack_start(m_ButtonBox);
  m_ButtonBox.pack_start(m_Button);
  m_Button.signal_clicked().connect(sigc::mem_fun(*this, &ExampleWindow::on_button_clicked) );

  m_Dialog.set_transient_for(*this);

  m_Dialog.set_program_name("Example application");
  m_Dialog.set_version("1.0.0");
  m_Dialog.set_copyright("Murray Cumming");
  m_Dialog.set_comments("This is just an example application.");
  m_Dialog.set_license("LGPL");

  m_Dialog.set_website("http://www.gtkmm.org");
  m_Dialog.set_website_label("gtkmm website");

  std::vector<Glib::ustring> list_authors;
  list_authors.push_back("Murray Cumming");
  list_authors.push_back("Somebody Else");
  list_authors.push_back("AN Other");
  m_Dialog.set_authors(list_authors);

  m_Dialog.signal_response().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_about_dialog_response) );

  show_all_children();

  // The widget must be realized and mapped before grab_focus() is called.
  // That's why it's called after show_all_children().
  m_Button.grab_focus();
}

ExampleWindow::~ExampleWindow()
{
 
}

void ExampleWindow::on_about_dialog_response(int response_id)
{
  std::cout << response_id
    << ", close=" << Gtk::RESPONSE_CLOSE
    << ", cancel=" << Gtk::RESPONSE_CANCEL
    << ", delete_event=" << Gtk::RESPONSE_DELETE_EVENT
    << std::endl;

  if((response_id == Gtk::RESPONSE_CLOSE) ||
     (response_id == Gtk::RESPONSE_CANCEL) )
  {
    m_Dialog.hide();
  }
}

void ExampleWindow::on_button_clicked()
{
  m_Dialog.show();

  //Bring it to the front, in case it was already shown:
  m_Dialog.present();
}
