#include "Database.h"

Database::Database(const std::string& name) {
	this->name = name;
	init();
}

void Database::init() {
	connect();
	execute("CREATE TABLE IF NOT EXISTS worm_stats (id_worm INTEGER PRIMARY KEY AUTOINCREMENT, zywe INTEGER, martwe INTEGER)");
	execute("CREATE TABLE IF NOT EXISTS food_stats (id_food INTEGER PRIMARY KEY AUTOINCREMENT, ilosc_jedzenia INTEGER)");
	execute("CREATE TABLE IF NOT EXISTS board_stats (id_board INTEGER PRIMARY KEY AUTOINCREMENT, puste_pola INTEGER, pelne_pola INTEGER, powierzchnia INTEGER)");
	disconnect();
}

void Database::connect() {
	this->rc = sqlite3_open(name.c_str(), &db);
}

void Database::disconnect() {
	sqlite3_close(db);
}

void Database::execute(const std::string& query) {
	int rc = sqlite3_exec(db, query.c_str(), nullptr, nullptr, nullptr);
}

void Database::fetchData() {
	//execute("SELECT * FROM worm_stats");
}