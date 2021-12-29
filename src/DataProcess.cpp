//
// Created by AAA on 2021/12/25.
//

#include "DataProcess.h"

bjw::DataProcess::DataProcess() {
  fin_list.clear();
}

void bjw::DataProcess::PrePareData(bjw::fin_group fin_obj, int count) {
  fin_list[count].emplace_back(fin_obj);
}
