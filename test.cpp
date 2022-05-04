#include<fstream>
#include<iostream>
#include<string>

int main(){
    // std::ifstream readFile{"test.txt", std::ios::binary | std::ios::in};
    // std::ofstream writeFile{"copy.txt", std::ios::binary | std::ios::out};
    // readFile.seekg(0, std::ios::end);
    // auto lastg = readFile.tellg();
    // readFile.seekg(0, std::ios::beg);
    // while(readFile.tellg() != lastg){
    //     char buffer;
    //     readFile.read(&buffer, sizeof(buffer));
    //     writeFile.write((const char*)&buffer, sizeof(buffer));
    // }

    // readFile.close();
    // writeFile.close();

    std::fstream both{"original.txt", std::ios::app | std::ios::in};
    // std::string getStr;
    // both>>getStr;
    // both.seekp(0, std::ios::beg);
    // std::ofstream deletee{"test.txt"};
    // deletee.close();
    // both<<std::string{"hello"};
    both.close();
}