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

bool InitTable() {
  return Execute(
      "CREATE TABLE IF NOT EXISTS player ("
      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
      "name TEXT NOT NULL,"
      "password TEXT NOT NULL,"
      "score INTEGER NOT NULL,"
      ");");
}

Player* GetPlayer(const std::string& name) {
  sqlite3* db = GetDB();
  if (db == nullptr) {
    return nullptr;
  }
  sqlite3_stmt* stmt = nullptr;
  int rc = sqlite3_prepare_v2(db, "SELECT * FROM player WHERE name = ?;", -1,
                              &stmt, nullptr);
  if (rc != SQLITE_OK) {
    std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
    return nullptr;
  }
  sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
  rc = sqlite3_step(stmt);
  if (rc != SQLITE_ROW) {
    std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
    sqlite3_finalize(stmt);
    return nullptr;
  }
  int id = sqlite3_column_int(stmt, 0);
  // std::string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt,
  // 1));
  std::string password =
      reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
  int score = sqlite3_column_int(stmt, 3);
  sqlite3_finalize(stmt);
  return new Player(id, name, password, score);
}

std::vector<Player*> GetPlayers() {
  sqlite3* db = GetDB();
  if (db == nullptr) {
    return std::vector<Player*>();
  }
  sqlite3_stmt* stmt = nullptr;
  int rc = sqlite3_prepare_v2(db, "SELECT * FROM player;", -1, &stmt, nullptr);
  if (rc != SQLITE_OK) {
    std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
    return std::vector<Player*>();
  }
  std::vector<Player*> players;
  while (sqlite3_step(stmt) == SQLITE_ROW) {
    int id = sqlite3_column_int(stmt, 0);
    std::string name = (const char*)sqlite3_column_text(stmt, 1);
    std::string password = (const char*)sqlite3_column_text(stmt, 2);
    int score = sqlite3_column_int(stmt, 3);
    players.push_back(new Player(id, name, password, score));
  }
  sqlite3_finalize(stmt);
  return players;
}

}  // namespace db
}  // namespace bjw
