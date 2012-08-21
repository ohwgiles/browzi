cmake_minimum_required(VERSION 2.6)
project(browzi)

find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

set(SOURCES main.cpp mainwindow.cpp rowedlist.cpp searchpanel.cpp
	searchdraw.cpp searchpinyin.cpp searchenglish.cpp searchradical.cpp
	searchstrokecount.cpp characterdisplaypanel.cpp scribblearea.cpp strokesmatcher.cpp writtencharacter.cpp writtenstroke.cpp writtenpoint.cpp)

set(HEADERS mainwindow.hpp rowedlist.hpp searchpanel.hpp searchdraw.hpp
	searchpinyin.hpp searchenglish.hpp searchradical.hpp searchstrokecount.hpp
	characterdisplaypanel.hpp scribblearea.h)

qt4_wrap_cpp(MOCS ${HEADERS})
qt4_add_resources(RCC resources.qrc)

FIND_PACKAGE(PkgConfig)
PKG_CHECK_MODULES(GLIB2 glib-2.0)
add_definitions(${GLIB2_CFLAGS})

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_BINARY_DIR})

add_definitions(-O0 -g)

add_executable(browzi ${SOURCES} ${HEADERS} ${MOCS} ${RCC})
target_link_libraries(browzi ${QT_LIBRARIES} glib-2.0 Unihan)
