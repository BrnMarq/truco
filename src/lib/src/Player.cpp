#include "Player.hpp"
#include <map>

// As a general thought, take in mind that every member of the class Player is accesible
// in this functions, as if it were variables inside the functions

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

  std::map<std::tuple <Rank, Suit>, int> table_value;

  table_value[std::make_tuple(Rank::One, Suit::Clubs)] = 1;
  table_value[std::make_tuple(Rank::Two, Suit::Clubs)] = 2;
  table_value[std::make_tuple(Rank::Three, Suit::Clubs)] = 3;
  table_value[std::make_tuple(Rank::Four, Suit::Clubs)] = 4;
  table_value[std::make_tuple(Rank::Five, Suit::Clubs)] = 5;
  table_value[std::make_tuple(Rank::Six, Suit::Clubs)] = 6;
  table_value[std::make_tuple(Rank::Seven, Suit::Clubs)] = 7;
  table_value[std::make_tuple(Rank::Ten, Suit::Clubs)] = 0;
  table_value[std::make_tuple(Rank::Eleven, Suit::Clubs)] = 0;
  table_value[std::make_tuple(Rank::Twelve, Suit::Clubs)] = 0;
  table_value[std::make_tuple(Rank::One, Suit::Spades)] = 1;
  table_value[std::make_tuple(Rank::Two, Suit::Spades)] = 2;
  table_value[std::make_tuple(Rank::Three, Suit::Spades)] = 3;
  table_value[std::make_tuple(Rank::Four, Suit::Spades)] = 4;
  table_value[std::make_tuple(Rank::Five, Suit::Spades)] = 5;
  table_value[std::make_tuple(Rank::Six, Suit::Spades)] = 6;
  table_value[std::make_tuple(Rank::Seven, Suit::Spades)] = 7;
  table_value[std::make_tuple(Rank::Ten, Suit::Spades)] = 0;
  table_value[std::make_tuple(Rank::Eleven, Suit::Spades)] = 0;
  table_value[std::make_tuple(Rank::Twelve, Suit::Spades)] = 0;
  table_value[std::make_tuple(Rank::One, Suit::Golds)] = 1;
  table_value[std::make_tuple(Rank::Two, Suit::Golds)] = 2;
  table_value[std::make_tuple(Rank::Three, Suit::Golds)] = 3;
  table_value[std::make_tuple(Rank::Four, Suit::Golds)] = 4;
  table_value[std::make_tuple(Rank::Five, Suit::Golds)] = 5;
  table_value[std::make_tuple(Rank::Six, Suit::Golds)] = 6;
  table_value[std::make_tuple(Rank::Seven, Suit::Golds)] = 7;
  table_value[std::make_tuple(Rank::Ten, Suit::Golds)] = 0;
  table_value[std::make_tuple(Rank::Eleven, Suit::Golds)] = 0;
  table_value[std::make_tuple(Rank::Twelve, Suit::Golds)] = 0;
  table_value[std::make_tuple(Rank::One, Suit::Cups)] = 1;
  table_value[std::make_tuple(Rank::Two, Suit::Cups)] = 2;
  table_value[std::make_tuple(Rank::Three, Suit::Cups)] = 3;
  table_value[std::make_tuple(Rank::Four, Suit::Cups)] = 4;
  table_value[std::make_tuple(Rank::Five, Suit::Cups)] = 5;
  table_value[std::make_tuple(Rank::Six, Suit::Cups)] = 6;
  table_value[std::make_tuple(Rank::Seven, Suit::Cups)] = 7;
  table_value[std::make_tuple(Rank::Ten, Suit::Cups)] = 0;
  table_value[std::make_tuple(Rank::Eleven, Suit::Cups)] = 0;
  table_value[std::make_tuple(Rank::Twelve, Suit::Cups)] = 0;

  if(vira.get_suit() == Suit::Clubs && vira.get_rank() != Rank::Ten && vira.get_rank() != Rank::Eleven)
  {
    table_value[std::make_tuple(Rank::Ten, Suit::Clubs)] = 8;
    table_value[std::make_tuple(Rank::Eleven, Suit::Clubs)] = 9;
  }
  else if(vira.get_suit() == Suit::Clubs && vira.get_rank() == Rank::Ten)
  {
    table_value[std::make_tuple(Rank::Twelve, Suit::Clubs)] = 8;
    table_value[std::make_tuple(Rank::Eleven, Suit::Clubs)] = 9;
  }
  else if(vira.get_suit() == Suit::Clubs && vira.get_rank() == Rank::Eleven)
  {
    table_value[std::make_tuple(Rank::Twelve, Suit::Clubs)] = 9;
    table_value[std::make_tuple(Rank::Ten, Suit::Clubs)] = 8;
  }
  else if(vira.get_suit() == Suit::Golds && vira.get_rank() != Rank::Ten && vira.get_rank() != Rank::Eleven)
  {
    table_value[std::make_tuple(Rank::Ten, Suit::Golds)] = 8;
    table_value[std::make_tuple(Rank::Eleven, Suit::Golds)] = 9;
  }
  else if(vira.get_suit() == Suit::Golds && vira.get_rank() == Rank::Ten)
  {
    table_value[std::make_tuple(Rank::Twelve, Suit::Golds)] = 8;
    table_value[std::make_tuple(Rank::Eleven, Suit::Golds)] = 9;
  }
  else if(vira.get_suit() == Suit::Golds && vira.get_rank() == Rank::Eleven)
  {
    table_value[std::make_tuple(Rank::Twelve, Suit::Golds)] = 9;
    table_value[std::make_tuple(Rank::Ten, Suit::Golds)] = 8;
  }
  else if(vira.get_suit() == Suit::Spades && vira.get_rank() != Rank::Ten && vira.get_rank() != Rank::Eleven)
  {
    table_value[std::make_tuple(Rank::Ten, Suit::Spades)] = 8;
    table_value[std::make_tuple(Rank::Eleven, Suit::Spades)] = 9;
  }
  else if(vira.get_suit() == Suit::Spades && vira.get_rank() == Rank::Ten)
  {
    table_value[std::make_tuple(Rank::Twelve, Suit::Spades)] = 8;
    table_value[std::make_tuple(Rank::Eleven, Suit::Spades)] = 9;
  }
  else if(vira.get_suit() == Suit::Spades && vira.get_rank() == Rank::Eleven)
  {
    table_value[std::make_tuple(Rank::Twelve, Suit::Spades)] = 9;
    table_value[std::make_tuple(Rank::Ten, Suit::Spades)] = 8;
  }
  else if(vira.get_suit() == Suit::Cups && vira.get_rank() != Rank::Ten && vira.get_rank() != Rank::Eleven)
  {
    table_value[std::make_tuple(Rank::Ten, Suit::Cups)] = 8;
    table_value[std::make_tuple(Rank::Eleven, Suit::Cups)] = 9;
  }
  else if(vira.get_suit() == Suit::Cups && vira.get_rank() == Rank::Ten)
  {
    table_value[std::make_tuple(Rank::Twelve, Suit::Cups)] = 8;
    table_value[std::make_tuple(Rank::Eleven, Suit::Cups)] = 9;
  }
  else if(vira.get_suit() == Suit::Cups && vira.get_rank() == Rank::Eleven)
  {
    table_value[std::make_tuple(Rank::Twelve, Suit::Cups)] = 9;
    table_value[std::make_tuple(Rank::Ten, Suit::Cups)] = 8;
  }
  
  int value = 0;
  for (auto i = cards.begin(); i != cards.end(); ++i)
  {
    auto j = std::next(i,1);
    auto k = std::next(j,1);
    int cardvalue_1 = table_value[std::make_tuple(i->get_rank(), i->get_suit())];
    int cardvalue_2 = table_value[std::make_tuple(j->get_rank(), j->get_suit())];
    int cardvalue_3 = table_value[std::make_tuple(k->get_rank(), k->get_suit())];
    if (i->get_suit() == j->get_suit())
    {
      value = cardvalue_1 + cardvalue_2 + 20;
    }
    else if(i->get_suit() == k->get_suit())
    {
      value = cardvalue_1 + cardvalue_3 + 20;
    }
    else if (j->get_suit() == k->get_suit())
    {
      value = cardvalue_2 + cardvalue_3 + 20;
    }
    else if (cardvalue_1 >= cardvalue_2 && cardvalue_1 >= cardvalue_3)
    {
      value = cardvalue_1;
    }
    else if (cardvalue_2 >= cardvalue_1 && cardvalue_2 >= cardvalue_3)
    {
      value = cardvalue_2;
    }
    else
    {
      value = cardvalue_3;
    }
    i = k;
  }
  return value;
};

// This function should calculate if the player have flower or not
bool Player::calculate_flower(Card& vira) {
  auto i = cards.begin();
  auto j = std::next(i,1);
  auto k = std::next(j,1);
  if (i->get_suit() == j->get_suit() && i->get_suit() == k->get_suit() && j->get_suit() == k->get_suit())
  {
    return true;
  }
  return false;
};

// This function should remove the card that is being passed on from the cards list
void Player::play_card(Card& card) {
  cards.remove(card);
};

// This function should set the cards that are being passed, calculate the envido and calculate
// if the player has flower
void Player::set_cards(CardDeck& cards_1, Card& vira) {
  cards = cards_1;
  envido_value = calculate_envido(vira);
  has_flower = calculate_flower(vira);
};