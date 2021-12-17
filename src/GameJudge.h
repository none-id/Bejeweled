//
// Created by AAA on 2021/12/16.
//

#ifndef BEJEWELED_GAMEJUDGE_H
#define BEJEWELED_GAMEJUDGE_H

#include <algorithm>
#include <cstdlib>
#include <vector>

#include "Item.h"

#define MAXSIZE 10

class GameJudge {
 private:
  std::vector<std::vector<Item>> gameMap; // TODO 实现建图

  void findLenthMore3(int, int, int &);
  int mapDFS(int, int, int, int&, int&, int&, int&);
  void sendData();

 public:
  void pdDeleteItem(int, int, int, int);
};

#endif  // BEJEWELED_GAMEJUDGE_H
