#pragma once

#include <sqlite3.h>
#include <string>

class Database {
  public:
    static bool Initialize(const std::string& databasePath = "SeerSolar.db");
    static sqlite3* Connection();
    static bool Execute(const char* sql);
    static bool Prepare(const char* sql, sqlite3_stmt** statement, const std::string& action);
    static bool StepDone(sqlite3_stmt* statement, const std::string& action);
    static std::string ColumnText(sqlite3_stmt* statement, int column);
    static void Close();

  private:
    static sqlite3* database;
};
