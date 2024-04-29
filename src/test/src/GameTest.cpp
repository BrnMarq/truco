#include <TestUtilities.hpp>
#include <Game.hpp>

int main()
{
    std::cout << std::boolalpha;
    
    std::cout << "Card value tests\n";
    assert_equal(get_card_value(Card{Suit::Clubs, Rank::Ace}), 1);
    assert_equal(get_card_value(Card{Suit::Clubs, Rank::Six}), 6);
    assert_equal(get_card_value(Card{Suit::Clubs, Rank::Queen}), 12);

    std::cout << "Deck suit tests\n";
    assert_equal(are_all_same_suit(CardDeck::create_empty_deck()), true);
    assert_equal(are_all_same_suit({Card{Suit::Clubs, Rank::Ace}}), true);
    assert_equal(are_all_same_suit({Card{Suit::Clubs, Rank::Ace}, Card{Suit::Clubs, Rank::Two}}), true);
    assert_equal(are_all_same_suit({Card{Suit::Clubs, Rank::Ace}, Card{Suit::Swords, Rank::Ace}}), false);

    std::cout << "Create hand test\n";
    {
        CardDeck expected_hand{
            Card{Suit::Clubs, Rank::Ace},
            Card{Suit::Clubs, Rank::Two},
            Card{Suit::Clubs, Rank::Three},
            Card{Suit::Clubs, Rank::Four},
            Card{Suit::Clubs, Rank::Five},
            Card{Suit::Clubs, Rank::Six},
            Card{Suit::Clubs, Rank::Seven},
            Card{Suit::Clubs, Rank::Jack}
        };

        CardDeck expected_deck = CardDeck::create_full_deck();
        for (size_t i = 0; i < 8; ++i)
        {
            expected_deck.pop_front();
        }

        auto expected_pair = std::make_pair(expected_hand, expected_deck);

        assert_equal(create_hand(CardDeck::create_full_deck()), expected_pair);
    }

    std::cout << "Draw card test\n";
    {
        CardDeck expected_hand{
            Card{Suit::Clubs, Rank::Ace},
            Card{Suit::Clubs, Rank::Two},
            Card{Suit::Clubs, Rank::Three},
            Card{Suit::Clubs, Rank::Four}
        };

        CardDeck expected_deck = CardDeck::create_full_deck();
        for (size_t i = 0; i < 4; ++i)
        {
            expected_deck.pop_front();
        }

        auto expected_pair = std::make_pair(expected_hand, expected_deck);

        assert_equal(draw_cards(CardDeck::create_full_deck(), 4), expected_pair);
    }
    {
        CardDeck expected_hand{
            Card{Suit::Clubs, Rank::Ace},
            Card{Suit::Clubs, Rank::Two},
            Card{Suit::Clubs, Rank::Three}
        };

        CardDeck expected_deck = CardDeck::create_full_deck();
        for (size_t i = 0; i < 3; ++i)
        {
            expected_deck.pop_front();
        }

        auto expected_pair = std::make_pair(expected_hand, expected_deck);

        assert_equal(draw_cards(CardDeck::create_full_deck(), 3), expected_pair);
    }
    {
        CardDeck expected_hand{
            Card{Suit::Clubs, Rank::Ace},
            Card{Suit::Clubs, Rank::Two}
        };

        CardDeck expected_deck = CardDeck::create_full_deck();
        for (size_t i = 0; i < 2; ++i)
        {
            expected_deck.pop_front();
        }

        auto expected_pair = std::make_pair(expected_hand, expected_deck);

        assert_equal(draw_cards(CardDeck::create_full_deck(), 2), expected_pair);
    }

    
    std::cout << "Play test\n";
    {
        
    }

    std::cout << "Play optimally test\n";
    {
        
    }

    return EXIT_SUCCESS;
}
