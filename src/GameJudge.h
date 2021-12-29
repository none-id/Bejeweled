#ifndef BEJEWELED_GAMEJUDGE_H
#define BEJEWELED_GAMEJUDGE_H

#include <algorithm>
#include <cstdlib>
#include <vector>

#include "DataProcess.h"
#include "Item.h"
#include "MapBuild.h"

namespace bjw {
typedef struct node1 {
  int x, y;
  node1();
  node1(int x, int y);

} do_group;

class GameJudge {
 private:
  Item **game_map;  // TODO 实现建图  对象传送
  // TODO
  // 非常重要！以下所有地图坐标均以1起，(1,1)为左上角坐标，(n,n)为右下角坐标，坐标0位置录入null
  DataProcess *data_obj;
  int count;
  int board;  // TODO 地图边界需要传入
  double now_score = 0;

  bool FindLengthMore3(int, int, bingo_group &);
  int MapDfs(int, int, int, int &, int &, int &, int &);
  void SendData(std::vector<std::vector<bingo_group>>);
  void SwapDataInMap(int, int, int, int);
  void FillInDataList(bingo_group);
  void RebuildMap(std::vector<bingo_group>);
  void RebuildMapBasic(int, int, int, bool);
  void ScorePlus(std::vector<bingo_group>);

 public:
  void PdDeleteItem(int, int, int, int);
};

}  // namespace bjw
#endif  // BEJEWELED_GAMEJUDGE_H
