//
// Created by AAA on 2021/12/24.
//

#ifndef BEJEWELED_MAPBUILD_H
#define BEJEWELED_MAPBUILD_H

#include "Item.h"

#define MAXSIZE 10

namespace bjw {
// 成功消去子的坐标存储结构
typedef struct node {
  int start_x, end_x, start_y, end_y;
  node();
  node(int startX, int endX, int startY, int endY) {
    this->start_x = startX;
    this->end_x = endX;
    this->start_y = startY;
    this->end_y = endY;
  }
  void Set(int startX, int endX, int startY, int endY) {
    this->start_x = startX;
    this->end_x = endX;
    this->start_y = startY;
    this->end_y = endY;
  }
  bool operator==(node &a) const {
    return a.start_x == start_x && a.end_x == end_x && a.start_y == start_y &&
           a.end_y == end_y;
  }
} bingo_group;

class MapBuild {
 private:
  Item **game_map;
  int level_discrete_range[4][2];
  int level_board[4];
  int level;
  int board;
  bool JudgeDiscretion();
  bool FindLengthMoreN(int, int, bingo_group &, int);
  int MapDfs(int, int, int, int &, int &, int &, int &);
  int CountProbalitiy(int, int, int, bool);

 public:
  Item GetGameMap();
  MapBuild(int);
};

}  // namespace bjw

#endif  // BEJEWELED_MAPBUILD_H
