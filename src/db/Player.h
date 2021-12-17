#ifndef BEJEWELED_PLAYER_H
#define BEJEWELED_PLAYER_H

#include <string>

namespace bjw {

class Player {
 private:
  std::string username;
  std::string password;
  unsigned long long int score;

 public:
  Player(std::string username, std::string password);
  void SetScore(unsigned long long int score);
  unsigned long long int GetScore() const;
};

}  // namespace bjw

#endif  // BEJEWELED_PLAYER_H
