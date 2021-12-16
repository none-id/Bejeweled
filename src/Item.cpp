//
// Created by AAA on 2021/12/16.
//

#include "Item.h"

Item::Item(std::string colorName) {
  this->colorName = colorName;
  colorID = colorString2Rank(colorName);
  cond = -1;
}

int Item::colorString2Rank(std::string colorName) {
  if (colorName == "red")
    return red;
  else if (colorName == "blue")
    return blue;
  else if (colorName == "green")
    return green;
  return -1;
}

int Item::getColorID() { return colorID; }
