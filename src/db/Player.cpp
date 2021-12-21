#include "Player.h"

#include <utility>

namespace bjw {

Player::Player(unsigned long long int id, std::string username,
               std::string password, unsigned long long int score)
    : id(id),
      username(std::move(username)),
      password(std::move(password)),
      score(score) {}

unsigned long long int Player::getId() const { return id; }

bool Player::VerifyPassword(const std::string &password) const {
  return Player::password == password;
}

unsigned long long int Player::GetScore() const { return score; }

}  // namespace bjw
