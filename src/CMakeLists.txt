add_library(src MainWindow.cpp MainWindow.h FileClass.cpp FileClass.h FileFunctions.cpp FileFunctions.h FindAndReplaceDialog.cpp FindAndReplaceDialog.h)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)

target_include_directories(src PUBLIC ${GTKMM_INCLUDE_DIRS})
                                        
target_link_libraries(src PUBLIC ${GTKMM_LIBRARIES})

target_compile_options(src PUBLIC ${GTKMM_CFLAGS_OTHER})