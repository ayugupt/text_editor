#include "FileFunctions.h"
#include<iostream>
#include<gtkmm/filechooserdialog.h>
#include<gtkmm/messagedialog.h>

std::string GetFileName(std::string str){
    int index{-1};

    for(int i = str.size()-1; i >= 0; i--){
        if(str[i] == '/' || str[i] == '\\'){
            index = i;
            break;
        }
    }

    if(index != -1){
        return str.substr(index+1); 
    }
    return str;
}

std::string OpenFileChooserDialog(Gtk::Window &window, Gtk::FileChooserAction action){
    Gtk::FileChooserDialog dialog("Please Choose a file", action);

    dialog.set_transient_for(window);

    dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
    dialog.add_button("_Open", Gtk::RESPONSE_OK);

    auto file_filter = Gtk::FileFilter::create();
    file_filter->set_name("Text files");
    file_filter->add_mime_type("text/plain");
    dialog.add_filter(file_filter);

    int result = dialog.run();

    switch(result){
        case(Gtk::RESPONSE_OK):
        {
            auto file = dialog.get_filename();
            return file;
        }default:
        {
            return "";
        }
    }
}

int OpenSimpleDialog(Gtk::Window &window, const char *message){
    Gtk::MessageDialog dialog(window, message);
    dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);

    return dialog.run();
}