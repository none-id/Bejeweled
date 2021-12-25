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
  bool no_init_flag = false;
  node();
  node(int startX, int endX, int startY, int endY) {
    this->start_x = startX;
    this->end_x = endX;
    this->start_y = startY;
    this->end_y = endY;
    no_init_flag = true;
  }
  void set(int startX, int endX, int startY, int endY) {
    this->start_x = startX;
    this->end_x = endX;
    this->start_y = startY;
    this->end_y = endY;
    no_init_flag = true;
  }
  bool operator==(node &a) const {
    return a.start_x == start_x && a.end_x == end_x && a.start_y == start_y &&
           a.end_y == end_y;
  }
} bingo_group;

typedef struct node1 {
  int x, y;
  node1();
  node1(int x, int y);

} do_group;

class GameJudge {
 private:
  std::vector<std::vector<Item>> game_map;  // TODO 实现建图

  bool FindLengthMore3(int, int, bingo_group &);
  int MapDfs(int, int, int, int &, int &, int &, int &);
  void SendData(std::vector<std::vector<bingo_group>>);
  void SwapDataInMap(int x1, int y1, int x2, int y2);
  void FillInDataList(bingo_group);
  void RebuildMap(std::vector<bingo_group>);
  void RebuildMapBasic(int start, int end, int level, bool heading);

 public:
  void PdDeleteItem(int, int, int, int);
};

}  // namespace bjw
#endif  // BEJEWELED_GAMEJUDGE_H
