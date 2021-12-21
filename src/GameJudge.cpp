#include "GameJudge.h"

namespace bjw {

// 处理玩家移子操作
// 接收数据格式：(x1, y1) (x2, y2) 对应两子交换前坐标
void GameJudge::PdDeleteItem(int x1, int y1, int x2, int y2) {
  int bingoNums = 0;
  bingoGroup bgGFirst, bgGSecond;
  std::vector<doGroup> doPdList;

  swapDataInMap(x1, y1, x2, y2);

  doPdList.emplace_back(x1, y1);
  doPdList.emplace_back(x2, y2);

  // TODO 实现每次以时间点为界限 发送对应修改后子集合
  while (!doPdList.empty() || bingoNums == 0) {
    switch (bingoNums) {
      case 0:
        // TODO 反馈非成功消去状态
        break;
      case 1:
        if (bgGFirst.noInitFlag) {
        } else {
        }
        // TODO 反馈单一成功消去状态
        break;
      case 2:

        break;
      default:
        throw -1;
    }

    bingoNums += FindLengthMore3(x1, y1, bgGFirst);
    bingoNums += FindLengthMore3(x2, y2, bgGSecond);
  }
}

// 向UI传输数据
void GameJudge::SendData() {
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
}  // namespace bjw
