#ifndef BEJEWELED_DB_H
#define BEJEWELED_DB_H

#include <sqlite3.h>

#include <functional>
#include <iostream>

#include "Player.h"

namespace bjw {
namespace db {

sqlite3* GetDB();
bool CloseDB();

}  // namespace db
}  // namespace bjw
#endif  // BEJEWELED_DB_H
