//
// Created by AAA on 2021/12/16.
//

#ifndef BEJEWELED_ITEM_H
#define BEJEWELED_ITEM_H

#include <string>

typedef enum {
  red, blue, green
} Color;

class Item {
 private:
  std::string colorName;   // 该子颜色string  用于文件读写
  int colorID;            // 该子颜色int  用于程序判断
  int itemID;             // 该子id标识

  static int colorString2Rank(std::string colorName);

 public:
  int cond;   // 代表该子状态   -1初始化  0不变   1消除  2新增
  int getColorID();
  Item(std::string);
};

#endif  // BEJEWELED_ITEM_H
