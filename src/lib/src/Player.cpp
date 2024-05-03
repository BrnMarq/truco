#include "Player.hpp"

Player::Player() {
};

Player::Player(CardDeck& cards): cards{cards}
{
}

Player::~Player()
{
}

int Player::get_envido_value() {
  return envido_value;
};
  
bool Player::get_has_flower() {
  return has_flower;
};

bool Player::get_can_raise_value() {
  return can_raise_value;
};

// This function should calculate the envido based on which suit is the vira
int Player::calculate_envido(Card& vira) {
  return 0;
};

// This function should calculate if the player have flower or not
bool Player::calculate_flower(Card& vira) {
  return false;
};

// This function should remove the card that is being passed on from the cards list
void Player::play_card(Card& card) {

};

// This function should set the cards that are being passed, calculate the envido and calculate
// if the player has flower
void Player::set_cards(CardDeck& cards, Card& vira) {

};