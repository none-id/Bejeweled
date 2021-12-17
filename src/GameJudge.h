#ifndef BEJEWELED_GAMEJUDGE_H
#define BEJEWELED_GAMEJUDGE_H

#include <algorithm>
#include <cstdlib>
#include <vector>

#include "Item.h"

#define MAXSIZE 10

namespace bjw {

class GameJudge {
 private:
  std::vector<std::vector<Item>> game_map;  // TODO 实现建图

  void FindLengthMore3(int, int, int &);
  int MapDfs(int, int, int, int &, int &, int &, int &);
  void SendData();

 public:
  void PdDeleteItem(int, int, int, int);
};

}  // namespace bjw
#endif  // BEJEWELED_GAMEJUDGE_H
