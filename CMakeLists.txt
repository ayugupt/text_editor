cmake_minimum_required(VERSION 3.10)

project(DIT VERSION 1.0)
configure_file(config.h.in config.h)

add_subdirectory(src)

add_executable(dit main.cpp)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)

target_include_directories(dit PUBLIC "${PROJECT_BINARY_DIR}"
                                        "${PROJECT_SOURCE_DIR}/src"
                                        ${GTKMM_INCLUDE_DIRS})
                                        
target_link_libraries(dit PUBLIC ${GTKMM_LIBRARIES}
                                 src)

target_compile_options(dit PUBLIC ${GTKMM_CFLAGS_OTHER})