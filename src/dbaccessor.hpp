#ifndef DBACCESSOR_HPP
#define DBACCESSOR_HPP

class sqlite3;
class sqlite3_stmt;

class DBAccessor {
public:
	static bool open(const char*);
	static void close();
protected:
	sqlite3_stmt* createStatement(const char* query);
public:
	static bool init;
	static sqlite3* db;
};

#endif // DBACCESSOR_HPP
