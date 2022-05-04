#pragma once

#include<string>
#include<gtkmm/window.h>
#include<gtkmm/filechooserdialog.h>

std::string GetFileName(std::string str);
std::string OpenFileChooserDialog(Gtk::Window &window, Gtk::FileChooserAction action);
int OpenSimpleDialog(Gtk::Window &window, const char *message);
