/**
 * @author: 
*/

#pragma once

#include <tuple>

#include <CardDeck.hpp>

// Warming problems

card_value_t get_card_value(const Card& card) noexcept;

// Intermediate problems

bool are_all_same_suit(const CardDeck& deck) noexcept;

std::pair<CardDeck, CardDeck> create_hand(CardDeck deck) noexcept;

std::pair<CardDeck, CardDeck> draw_cards(CardDeck deck, size_t n) noexcept;

// Play problems

std::tuple<bool, size_t, CardDeck, CardDeck> play(CardDeck deck) noexcept;

std::tuple<bool, size_t, CardDeck, CardDeck> play_optimally(CardDeck deck) noexcept;
