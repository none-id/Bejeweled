#include "Player.h"

#include <utility>

namespace bjw {

Player::Player(unsigned long long int id, std::string username,
               std::string password, unsigned long long int score)
    : id(id),
      username(std::move(username)),
      password(std::move(password)),
      score(score) {}

bool Player::VerifyPassword(std::string password) const {
  return Player::password == password;
}

void Player::SetScore(unsigned long long int score) { Player::score = score; }

unsigned long long int Player::GetScore() const { return score; }

}  // namespace bjw
