#include <CardDeck.hpp>
#include <Player.hpp>
#include <time.h>

int main() {
  {
    rng_t seed(time(nullptr));
    CardDeck full_deck = CardDeck::create_full_deck();
    full_deck.shuffle(seed);
    CardDeck deck;
    for (int j = 0; j < 3; ++j) {
        Card card = full_deck.get_card();
        deck.push_front(card);
    }
    Player player = Player(deck, "Jugador 1");
    player.play_card(deck.front());
    std::cout << deck.size() << std::endl;
  }
};