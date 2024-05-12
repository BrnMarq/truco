#include <Table.hpp>

int main() {
  rng_t seed(time(nullptr));
  {
    std::vector<Player> players;
    CardDeck full_deck = CardDeck::create_full_deck();
    full_deck.shuffle(seed);
    std::vector<Team> teams;
    for (int i = 0; i < 4; ++i) {
        CardDeck deck;
        for (int j = 0; j < 3; ++j) {
            Card card = full_deck.get_card();
            if (i != 3) card.flip();
            deck.push_front(card);
        }
        players.push_back(Player(deck, "Jugador " + std::to_string(i + 1)));
    }
    for (int i = 0; i < 2; ++i) {
        teams.push_back(Team(players[i], players[i + 2]));
    }
    Card vira = full_deck.get_card();
    Table table = Table(vira, players);
    std::cout << "Size play_order test" << std::endl;
    std::cout << "Pruebita" << std::endl;
  }
};