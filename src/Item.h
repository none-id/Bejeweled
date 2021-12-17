#ifndef BEJEWELED_ITEM_H
#define BEJEWELED_ITEM_H

#include <string>

namespace bjw {

typedef enum { red, blue, green } Color;

class Item {
 private:
  std::string color_name;  // 该子颜色string  用于文件读写
  int color_id;            // 该子颜色int  用于程序判断
  int item_id;             // 该子id标识

  static int ColorString2Rank(std::string color_name);

 public:
  int cond;  // 代表该子状态   -1初始化  0不变   1消除  2新增
  int GetColorId();
  Item(std::string color_name);
};

}  // namespace bjw
#endif  // BEJEWELED_ITEM_H
