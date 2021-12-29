#include "GameJudge.h"

namespace bjw {

// 处理玩家移子操作
// 接收数据格式：(x1, y1) (x2, y2) 对应两子交换前坐标
void GameJudge::PdDeleteItem(int x1, int y1, int x2, int y2) {
  std::vector<do_group> next_pd_list;  // 存储 需要判断的位置
  std::vector<bingo_group> bingo_list;  // 存储 对应UI的子最终操作 消去和下落
  data_obj = new DataProcess;
  count = 0;

  SwapDataInMap(x1, y1, x2, y2);

  next_pd_list.emplace_back(x1, y1);
  next_pd_list.emplace_back(x2, y2);

  // 处理全部需要判断的子  包括可能由于消去后新生成子仍需判断的部分
  while (!next_pd_list.empty()) {
    int beforeSize = next_pd_list.size();  // 记录该时刻时对应的list长度

    for (int i = 0; i < beforeSize; ++i) {
      bingo_group bg_temp;
      if (FindLengthMore3(next_pd_list[i].x, next_pd_list[i].y,
                          bg_temp)) {  // 若发现可以消去子
        bingo_list.push_back(bg_temp);  // 存入bingo_list等待UI数据部分传输

        int b_start_x, b_start_y, b_end_x, b_end_y;
        b_start_x = bg_temp.start_x;
        b_start_y = bg_temp.start_y;
        b_end_x = bg_temp.end_x;
        b_end_y = bg_temp.end_y;

        // 根据横竖 消去子后 下落部分的边缘需要重新判断
        if (b_start_x == b_end_x) {  // x起止位置相等 该次消去为竖消
          // 竖消只需对该次操作 对应列的全部子 进行修改即可
          for (int j = b_end_y; j >= 1; --j) {
            next_pd_list.emplace_back(b_start_x, j);
          }
        } else {
          // 横消需要判断 落子区域的 外围部分 可能性
          for (int j = b_start_x; j <= b_end_x; ++j) {
            next_pd_list.emplace_back(j, b_start_y);
            next_pd_list.emplace_back(j, 1);
          }
          for (int j = 2; j <= b_start_y - 1; ++j) {
            next_pd_list.emplace_back(b_start_x, j);
            next_pd_list.emplace_back(b_end_x, j);
          }
        }
      }
    }

    // 重构新地图及分数判定
    // TODO 查看ScorePlus中的TODO
    RebuildMap(bingo_list);
    ScorePlus(bingo_list);
    bingo_list.clear();  // 清空当前bingo_list以供后用

    // 将该时刻处理过的判断位置  从仍需判断列表删去
    for (int i = 0; i < beforeSize; ++i) {
      next_pd_list.erase(next_pd_list.begin());
    }

    // 时刻计数+2
    count += 2;
  }
}

// 向UI传输数据
void GameJudge::SendData(
    std::vector<std::vector<bingo_group>> draw_acting_list) {
  // TODO  接口协商  emit函数注册
}

bool GameJudge::FindLengthMore3(int x, int y, bingo_group &bgG) {
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
int GameJudge::MapDfs(int now_x, int now_y, int target_color, int &t_min_x,
                      int &t_min_y, int &t_max_x, int &t_max_y) {
  // 越界0
  if (now_x < 1 || now_y < 1 || now_x > board || now_y > board) {
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
void GameJudge::SwapDataInMap(int x1, int y1, int x2, int y2) {
  Item temp_item(game_map[x1][y1]);
  game_map[x1][y1] = game_map[x2][y2];
  game_map[x2][y2] = temp_item;
}

// 根据目标List重构地图
void GameJudge::RebuildMap(std::vector<bingo_group> bingoList) {
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

// 重构地图
void GameJudge::RebuildMapBasic(int start, int end, int level, bool heading) {
  // heading   为真横向  为假纵向
  if (heading) {
    for (int i = start; i <= end; ++i) {
      fin_group fg_clear(i, level, 0, 0);
      fin_group fg_drop(i, level, 1, 1);
      data_obj->PrePareData(fg_clear, count);
      data_obj->PrePareData(fg_drop, count + 1);
    }

    // TODO 调用建图方法 更新地图空缺位置
  } else {
    for (int i = start; i <= end; ++i) {
      fin_group fg_clear(level, i, 0, 0);
      data_obj->PrePareData(fg_clear, count);
    }

    fin_group fg_drop(level, start, 1, 1);
    data_obj->PrePareData(fg_drop, count + 1);

    // TODO 调用建图方法 更新地图空缺位置
  }
}

void GameJudge::ScorePlus(std::vector<bingo_group> bingo_list) {
  double sum_temp = 0;

  for (auto i : bingo_list) {
    int num = i.end_y - i.start_y + i.end_x - i.start_x;
    sum_temp +=
        num * (1 + (count - 1) * 0.1);  // combo加分  第一次1x 第二次1.1x  类推
  }

  now_score += sum_temp;

  // TODO  UI更新成绩数据
}

}  // namespace bjw
