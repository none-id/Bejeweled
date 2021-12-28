//
// Created by AAA on 2021/12/24.
//

#include "MapBuild.h"

// TODO 地图生成 离散定义
bjw::Item bjw::MapBuild::GetGameMap() { return **game_map; }

bool bjw::MapBuild::CountForJudge(int level) {
  int board = level_board[level];
  bool visited_map[board][board];
  for (int i = 1; i <= board; ++i) {
    for (int j = 1; j <= board; ++j) {
      visited_map[i][j] = false;
    }
  }

  for (int i = 1; i <= board; ++i) {
    for (int j = 1; j <= board; ++j) {
      if (!visited_map[i][j]) {
        bingo_group bg_temp;
        if (FindLengthMore3(i, j, bg_temp)) {
        }
        visited_map[i][j] = true;
      }
    }
  }

  return false;
}

bool bjw::MapBuild::FindLengthMore3(int x, int y, bingo_group &bgG) {
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
    bgG.Set(start_x, end_x, start_y, end_y);
    return true;
  } else {
    return false;
  }
}

// dfs递归求可消坐标
int bjw::MapBuild::MapDfs(int now_x, int now_y, int target_color, int &t_min_x,
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

bjw::MapBuild::MapBuild() {
  game_map = new Item[MAXSIZE];  // TODO 二维数组定义
  level_board[1] = 6;
  level_board[2] = 8;
  level_board[3] = 12;
  level_discrete_range[1][0] = 0;
  level_discrete_range[1][1] = 30;
  level_discrete_range[2][0] = 30;
  level_discrete_range[2][1] = 60;
  level_discrete_range[3][0] = 60;
  level_discrete_range[3][1] = 90;
}
