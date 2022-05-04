#include"MainWindow.h"
#include<giomm/simpleactiongroup.h>
#include<giomm/simpleaction.h>
#include<glibmm/ustring.h>
#include<gtkmm.h>
#include<gtkmm/button.h>
#include<iostream>
#include "FileFunctions.h"
#include<string>
#include<gtkmm/filechooserdialog.h>
#include "FileClass.h"
#include<algorithm>
#include<vector>
#include "FindAndReplaceDialog.h"
//----------------------------------Constructors----------------------------------------

MainWindow::MainWindow(): m_action_group_ptr{Gio::SimpleActionGroup::create()}, m_builder{Gtk::Builder::create()} 
                            ,body_box{Gtk::ORIENTATION_VERTICAL}, m_buffer_ptr{Gtk::TextBuffer::create(m_buffer_tagtable_ptr)}, m_buffer_tagtable_ptr{Gtk::TextBuffer::TagTable::create()}, m_buffer_tag_ptr{Gtk::TextBuffer::Tag::create("highlight")}
                            ,m_file{nullptr}{
    Render();
}

MainWindow::MainWindow(const char * fileName): m_action_group_ptr{Gio::SimpleActionGroup::create()}, m_builder{Gtk::Builder::create()},
                                                body_box{Gtk::ORIENTATION_VERTICAL}, m_buffer_ptr{Gtk::TextBuffer::create(m_buffer_tagtable_ptr)}, m_buffer_tagtable_ptr{Gtk::TextBuffer::TagTable::create()}, m_buffer_tag_ptr{Gtk::TextBuffer::Tag::create("highlight")},
                                                m_file{new FileClass{fileName}}{
    Render();
    userChange = false;
    m_buffer_ptr->set_text(m_file->Read());
    userChange = true;
    set_title(m_file->GetTheFileName().c_str());
}

//-------------------------------------------------------------------------------------------



//------------------------------------Menu Actions-------------------------------------------

void MainWindow::ActionSave(){
    if(m_file == nullptr){
        ActionSaveAs();
    }else{
         m_file->Write(std::string{m_buffer_ptr->get_text().c_str()});
         set_title(m_file->GetTheFileName().c_str());
         m_state = FileState::SAVED;
    }
}

void MainWindow::ActionOpen(){
    if(m_state==FileState::SAVED || OpenSimpleDialog(*this, "Are you sure you want to open a new File? Current progress will be lost.")==Gtk::RESPONSE_OK){
        std::string new_file = OpenFileChooserDialog(*this, Gtk::FILE_CHOOSER_ACTION_OPEN);
        if(new_file.size() > 0){
            m_file.release();
            m_file.reset(new FileClass{new_file});
            userChange = false;
            m_buffer_ptr->set_text(m_file->Read());
            userChange = true;
            set_title(m_file->GetTheFileName().c_str());
            m_state = FileState::SAVED;
        }
    }
}

void MainWindow::ActionSaveAs(){
    std::string file_name = OpenFileChooserDialog(*this, Gtk::FILE_CHOOSER_ACTION_SAVE);
    if(file_name.size() > 0){
        if(m_file == nullptr){
            m_file.reset(new FileClass{file_name});
            m_file->Write(m_buffer_ptr->get_text());
            set_title(m_file->GetTheFileName().c_str());
        }else{
            m_file->SaveAs(file_name.c_str());
            set_title(m_file->GetTheFileName().c_str());
        }
        m_state = FileState::SAVED;
    }
}

void MainWindow::ActionNew(){
    if(m_state==FileState::SAVED || OpenSimpleDialog(*this, "Are you sure you want to open a new File? Current progress will be lost.")==Gtk::RESPONSE_OK){
        userChange = false;
        m_buffer_ptr->set_text("");
        userChange = true;
        m_file = nullptr;
        set_title("dit");
        m_state = FileState::SAVED;
    }
    
}

void MainWindow::ActionFindAndReplace(){
    FindAndReplaceDialog dialog{this};
    m_text.add_child_in_window(dialog, Gtk::TEXT_WINDOW_WIDGET, m_text.get_width()-400, 0);
    dialog.run();
}

//--------------------------------------------------------------------------------------------


//---------------------------------Signal Handlers-------------------------------------------

void MainWindow::OnTextChange(){
    if(userChange){
        if(m_file == nullptr){
            set_title("dit*");
        }else{
            set_title(m_file->GetTheFileName() + "*");
        }
        m_state = FileState::UNSAVED;
    }
}


//-------------------------------------------------------------------------------------------

//------------------------------------Miscellanous Functions--------------------------------

void MainWindow::HighlightFindText(const Glib::ustring &find){
    std::vector<Gtk::TextBuffer::iterator> allIterators;
    auto itr = m_buffer_ptr->begin();
    while(itr != m_buffer_ptr->end()){
        auto beginItr = itr;
        while(beginItr != m_buffer_ptr->end()){
            if(*beginItr == find[0]){
                auto someItr = beginItr;
                bool match = true;
                for(auto character:find){
                    if(someItr == m_buffer_ptr->end() || character != *someItr){
                        match = false;
                        break;
                    }
                    ++someItr;
                }
                if(match){
                    break;
                }
            }
            ++beginItr;
        }
        itr = beginItr;
        if(itr != m_buffer_ptr->end()){
            allIterators.push_back(itr);
            ++itr;
        }
    }

    for(auto wordItr:allIterators){
        auto endItr = wordItr;
        for(int q = 1; q <= find.size(); q++){
            ++endItr;
        }
        m_buffer_ptr->apply_tag_by_name("highlight", wordItr, endItr);
    }
}

void MainWindow::UnHighlightFindText(){
    m_buffer_ptr->remove_tag_by_name("highlight", m_buffer_ptr->begin(), m_buffer_ptr->end());
}

//------------------------------------------------------------------------------------------

//------------------------------------Render Function---------------------------------------

void MainWindow::Render(){
    set_default_size(800, 400);
    set_title("dit");
    body_box.set_homogeneous(false);

    m_buffer_tag_ptr->property_background() = "orange";
    m_buffer_tagtable_ptr->add(m_buffer_tag_ptr);


    AddAction("save", sigc::mem_fun(*this, &MainWindow::ActionSave));
    AddAction("open", sigc::mem_fun(*this, &MainWindow::ActionOpen));
    AddAction("saveas", sigc::mem_fun(*this, &MainWindow::ActionSaveAs));
    AddAction("new", sigc::mem_fun(*this, &MainWindow::ActionNew));
    AddAction("findreplace", sigc::mem_fun(*this, &MainWindow::ActionFindAndReplace));
    insert_action_group("menu", m_action_group_ptr);

    const char *ui_info = 
                            "<interface>"
                            "  <menu id='menubar'>"
                            "    <submenu>"
                            "      <attribute name='label' translatable='yes'>_File</attribute>"
                            "      <section>"
                            "        <item>"
                            "          <attribute name='label' translatable='yes'>_New</attribute>"
                            "          <attribute name='action'>menu.new</attribute>"
                            "          <attribute name='accel'>&lt;Primary&gt;n</attribute>"
                            "        </item>"
                            "        <item>"
                            "          <attribute name='label' translatable='yes'>_Open</attribute>"
                            "          <attribute name='action'>menu.open</attribute>"
                            "          <attribute name='accel'>&lt;Primary&gt;o</attribute>"
                            "        </item>"
                            "        <item>"
                            "          <attribute name='label' translatable='yes'>_Save</attribute>"
                            "          <attribute name='action'>menu.save</attribute>"
                            "          <attribute name='accel'>&lt;Primary&gt;s</attribute>"
                            "        </item>"
                            "        <item>"
                            "          <attribute name='label' translatable='yes'>_Save As</attribute>"
                            "          <attribute name='action'>menu.saveas</attribute>"
                            "          <attribute name='accel'>&lt;Primary&gt;a</attribute>"
                            "        </item>"
                            "      </section>"
                            "    </submenu>"
                            "    <submenu>"
                            "      <attribute name='label' translatable='yes'>_Tools</attribute>"
                            "      <section>"
                            "        <item>"
                            "          <attribute name='label' translatable='yes'>_Find and Replace</attribute>"
                            "          <attribute name='action'>menu.findreplace</attribute>"
                            "          <attribute name='accel'>&lt;Primary&gt;f</attribute>"
                            "        </item>"
                            "      </section>"
                            "    </submenu>"
                            "  </menu>"
                            "</interface>";    
                            
    m_builder->add_from_string(ui_info);

    auto object = m_builder->get_object("menubar");
    auto gmenu = Glib::RefPtr<Gio::Menu>::cast_dynamic(object);
    auto pMenuBar = Gtk::make_managed<Gtk::MenuBar>(gmenu);

    menu_box.pack_start(*pMenuBar);

    body_box.pack_start(menu_box, Gtk::PACK_SHRINK);

    m_buffer_ptr->signal_changed().connect(sigc::mem_fun(*this, &MainWindow::OnTextChange));

    m_text.set_buffer(m_buffer_ptr);
    m_scroll.add(m_text);

    body_box.pack_start(m_scroll);
    m_scroll.show_all();
    
    body_box.show_all();
    add(body_box);
}

//-----------------------------------------------------------------------------------------