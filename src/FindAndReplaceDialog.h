#pragma once

#include<gtkmm/dialog.h>
#include<gtkmm/box.h>
#include<gtkmm/entry.h>
#include<gtkmm/entrybuffer.h>
#include<glibmm/refptr.h>
#include "MainWindow.h"
class FindAndReplaceDialog: public Gtk::Dialog{
protected:
    Gtk::Box find_box;

    Glib::RefPtr<Gtk::EntryBuffer> m_entry_ref_ptr;
    Gtk::Entry m_entry;

    Gtk::Button m_find_button;
    Gtk::Button m_exit_button;

    MainWindow *window;

public: 
    FindAndReplaceDialog();
    FindAndReplaceDialog(MainWindow *parent);

    void FindAllSignalHandler();
    void ExitSignalHandler();

    void PositionWindowInitially();

    ~FindAndReplaceDialog();

};
