#pragma once

#include "CardDeck.hpp"

class Player
{
private:
  std::string name;
  int envido_value;
  bool has_flower;
  bool can_raise_value;
  CardDeck cards;
public:
  Player();
  Player(CardDeck& cards, std::string name);
  ~Player();

  // Getters
  std::string get_name();
  int get_envido_value();
  bool get_has_flower();
  bool get_can_raise_value();

  int calculate_envido(Card& vira);
  bool calculate_flower(Card& vira);
  void play_card(Card& card);
  
  void set_cards(CardDeck& cards, Card& vira);
};
