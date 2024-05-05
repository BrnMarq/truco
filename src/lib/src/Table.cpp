#include "Table.hpp"

// As a general thought, take in mind that every member of the class Table is accesible
// in this functions, as if it were variables inside the functions

Table::Table(Card& vira, std::array<Team, 2> teams): vira{vira}, teams{teams}
{
}

Table::~Table()
{
}

// This function should raise the value of the table by 1-3-6-9-12, preferably on a scalable way
// if no idea found, I suggest to add 2 on the value if it's one, otherwise just add 3
void Table::raise_value() {
      if(value == 1) 
        value += 2;
      else 
        value += 3;
};

// Like the function says, it just turns on the envido
void Table::activate_envido() {
    if(!envido)  envido = true;
};

// Calculate the staircase based on which is the vira(I suggest to go from 1-n, the greater the number,
// the greater the power)(Burnt cards should have a value of 0, but it is okay if it is not included on the staircase)
CardValues Table::calculate_staircase() {
  CardValues result;
  return result;
};

// If the play_order list is not initialized already, initialize it(Suggestion: use the teams array
// to create it), if the play_order list is initialized, just crop the first item and append it at the end
void Table::update_play_order() {

};

// current_player is a node on the play_order list, executing std::next on that node should get you the next on the list
// be aware that play_order is not a circular list, once you reach the end of the list, return *std::begin
Player Table::get_next_player() {
  Player player;
  return player;
};

// This function should add the card and the current player to plays array(The current player node, not
// the player in the node)
void Table::play_card(Card& card, bool burnt) {

};

// This function should get who wins based on plays array
PlayerNode Table::get_round_winner() {
  static std::list<Player> players;
  return players.begin();
};

// This function should get the round winner, set the winner as current_player, and add round_winners
// array which team won(round_winners array works in the way that, nullptr is a tie, ptr to team1 is team1 winner and so on)
void Table::update_round_winners() {

};

// This function should calculate which team won the table based on the round_winners array
Team Table::get_table_winner() {
  Player player;
  Team team(player, player);
  return team;
};

// This function should check if there's a winner, if the points of one of the teams is greater than twelve
// then return a pointer to that theam, otherwise, just return nullptr
Team* Table::get_game_winner() {
  Player player;
  static Team team(player, player);
  return &team;
};

// update_table should get the table winner, update the play_order, set the current_player as the beginning of the list
// add the value of the table to the points of the team, add the envido value, in case there was envido
// set the value again as 1, set the envido as false, this function should do a lot of shit xd, once you get here call me
void Table::update_table() {

};

