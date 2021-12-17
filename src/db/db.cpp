#include "db.h"

#include "Player.h"

namespace bjw {
namespace db {

sqlite3* GetDB() {
  static sqlite3* db = nullptr;
  if (db == nullptr) {
    int rc = sqlite3_open("data/bjw.db", &db);
    if (rc != SQLITE_OK) {
      std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
      sqlite3_close(db);
      db = nullptr;
    }
  }
  return db;
}

bool CloseDB() {
  if (GetDB() == nullptr) {
    return false;
  }
  sqlite3_close(GetDB());
  return true;
}

bool Execute(const std::string& sql) {
  sqlite3* db = GetDB();
  if (db == nullptr) {
    return false;
  }
  char* errmsg = nullptr;
  int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errmsg);
  if (rc != SQLITE_OK) {
    std::cerr << "SQL error: " << errmsg << std::endl;
    sqlite3_free(errmsg);
    return false;
  }
  return true;
}

}  // namespace db
}  // namespace bjw
