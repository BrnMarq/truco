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
  std::string get_name() const;
  int get_envido_value() const;
  bool get_has_flower() const;
  bool get_can_raise_value() const;
  CardDeck get_cards() const;

  int calculate_envido(const Card& vira) ;
  bool calculate_flower(const Card& vira);
  void play_card(Card& card);
  
  void set_cards(const CardDeck& cards, const Card& vira);

  bool operator == (const Player& player) const noexcept;

  bool operator != (const Player& player) const noexcept;
};

struct PlayerHash
{
    size_t operator () (const Player& c) const noexcept;
};