#include "Item.h"

namespace bjw {

Item::Item(std::string color_name) {
  this->color_name = color_name;
  color_id = ColorString2Rank(color_name);
  cond = -1;
}

int Item::ColorString2Rank(std::string color_name) {
  if (color_name == "red")
    return red;
  else if (color_name == "blue")
    return blue;
  else if (color_name == "green")
    return green;
  return -1;
}

int Item::GetColorId() { return color_id; }

}  // namespace bjw
