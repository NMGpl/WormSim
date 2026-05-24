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

std::vector<std::vector<std::string>> Database::fetchData() {
    std::vector<std::vector<std::string>> data;

    std::string query =
        "SELECT w.zywe, w.martwe, "
        "f.ilosc_jedzenia, "
        "b.puste_pola, b.pelne_pola, b.powierzchnia "
        "FROM worm_stats w "
        "JOIN food_stats f "
        "JOIN board_stats b";

    sqlite3_stmt* stmt;

    sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        std::vector<std::string> row(6);

        row[0] = std::to_string(sqlite3_column_int(stmt, 0));
        row[1] = std::to_string(sqlite3_column_int(stmt, 1));
        row[2] = std::to_string(sqlite3_column_int(stmt, 2));
        row[3] = std::to_string(sqlite3_column_int(stmt, 3));
        row[4] = std::to_string(sqlite3_column_int(stmt, 4));
        row[5] = std::to_string(sqlite3_column_int(stmt, 5));

        data.push_back(row);
    }

    sqlite3_finalize(stmt);

    return data;
}