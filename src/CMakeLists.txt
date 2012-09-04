# BROWZI
cmake_minimum_required(VERSION 2.6)
project(browzi)

# Version info
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "3")
set(VERSION ${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR})
file(WRITE "${CMAKE_BINARY_DIR}/version.h.txt" "#define BROWZI_VERSION \"${VERSION}\"")
add_custom_command(OUTPUT version.h
	COMMAND ${CMAKE_COMMAND} -E copy_if_different
	${CMAKE_BINARY_DIR}/version.h.txt ${CMAKE_BINARY_DIR}/version.h
	DEPENDS ${CMAKE_BINARY_DIR}/version.h.txt)

# Find Qt
find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

# This would be great, but can't unzip it in CMake!
# if(WIN32)
#  file(DOWNLOAD http://www.sqlite.org/sqlite-dll-win32-x86-3071300.zip
#   SHOW_PROGRESS EXPECTED_MD5 61582290923dc9a0d79a080080e0e338)
#  dlltool -D sqlite3.dll -d sqlite3.def -l libsqlite3.a
# endif()

# Find Sqlite3. On windows, drop libsqlite3.a into the build dir
find_library(SQLITE3_LIB NAMES sqlite3 HINTS ${CMAKE_BINARY_DIR})

# Find the Unihan db. On windows, drop Unihan.db into the build dir
find_file(UNIHAN_DB NAMES Unihan.db PATHS ${CMAKE_BINARY_DIR})

# Sources and headers
set(SOURCES 
	characterdisplaypanel.cpp
	clipboard.cpp
   dbaccessor.cpp
   main.cpp
   mainwindow.cpp
	pinyin.cpp
   rowedlist.cpp
   scribblearea.cpp
   searchdraw.cpp
   searchenglish.cpp
   searchpanel.cpp
   searchpinyin.cpp
   searchradical.cpp
   searchstrokecount.cpp
   strokesmatcher.cpp
   writtencharacter.cpp
   writtenpoint.cpp
   writtenstroke.cpp
)
set(HEADERS
	characterdisplaypanel.hpp
	clipboard.hpp
	mainwindow.hpp
	rowedlist.h
	scribblearea.h
	searchdraw.hpp
	searchenglish.hpp
	searchpanel.hpp
	searchpinyin.hpp
	searchradical.hpp
	searchstrokecount.hpp
)

# Generate extra sources from Qt objects
qt4_wrap_cpp(MOCS ${HEADERS})
qt4_add_resources(RCC resources.qrc)

include_directories(${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR})

# Debug
add_definitions(-O0 -g)
# Release
# add_definitions(-O3)

# If we have ImageMagick, create the icon from the svg.
# Otherwise you can drop icon.ico into the build directory.
find_package(ImageMagick QUIET)
if(ImageMagick_FOUND)
 foreach(ICON_SIZE 16x16 32x32 48x48 64x64 128x128 256x256)
  add_custom_command(OUTPUT icon_${ICON_SIZE}.png
	 COMMAND ${ImageMagick_CONVERT_EXECUTABLE}
	 ARGS -flatten -channel RGBA -colorspace RGB -geometry ${ICON_SIZE}
			-background none -quality 80 -depth 8
			${CMAKE_SOURCE_DIR}/icon.svg icon_${ICON_SIZE}.png DEPENDS icon.svg)
  list(APPEND ICON_FILES icon_${ICON_SIZE}.png)
 endforeach()
 add_custom_command(OUTPUT icon.ico
	 COMMAND convert ${ICON_FILES} icon.ico DEPENDS ${ICON_FILES})
 add_custom_target(icon DEPENDS icon.ico)
endif()

# On Windows, embeded the icon as a resources
if(WIN32)
 find_program(WINDRES windres.exe REQUIRED)
 add_custom_command(OUTPUT icon.o
	 COMMAND ${WINDRES} ${CMAKE_SOURCE_DIR}/win_icon.rc icon.o
	 DEPENDS win_icon.rc ${CMAKE_BINARY_DIR}/icon.ico)
 set(EXTRA_SOURCES ${CMAKE_BINARY_DIR}/icon.o)
endif()

# Create the executable!
add_executable(browzi ${SOURCES} ${MOCS} ${RCC} ${EXTRA_SOURCES} ${CMAKE_BINARY_DIR}/version.h)
target_link_libraries(browzi ${QT_LIBRARIES} ${SQLITE3_LIB})

# ------------------- PACKAGING

set(CPACK_STRIP_FILES ON)
INCLUDE(InstallRequiredSystemLibraries)
# Package description and copyright
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Browzi is a Hanzi browser")
set(CPACK_PACKAGE_VENDOR "Oliver Giles")
#set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_SOURCE_DIR}/DESCRIPTION")
#set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/COPYING")
set(CPACK_PACKAGE_EXECUTABLES "browzi;Browzi")

# Create the installer for Windows
if(WIN32)
 install(TARGETS browzi RUNTIME DESTINATION .)
 string(REPLACE "bin/qmake.exe" "lib/QtCore4.dll" QT_CORE_DLL ${QT_QMAKE_EXECUTABLE})
 string(REPLACE "bin/qmake.exe" "lib/QtGui4.dll" QT_GUI_DLL ${QT_QMAKE_EXECUTABLE})
 install(FILES
	 ${QT_CORE_DLL} ${QT_GUI_DLL}
	 ${UNIHAN_DB}
	 ${CMAKE_BINARY_DIR}/sqlite3.dll
	 ${CMAKE_BINARY_DIR}/libgcc_s_dw2-1.dll
	 ${CMAKE_BINARY_DIR}/mingwm10.dll
	 DESTINATION .)
 # This gets rid of the console window
 set_target_properties(browzi PROPERTIES WIN32_EXECUTABLE true)
 set(CPACK_NSIS_INSTALLED_ICON_NAME "browzi.exe")
 set(CPACK_NSIS_DISPLAY_NAME "Browzi")
 set(CPACK_NSIS_HELP_LINK "https://github.com/ohwgiles/browzi")
 set(CPACK_NSIS_URL_INFO_ABOUT "https://github.com/ohwgiles/browzi")
 set(CPACK_NSIS_CREATE_ICONS "CreateShortCut '\$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\Browzi.lnk' '\$INSTDIR\\\\browzi.exe'")
 set(CPACK_STRIP_FILES "browzi.exe")
 set(CPACK_MODULE_PATH ${CMAKE_SOURCE_DIR})
 set(CPACK_GENERATOR "NSIS")
endif(WIN32)
include(CPack)
