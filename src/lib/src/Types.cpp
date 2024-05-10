#include <type_traits>

#include <Types.hpp>

Suit& operator ++ (Suit& suit)
{
    if (suit == Suit::End)
    {
        throw std::overflow_error{"suit cannot be incremented"};
    }

    using base_type = std::underlying_type<Suit>::type;
    suit = static_cast<Suit>(static_cast<base_type>(suit) + 1);
    return suit;
}

Suit operator ++ (Suit& suit, int)
{
    Suit result = suit;
    ++suit;
    return suit;
}

Suit& operator -- (Suit& suit)
{
    if (suit == Suit::REnd)
    {
        throw std::underflow_error{"suit cannot be decremented"};
    }

    using base_type = std::underlying_type<Suit>::type;
    suit = static_cast<Suit>(static_cast<base_type>(suit) - 1);
    return suit;
}

Suit operator -- (Suit& suit, int)
{
    Suit result = suit;
    --suit;
    return suit;
}

std::string to_string(Suit suit) noexcept
{
    switch (suit)
    {
        case Suit::Golds: return "Golds";
        case Suit::Cups: return "Cups";
        case Suit::Clubs: return "Clubs";
        case Suit::Spades: return "Spades";
        default: return "";
    }
}

Rank& operator ++ (Rank& rank)
{
    if (rank == Rank::End)
    {
        throw std::underflow_error{"rank cannot be incremented"};
    }

    using base_type = std::underlying_type<Rank>::type;
    rank = static_cast<Rank>(static_cast<base_type>(rank) + 1);
    return rank;
}

Rank operator ++ (Rank& rank, int)
{
    Rank result = rank;
    ++rank;
    return result;
}

Rank& operator -- (Rank& rank)
{
    if (rank == Rank::REnd)
    {
        throw std::underflow_error{"rank cannot be decremented"};
    }

    using base_type = std::underlying_type<Rank>::type;
    rank = static_cast<Rank>(static_cast<base_type>(rank) - 1);
    return rank;
}

Rank operator -- (Rank& rank, int)
{
    Rank result = rank;
    --rank;
    return result;
}

std::string to_string(Rank rank) noexcept
{
    switch (rank)
    {
        case Rank::One: return "One";
        case Rank::Two: return "Two";
        case Rank::Three: return "Three";
        case Rank::Four: return "Four";
        case Rank::Five: return "Five";
        case Rank::Six: return "Six";
        case Rank::Seven: return "Seven";
        case Rank::Ten: return "Ten";
        case Rank::Eleven: return "Eleven";
        case Rank::Twelve: return "Twelve";
        default: return "";
    }
}


HandPosition& operator ++ (HandPosition& hand_position)
{
    if (hand_position == HandPosition::End)
    {
        throw std::underflow_error{"hand_position cannot be incremented"};
    }

    using base_type = std::underlying_type<HandPosition>::type;
    hand_position = static_cast<HandPosition>(static_cast<base_type>(hand_position) + 1);
    return hand_position;
}

HandPosition operator ++ (HandPosition& hand_position, int)
{
    HandPosition result = hand_position;
    ++hand_position;
    return result;
}

HandPosition& operator -- (HandPosition& hand_position)
{
    if (hand_position == HandPosition::REnd)
    {
        throw std::underflow_error{"hand_position cannot be decremented"};
    }

    using base_type = std::underlying_type<HandPosition>::type;
    hand_position = static_cast<HandPosition>(static_cast<base_type>(hand_position) - 1);
    return hand_position;
}

HandPosition operator -- (HandPosition& hand_position, int)
{
    HandPosition result = hand_position;
    --hand_position;
    return result;
}

std::string to_string(HandPosition hand_position) noexcept
{
    switch (hand_position)
    {
        case HandPosition::Bottom: return "Bottom";
        case HandPosition::Right: return "Right";
        case HandPosition::Top: return "Top";
        case HandPosition::Left: return "Left";
        default: return "";
    }
}
