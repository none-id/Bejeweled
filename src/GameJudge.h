#ifndef BEJEWELED_GAMEJUDGE_H
#define BEJEWELED_GAMEJUDGE_H

#include <algorithm>
#include <cstdlib>
#include <vector>

#include "Item.h"

#define MAXSIZE 10

namespace bjw {

// 成功消去子的坐标存储结构
typedef struct node {
  int start_x, end_x, start_y, end_y;
  bool noInitFlag = false;
  node();
  node(int startX, int endX, int startY, int endY) {
    this->start_x = startX;
    this->end_x = endX;
    this->start_y = startY;
    this->end_y = endY;
    noInitFlag = true;
  }
  void set(int startX, int endX, int startY, int endY) {
    this->start_x = startX;
    this->end_x = endX;
    this->start_y = startY;
    this->end_y = endY;
    noInitFlag = true;
  }
  bool operator==(node &a) {
    return a.start_x == start_x && a.end_x == end_x && a.start_y == start_y &&
               a.end_y = end_y;
  }
} bingoGroup;

typedef struct node1 {
  int x, y;
  node1();
  node1(int x, int y);

} doGroup;

class GameJudge {
 private:
  std::vector<std::vector<Item>> game_map;  // TODO 实现建图

  bool FindLengthMore3(int, int, bingoGroup &);
  int MapDfs(int, int, int, int &, int &, int &, int &);
  void SendData();
  void swapDataInMap(int x1, int y1, int x2, int y2);

 public:
  void PdDeleteItem(int, int, int, int);
};

}  // namespace bjw
#endif  // BEJEWELED_GAMEJUDGE_H
