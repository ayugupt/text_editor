# dit - Text Editor

This is a text editor which allows users to create new text files, open existing text files and save text files. Users can also search for words 
in the document. It has been developed using C++ with the gtkmm-3.0 library. Cmake has been used to compile the project.

![Text_Editor1](https://raw.githubusercontent.com/ayugupt/text_editor/master/images/ssq.png)
![Text_Editor2](https://raw.githubusercontent.com/ayugupt/text_editor/master/images/ss2.png)

# Build Instructions

Make sure you have the gtkmm-3.0 libraries and header files installed. If not follow the instructions [here](https://www.gtkmm.org/en/download.html) 

1. Go to the root directory of the project
2. mkdir build && cd build
3. cmake ..
4. Run the build command specific to your platform. For unix systems it will be: make
5. ./dit
