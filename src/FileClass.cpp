#include "FileClass.h"
#include<fstream>
#include<iostream>
#include "FileFunctions.h"

FileClass::FileClass(const char *name): m_stream{name, std::ios::in | std::ios::app}{
    if(m_stream.is_open()){
        m_name = name;
        m_filename = GetFileName(name);
    }else{
        throw "File couldn't be opened";
    }
}

FileClass::FileClass(const std::string &name): m_stream{name, std::ios::in | std::ios::app}{
    if(m_stream.is_open()){
        m_name = name;
        m_filename = GetFileName(name);
    }else{
        throw "File couldn't be opened";
    }
}

std::string FileClass::Read(){
    if(IsOpen()){
        m_stream.seekg(0, std::ios::beg);
        std::string content{""};
        std::string temp;
        while(std::getline(m_stream, temp)){
            content = content + temp + "\n";
        }
        m_stream.clear();
        return content;
    }

    throw "File is not open";
}

void FileClass::Write(const std::string &input){
    if(IsOpen()){
        m_stream.seekp(0, std::ios::beg);
        std::ofstream deleteStream{m_name};
        deleteStream.close();

        m_stream<<input;
        m_stream.flush();
        m_stream.clear();
        
    }else{
        throw "No file is opened";
    }
    
}

void FileClass::SaveAs(const char *name){
    if(IsOpen()){
        std::ifstream originalFile{m_name, std::ios::binary | std::ios::in};
        std::ofstream newFile{name, std::ios::binary | std::ios::out};

        originalFile.seekg(0, std::ios::end);
        auto pointer_to_last = originalFile.tellg();
        originalFile.seekg(0, std::ios::beg);

        while(originalFile.tellg() != pointer_to_last){
            char buffer;
            originalFile.read(&buffer, sizeof(buffer));
            newFile.write((const char*)&buffer, sizeof(buffer));
        }

        originalFile.close();
        newFile.close();

        if(m_stream.is_open()){
            m_stream.close();
        }

        m_stream.open(name, std::ios::out | std::ios::in);
        m_name = name;
        m_filename = GetFileName(name);
    }else{
        throw "File is not open";
    }

}

bool FileClass::IsOpen() const{
    return m_stream.is_open();
}


std::string FileClass::GetTheFileName()const{
    return m_filename;
}

FileClass::~FileClass(){
    if(m_stream.is_open()){
        m_stream.close();
    }
}