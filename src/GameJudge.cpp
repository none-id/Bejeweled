//
// Created by AAA on 2021/12/16.
//

#include "GameJudge.h"

// 处理玩家移子操作
void GameJudge::pdDeleteItem(int x1, int y1, int x2, int y2) {
  int flag = 0;
  findLenthMore3(x1, y1, flag);
  findLenthMore3(x2, y2, flag);
}

// 向UI传输数据
void GameJudge::sendData() {
  // TODO  接口协商  emit函数注册
}

void GameJudge::findLenthMore3(int x, int y, int &flag) {
  int sum = 0;
  int targetColor = gameMap[x][y].getColorID();
  int startX, endX, startY, endY;
  startX = endX = x;
  startY = endY = y;

  // 上下左右四方向前进
  sum += mapDFS(x + 1, y, targetColor, startX, startY, endX, endY);
  sum += mapDFS(x, y + 1, targetColor, startX, startY, endX, endY);
  sum += mapDFS(x - 1, y, targetColor, startX, startY, endX, endY);
  sum += mapDFS(x, y - 1, targetColor, startX, startY, endX, endY);

  // 大于3 代表可以消去
  if (sum > 3) {
    sendData();  // TODO 当前需消起止坐标传输
  }
}

// dfs递归求可消坐标
int GameJudge::mapDFS(int nowX, int nowY, int targetColor, int &tMinX,
                      int &tMinY, int &tMaxX, int &tMaxY) {
  // 越界0
  if (nowX < 0 || nowY < 0 || nowX >= MAXSIZE || nowY >= MAXSIZE) {
    return 0;
  }

  // 非匹配0
  if (gameMap[nowX][nowY].getColorID() != targetColor) {
    return 0;
  }

  // 匹配状况时
  int sum = 1;
  if (nowX < tMinX) tMinX = nowX;
  if (nowY < tMinY) tMinY = nowY;
  if (nowX > tMaxX) tMaxX = nowX;
  if (nowY > tMaxY) tMaxY = nowY;

  // 上下左右四方向前进
  sum += mapDFS(nowX + 1, nowY, targetColor, tMinX, tMinY, tMaxX, tMaxY);
  sum += mapDFS(nowX, nowY + 1, targetColor, tMinX, tMinY, tMaxX, tMaxY);
  sum += mapDFS(nowX - 1, nowY, targetColor, tMinX, tMinY, tMaxX, tMaxY);
  sum += mapDFS(nowX, nowY - 1, targetColor, tMinX, tMinY, tMaxX, tMaxY);

  return sum;
}
