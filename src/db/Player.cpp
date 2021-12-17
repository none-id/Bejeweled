#include "Player.h"

#include <utility>

namespace bjw {

Player::Player(std::string username, std::string password)
    : username(std::move(username)), password(std::move(password)), score(0) {}

void Player::SetScore(unsigned long long int score) { Player::score = score; }

unsigned long long int Player::GetScore() const { return score; }

}  // namespace bjw