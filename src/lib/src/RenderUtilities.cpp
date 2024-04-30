#include "RenderUtilities.hpp"

std::unordered_map<Suit, std::string> SUIT_PATHS = {
  {Suit::Spades, "Spades"},
  {Suit::Clubs, "Clubs"},
  {Suit::Cups, "Cups"},
  {Suit::Golds, "Golds"},
};

std::unordered_map<Rank, std::string> RANK_PATHS = {
  {Rank::One, "1"},
  {Rank::Two, "2"},
  {Rank::Three, "3"},
  {Rank::Four, "4"},
  {Rank::Five, "5"},
  {Rank::Six, "6"},
  {Rank::Seven, "7"},
  {Rank::Ten, "10"},
  {Rank::Eleven, "11"},
  {Rank::Twelve, "12"},
};

std::string get_card_image(const Card& card) {
  std::string path = "images/";
  path += SUIT_PATHS[card.get_suit()] + "/";
  path += RANK_PATHS[card.get_rank()] + ".JPG";
  return path;
};