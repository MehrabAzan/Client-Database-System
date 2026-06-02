#include "Database.h"
#include <iostream>

sqlite3* Database::database = nullptr;

bool Database::Initialize(const std::string& databasePath) {
  if (database != nullptr) {
    return true;
  }

  if (sqlite3_open(databasePath.c_str(), &database) != SQLITE_OK) {
    std::cout << "Could not open database: " << sqlite3_errmsg(database) << std::endl;
    return false;
  }

  const char* schema =
    "PRAGMA foreign_keys = ON;"
    "CREATE TABLE IF NOT EXISTS clients ("
    "  email TEXT PRIMARY KEY,"
    "  first_name TEXT NOT NULL,"
    "  last_name TEXT NOT NULL,"
    "  address TEXT NOT NULL,"
    "  sales INTEGER NOT NULL"
    ");"
    "CREATE TABLE IF NOT EXISTS sales_representatives ("
    "  email TEXT PRIMARY KEY,"
    "  first_name TEXT NOT NULL,"
    "  last_name TEXT NOT NULL,"
    "  address TEXT NOT NULL,"
    "  sales INTEGER NOT NULL"
    ");"
    "CREATE TABLE IF NOT EXISTS products ("
    "  name TEXT PRIMARY KEY,"
    "  price INTEGER NOT NULL,"
    "  wattage INTEGER NOT NULL,"
    "  inverter_type TEXT NOT NULL,"
    "  battery TEXT NOT NULL,"
    "  sales INTEGER NOT NULL"
    ");"
    "CREATE TABLE IF NOT EXISTS sales ("
    "  id INTEGER PRIMARY KEY AUTOINCREMENT,"
    "  product_name TEXT NOT NULL,"
    "  client_first_name TEXT NOT NULL,"
    "  client_last_name TEXT NOT NULL,"
    "  sales_rep_first_name TEXT NOT NULL,"
    "  sales_rep_last_name TEXT NOT NULL,"
    "  month TEXT NOT NULL,"
    "  day INTEGER NOT NULL,"
    "  year INTEGER NOT NULL"
    ");";

  return Execute(schema);
}

sqlite3* Database::Connection() {
  return database;
}

bool Database::Execute(const char* sql) {
  char* errorMessage = nullptr;

  if (sqlite3_exec(database, sql, nullptr, nullptr, &errorMessage) != SQLITE_OK) {
    std::cout << "Database error: " << errorMessage << std::endl;
    sqlite3_free(errorMessage);
    return false;
  }

  return true;
}

bool Database::Prepare(const char* sql, sqlite3_stmt** statement, const std::string& action) {
  if (sqlite3_prepare_v2(database, sql, -1, statement, nullptr) != SQLITE_OK) {
    std::cout << "Database error while " << action << ": " << sqlite3_errmsg(database) << std::endl;
    return false;
  }

  return true;
}

bool Database::StepDone(sqlite3_stmt* statement, const std::string& action) {
  if (sqlite3_step(statement) != SQLITE_DONE) {
    std::cout << "Database error while " << action << ": " << sqlite3_errmsg(database) << std::endl;
    return false;
  }

  return true;
}

std::string Database::ColumnText(sqlite3_stmt* statement, int column) {
  const unsigned char* text = sqlite3_column_text(statement, column);
  return text == nullptr ? "" : reinterpret_cast<const char*>(text);
}

void Database::Close() {
  if (database != nullptr) {
    sqlite3_close(database);
    database = nullptr;
  }
}
