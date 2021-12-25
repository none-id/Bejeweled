//
// Created by AAA on 2021/12/25.
//

#ifndef BEJEWELED_DATAPROCESS_H
#define BEJEWELED_DATAPROCESS_H

#include "GameJudge.h"

namespace bjw {
typedef struct node2 {
  int x, int y;
  bjw::Item now_item;
  int cond_flag = -1;  // -1 初值  0 消去  1 下落  2 新增并下落
                       // 该值为0或1时Item无用  为2时读取Item值并绘制
  int act_flag =
      -1;  // -1 初值  0 单点 (此时(x,y)指定一个对应地图内)
           //          1 单纵 (此时x指代对应列位置  y指代该列起始操作的行位置
           //          对应操作区间为[x~边缘])
  node2();
  node2(int x, int y, int cond_flag, int act_flag) {
    this.x = x;
    this.y = y;
    this.cond_flag = cond_flag;
    this.act_flag = act_flag;
  }
} fin_group;

class DataProcess {
 private:
  std::vector<std::vector<fin_group>> fin_list;

 public:
  DataProcess();
  void PrePareData(fin_group, int);
};

}  // namespace bjw

#endif  // BEJEWELED_DATAPROCESS_H

// https://www.youtube.com/watch?v=2gm1as_h_ds
