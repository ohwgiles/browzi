/**************************************************************************
 *
 *  main.cpp
 *  Copyright 2012 Oliver Giles
 *
 *  This file is part of Browzi.
 *
 *  Browzi is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Browzi is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Browzi.  If not, see <http://www.gnu.org/licenses/>.
 *
 **************************************************************************/
#include <QApplication>
#include "dbaccessor.hpp"
#include "mainwindow.hpp"

#ifdef __linux__
QString unihan_db_path() {
	return "/usr/share/UnihanDb/Unihan.db";
}
#endif

#ifdef _WIN32
#define UNICODE
#include <windows.h>
QString unihan_db_path() {
	wchar_t loc[MAX_PATH];
	GetModuleFileName(NULL, loc, MAX_PATH);
	QString result = QString::fromWCharArray(loc);
	int len = result.length();
	int slashPos = result.lastIndexOf('\\');
	result.replace(slashPos,len-slashPos,"\\Unihan.db");
	return result;
}
#endif

int main(int argc, char** argv) {
	DBAccessor::open(unihan_db_path().toUtf8());
	QApplication app(argc, argv);
	MainWindow m;
	m.show();
	app.exec();
	DBAccessor::close();
}
