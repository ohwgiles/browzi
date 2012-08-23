#include "dbaccessor.hpp"
#include <sqlite3.h>

bool DBAccessor::init = false;
sqlite3* DBAccessor::db = 0;

bool DBAccessor::open(const char* path) {
	if(init) return false;

	if(sqlite3_open(path, &db) == SQLITE_OK)
		init = true;
	return init;
}

void DBAccessor::close() {
	if(!init) return;
	sqlite3_close(db);
}

sqlite3_stmt* DBAccessor::createStatement(const char *query) {
	sqlite3_stmt* stmt;
	sqlite3_prepare_v2(db, query, -1, &stmt, 0);
	return stmt;
}
