#pragma once

#include "Player.hpp"

using CardValues = std::unordered_map<Card, int, CardHash>;
using PlayerNode = std::list<Player>::iterator;

struct Play {
    PlayerNode player;
    Card card;
    bool burnt;

    Play(PlayerNode player, Card card, bool burnt) : card{ card }, player{ player }, burnt{ burnt } {

    }

    Play() {}
};

struct Team {
    std::array<Player,2> players;
    int points;

    Team(Player& player1, Player& player2) {
        players[0] = player1;
        players[1] = player2;
        points = 0;
    }

    Team(const Team& team) : players{ team.players }, points{ 0 } {

    }
};

class Table
{
private:
    int value;
    bool envido;
    Card vira;
    CardValues staircase;
    std::vector<Play> plays;
    std::vector<Team*> round_winners;
    std::vector<Team> teams;
    std::list<Player> play_order;
    PlayerNode current_player;
public:
    Table(Card& vira, std::vector<Team>& teams);
    Table(Card& vira, std::vector<Player>& players);
    ~Table();

    void raise_value();
    void activate_envido();
    Player get_first_player() const;
    Player get_current_player() const;
    Card get_vira() const;
    std::vector<Play> get_plays() const;
    std::vector<Player> get_players() const;
    std::list<Player> get_play_order() const;
    std::vector<Team> get_teams() const;

    void change_vira(Card card);
    CardValues get_card_values();
    CardValues calculate_staircase();
    void update_play_order();
    PlayerNode get_next_player();

    void play_card(Card& card, bool burnt = false);

    Team& get_team_by_player(const Player& player);
    Team* get_envido_winner();

    PlayerNode* get_round_winner();
    void update_round_winners();
    Team* get_table_winner();
    Team* get_game_winner();
    void update_table();
};