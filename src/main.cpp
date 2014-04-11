#include <gtkmm.h>
#include "gsteg.h"

int main(int argc, char *argv[])
{
  Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "org.gtkmm.gsteg");

  GSteg window;

  //Shows the window and returns when it is closed.
  return app->run(window);
}
