#include "GameJudge.h"

namespace bjw {

// 处理玩家移子操作
// 接收数据格式：(x1, y1) (x2, y2) 对应两子交换前坐标
void GameJudge::PdDeleteItem(int x1, int y1, int x2, int y2) {
  int count = 0;
  std::vector<doGroup> doPdList;
  std::vector<std::vector<bingoGroup>> bingoList;

  swapDataInMap(x1, y1, x2, y2);

  doPdList.emplace_back(x1, y1);
  doPdList.emplace_back(x2, y2);

  while (!doPdList.empty()) {
    int beforeSize = doPdList.size();

    for (int i = 0; i < beforeSize; ++i) {
      bingoGroup bgGTemp;
      FindLengthMore3(doPdList[i].x, doPdList[i].y, bgGTemp);
      if (bgGTemp.noInitFlag) {
        bingoList[count].push_back(bgGTemp);

        int b_start_x, b_start_y, b_end_x, b_end_y;
        b_start_x = bgGTemp.start_x;
        b_start_y = bgGTemp.start_y;
        b_end_x = bgGTemp.end_x;
        b_end_y = bgGTemp.end_y;

        if (b_start_x == b_end_x) {
          for (int j = b_start_y; j <= b_end_y; ++j) {
            doPdList.emplace_back(b_start_x, j);
          }
        } else {
          for (int j = b_start_x; j <= b_end_x; ++j) {
            doPdList.emplace_back(j, b_start_y);
          }
        }
      }
    }

    RebuildMap(bingoList[count]);

    for (int i = 0; i < beforeSize; ++i) {
      doPdList.erase(doPdList.begin());
    }

    count++;
  }

  SendData(bingoList);
}

// 向UI传输数据
void GameJudge::SendData(std::vector<std::vector<bingoGroup>> bingoList) {
  // TODO  接口协商  emit函数注册
}

bool GameJudge::FindLengthMore3(int x, int y, bingoGroup &bgG) {
  int sum = 0;
  int target_color = game_map[x][y].GetColorId();
  int start_x, end_x, start_y, end_y;
  start_x = end_x = x;
  start_y = end_y = y;

  // 上下左右四方向前进
  sum += MapDfs(x + 1, y, target_color, start_x, start_y, end_x, end_y);
  sum += MapDfs(x, y + 1, target_color, start_x, start_y, end_x, end_y);
  sum += MapDfs(x - 1, y, target_color, start_x, start_y, end_x, end_y);
  sum += MapDfs(x, y - 1, target_color, start_x, start_y, end_x, end_y);

  // 大于3 代表可以消去
  if (sum > 3) {
    bgG.set(start_x, end_x, start_y, end_y);
    return true;
  } else {
    return false;
  }
}

// dfs递归求可消坐标
int GameJudge::MapDfs(int now_x, int now_y, int target_color, int &t_min_x,
                      int &t_min_y, int &t_max_x, int &t_max_y) {
  // 越界0
  if (now_x < 0 || now_y < 0 || now_x >= MAXSIZE || now_y >= MAXSIZE) {
    return 0;
  }

  // 非匹配0
  if (game_map[now_x][now_y].GetColorId() != target_color) {
    return 0;
  }

  // 匹配状况时
  int sum = 1;
  if (now_x < t_min_x) t_min_x = now_x;
  if (now_y < t_min_y) t_min_y = now_y;
  if (now_x > t_max_x) t_max_x = now_x;
  if (now_y > t_max_y) t_max_y = now_y;

  // 上下左右四方向前进
  sum += MapDfs(now_x + 1, now_y, target_color, t_min_x, t_min_y, t_max_x,
                t_max_y);
  sum += MapDfs(now_x, now_y + 1, target_color, t_min_x, t_min_y, t_max_x,
                t_max_y);
  sum += MapDfs(now_x - 1, now_y, target_color, t_min_x, t_min_y, t_max_x,
                t_max_y);
  sum += MapDfs(now_x, now_y - 1, target_color, t_min_x, t_min_y, t_max_x,
                t_max_y);

  return sum;
}

// 交换地图内元素
void GameJudge::swapDataInMap(int x1, int y1, int x2, int y2) {
  Item temp_item(game_map[x1][y1]);
  game_map[x1][y1] = game_map[x2][y2];
  game_map[x2][y2] = temp_item;
}

// 根据目标List重构地图
void GameJudge::RebuildMap(std::vector<bingoGroup> bingoList) {
  for (int i = 0; i < bingoList.size(); ++i) {
    int b_start_x, b_start_y, b_end_x, b_end_y;
    b_start_x = bingoList[i].start_x;
    b_start_y = bingoList[i].start_y;
    b_end_x = bingoList[i].end_x;
    b_end_y = bingoList[i].end_y;

    if (b_start_x == b_end_x) {
      RebuildMapBasic(b_start_y, b_end_y, b_start_x, false);
    } else {
      RebuildMapBasic(b_start_x, b_end_x, b_start_y, true);
    }
  }
}
void GameJudge::RebuildMapBasic(int start, int end, int level, bool heading) {
  // heading   为真横向  为假纵向
  if (heading) {
  } else {
  }
}

}  // namespace bjw
