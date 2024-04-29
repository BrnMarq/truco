#include <algorithm>

#include <Game.hpp>
#include <Settings.hpp>

card_value_t get_card_value(const Card& card) noexcept
{
    // Write your solution here
    return -1;
}

bool are_all_same_suit(const CardDeck& deck) noexcept
{
    // Write your solution here
    return false;
}

std::pair<CardDeck, CardDeck> create_hand(CardDeck deck) noexcept
{
    // Write your solution here
    return std::make_pair(CardDeck::create_empty_deck(), deck);
}

std::pair<CardDeck, CardDeck> draw_cards(CardDeck deck, size_t n) noexcept
{
    // Write your solution here
    return std::make_pair(CardDeck::create_empty_deck(), deck);
}

std::tuple<bool, size_t, CardDeck, CardDeck> play(CardDeck deck) noexcept
{
    // Write your solution here
    return std::make_tuple(false, 0, CardDeck::create_empty_deck(), deck);
}

std::tuple<bool, size_t, CardDeck, CardDeck> play_optimally(CardDeck deck) noexcept
{
    // Write your solution here
    return std::make_tuple(false, 0, CardDeck::create_empty_deck(), deck);
}
