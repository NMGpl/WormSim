#pragma once
#include "sqlite3.h"
#include <string>

class Database
{
	std::string name;
	int rc;
	sqlite3 *db;
	void init();
public:
	Database(const std::string& name);
	void connect();
	void disconnect();
	void execute(const std::string& query);
	void fetchData();
};

