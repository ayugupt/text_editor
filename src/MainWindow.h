#pragma once
#include<gtkmm/window.h>
#include<iostream>
#include<giomm/simpleaction.h>
#include<giomm/simpleactiongroup.h>
#include<glibmm/refptr.h>
#include<glibmm/ustring.h>
#include<gtkmm/builder.h>
#include<gtkmm/box.h>
#include<gtkmm/button.h>
#include<gtkmm/textview.h>
#include<gtkmm/textbuffer.h>
#include<memory>
#include "FileClass.h"
#include<gtkmm/scrolledwindow.h>

enum class FileState{UNSAVED, SAVED};

class MainWindow: public Gtk::Window{

protected:
    Glib::RefPtr<Gio::SimpleActionGroup> m_action_group_ptr;
    Glib::RefPtr<Gtk::Builder> m_builder;

    Gtk::Box body_box;
    Gtk::Box menu_box;

    Gtk::TextView m_text;
    Glib::RefPtr<Gtk::TextBuffer::Tag> m_buffer_tag_ptr;
    Glib::RefPtr<Gtk::TextBuffer::TagTable> m_buffer_tagtable_ptr;
    Glib::RefPtr<Gtk::TextBuffer> m_buffer_ptr;

    std::unique_ptr<FileClass> m_file;
    FileState m_state{FileState::SAVED};

    Gtk::ScrolledWindow m_scroll;
    bool userChange{true};

    void Render();

public:

    MainWindow();
    MainWindow(const char * fileName);

    template<typename T>
    void AddAction(const Glib::ustring &action_name, T functor){
        m_action_group_ptr->add_action(action_name, functor);

    }
    void HighlightFindText(const Glib::ustring &find);
    void UnHighlightFindText();


    void ActionOpen();
    void ActionNew();
    void ActionSave();
    void ActionSaveAs();
    void ActionFindAndReplace();

    void OnTextChange();
};