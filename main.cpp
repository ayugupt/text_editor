#include<config.h>
#include<gtkmm/application.h>
#include<MainWindow.h>

int main(int argc, char *argv[]){
    auto app = Gtk::Application::create("org.gtkmm.example");
    app->set_accel_for_action("menu.save", "<Primary>s");
    app->set_accel_for_action("menu.saveas", "<Primary>d");
    app->set_accel_for_action("menu.open", "<Primary>o");
    app->set_accel_for_action("menu.new", "<Primary>n");
    app->set_accel_for_action("menu.findreplace", "<Primary>f");

    
    if(argc > 1){
        MainWindow argWindow(argv[1]);
        return app->run(argWindow);
    }
    MainWindow mainWindow;
    return app->run(mainWindow);
}