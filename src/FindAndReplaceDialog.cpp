#include "FindAndReplaceDialog.h"
#include<gtkmm/box.h>
#include<gtkmm/entrybuffer.h>
#include<glibmm/ustring.h>
#include<gtkmm/window.h>
#include "MainWindow.h"

FindAndReplaceDialog::FindAndReplaceDialog(): Gtk::Dialog{"Find&Replace", true}, m_entry_ref_ptr{Gtk::EntryBuffer::create()},
                                              m_entry{m_entry_ref_ptr}, m_find_button{"Find"}, m_exit_button{"X"} {
    
    set_default_size(100, 20);
    set_border_width(10);

    find_box.pack_start(m_entry);
    m_entry.show();

    m_find_button.signal_clicked().connect(sigc::mem_fun(*this, &FindAndReplaceDialog::FindAllSignalHandler));
    find_box.pack_start(m_find_button, Gtk::PACK_SHRINK, 2);
    m_find_button.show();

    m_exit_button.signal_clicked().connect(sigc::mem_fun(*this, &FindAndReplaceDialog::ExitSignalHandler));

    find_box.pack_start(m_exit_button);
    m_exit_button.show();
    
    
    //get_vbox()->pack_start(m_exit_box, Gtk::PACK_SHRINK);
    get_vbox()->pack_start(find_box, Gtk::PACK_SHRINK);

    get_vbox()->show_all();
}

FindAndReplaceDialog::FindAndReplaceDialog(MainWindow *parent): FindAndReplaceDialog::FindAndReplaceDialog(){
    window = parent;
}

void FindAndReplaceDialog::FindAllSignalHandler(){
    window->UnHighlightFindText();
    Glib::ustring findText = m_entry_ref_ptr->get_text();
    window->HighlightFindText(findText);
}

void FindAndReplaceDialog::ExitSignalHandler(){
    destroy_();
}

FindAndReplaceDialog::~FindAndReplaceDialog(){
    window->UnHighlightFindText();
}

