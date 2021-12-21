#ifndef BEJEWELED_PLAYER_H
#define BEJEWELED_PLAYER_H

#include <string>

namespace bjw {

class Player {
 private:
  const unsigned long long int id;
  const std::string username;
  const std::string password;
  const unsigned long long int score;

 public:
  Player(unsigned long long int id, std::string username, std::string password,
         unsigned long long int score);
  unsigned long long int getId() const;
  bool VerifyPassword(const std::string &password) const;
  unsigned long long int GetScore() const;
};

}  // namespace bjw

#endif  // BEJEWELED_PLAYER_H
