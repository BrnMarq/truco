#pragma once

#include <iostream>
#include <sstream>
#include <optional>
#include <random>
#include <unordered_map>
#include <array>
#include <list>
#include <queue>
#include <algorithm>

using rd_t = std::random_device;
using rng_t = std::mt19937;
using seed_t = rd_t::result_type;
using optional_seed_t = std::optional<seed_t>;

enum class Suit
{
    REnd,
    Golds, //oros
    Cups, //copas
    Clubs, //bastos
    Spades, //espadas
    End
};

Suit& operator ++ (Suit& suit);

Suit operator ++ (Suit& suit, int);

Suit& operator -- (Suit& suit);

Suit operator -- (Suit& suit, int);

std::string to_string(Suit suit) noexcept;

enum class Rank
{
    REnd,
    One,
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Ten, //sota
    Eleven, //caballo
    Twelve, //rey
    End
};

// This an integral type, so you can perform arithmetic operations with any variable of this type
using card_value_t = std::underlying_type<Rank>::type;

Rank& operator ++ (Rank& rank);

Rank operator ++ (Rank& rank, int);

Rank& operator -- (Rank& rank);

Rank operator -- (Rank& rank, int);

std::string to_string(Rank rank) noexcept;

enum class HandPosition
{
    REnd,
    Bottom,
    Right,
    Top,
    Left,
    End
};

HandPosition& operator ++ (HandPosition& hand_position);

HandPosition operator ++ (HandPosition& hand_position, int);

HandPosition& operator -- (HandPosition& hand_position);

HandPosition operator -- (HandPosition& hand_position, int);

std::string to_string(HandPosition hand_position) noexcept;