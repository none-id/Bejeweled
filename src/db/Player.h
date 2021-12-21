#ifndef BEJEWELED_PLAYER_H
#define BEJEWELED_PLAYER_H

#include <string>

namespace bjw {

class Player {
 private:
  unsigned long long int id;
  std::string username;
  std::string password;
  unsigned long long int score;

 public:
  Player(unsigned long long int id, std::string username, std::string password,
         unsigned long long int score);
  bool VerifyPassword(std::string password) const;
  unsigned long long int GetScore() const;
  void SetScore(unsigned long long int score);
};

}  // namespace bjw

#endif  // BEJEWELED_PLAYER_H
