#include <Table.hpp>

int main() {
  rng_t seed(time(nullptr));
  {
    std::vector<Player> players;
    CardDeck full_deck = CardDeck::create_full_deck();
    Card vira = full_deck.get_card();
    full_deck.shuffle(seed);
    for (int i = 0; i < 4; ++i) {
        CardDeck deck;
        for (int j = 0; j < 3; ++j) {
            Card card = full_deck.get_card();
            if (i != 3) card.flip();
            deck.push_front(card);
        }
        players.push_back(Player(deck, "Jugador " + std::to_string(i + 1), vira));
    }
    Table table = Table(vira, players);

    std::cout << "Size play_order test" << std::endl;
    table.points_test();

    std::vector<Team> teams = table.get_teams();

    for (auto& team: table.teams) {
      std::cout << team.points << std::endl;
    }

    for (auto& team: teams) {
      std::cout << team.points << std::endl;
    }
  }
};