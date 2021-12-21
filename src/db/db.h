#ifndef BEJEWELED_DB_H
#define BEJEWELED_DB_H

#include <sqlite3.h>

#include <iostream>
#include <vector>

#include "Player.h"

namespace bjw {
namespace db {

sqlite3* GetDB();
bool CloseDB();
bool Execute(const std::string& sql);
bool InitTable();
Player* GetPlayer(const std::string& name);
std::vector<Player*> GetPlayers();

}  // namespace db
}  // namespace bjw

#endif  // BEJEWELED_DB_H
