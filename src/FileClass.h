#pragma once
#include<string>
#include<fstream>

class FileClass{

    std::string m_name;
    std::string m_filename;
    std::fstream m_stream;


public: 
    FileClass(const char *name);
    FileClass(const std::string &name);
    
    std::string Read();
    void Write(const std::string &input);
    void SaveAs(const char *name);

    bool IsOpen() const;

    std::string GetTheFileName() const;
    
    ~FileClass();
};