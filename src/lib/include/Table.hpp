#pragma once

#include "Player.hpp"

using CardValues = std::unordered_map<Card, int, CardHash>;
using PlayerNode = std::list<Player>::iterator;

struct Play {
  PlayerNode player;
  Card card;
  bool burnt;

  Play(PlayerNode player, Card card, bool burnt): card{card}, player{player}, burnt{burnt} {

  }

  Play() {}
};

struct Team {
  std::array<Player, 2> players;
  int points;

  Team(Player& player1, Player& player2) {
    players[0] = player1;
    players[1] = player2;
    points = 0;
  }

  Team(Team& team): players{team.players}, points{0} {

  }
};

class Table
{
private:
  int value;
  bool envido;
  Card vira;
  CardValues staircase;
  std::array<Play, 4> plays;
  std::array<Team*, 3> round_winners;
  std::array<Team, 2> teams;
  std::list<Player> play_order;
  PlayerNode current_player;
public:
  Table(Card& vira, std::array<Team, 2> teams);
  ~Table();

  void raise_value();
  void activate_envido();

  CardValues calculate_staircase();
  void update_play_order();
  Player get_next_player();

  void play_card(Card& card, bool burnt);

  PlayerNode get_round_winner();
  void update_round_winners();
  Team get_table_winner();
  Team* get_game_winner();
  void update_table();
};