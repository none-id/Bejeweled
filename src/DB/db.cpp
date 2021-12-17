#include "db.h"

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

}  // namespace db
}  // namespace bjw
