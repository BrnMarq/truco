#include "Table.hpp"

// As a general thought, take in mind that every member of the class Table is accesible
// in this functions, as if it were variables inside the functions

Table::Table(Card& vira, std::vector<Team>& teams) : vira{ vira }, teams{ teams }
{
    value = 1;
    envido = false;
    update_play_order();
    current_player = play_order.begin();
}

Table::Table(Card& vira, std::vector<Player>& players) : vira{ vira }
{
    for (int i = 0; i < 2; ++i) {
        teams.push_back(Team(players[i], players[i + 2]));
    }
    value = 1;
    envido = false;
    update_play_order();
    current_player = play_order.begin();
}

Table::~Table()
{
}

// This function should raise the value of the table by 1-3-6-9-12, preferably on a scalable way
// if no idea found, I suggest to add 2 on the value if it's one, otherwise just add 3
void Table::raise_value() {

    if (value == 1)
        value += 2;
    else
        value += 3;
};

// Like the function says, it just turns on the envido
void Table::activate_envido() {
    if (!envido)  envido = true;
}

Player Table::get_first_player() const {
    return play_order.front();
}

Player Table::get_current_player() const {
    return *(current_player);
}

Card Table::get_vira() const {
    return vira;
}

std::vector<Play> Table::get_plays() const {
    return plays;
}

std::vector<Player> Table::get_players() const {
    std::vector<Player> players{ std::begin(play_order), std::end(play_order) };
    return players;
}

std::list<Player> Table::get_play_order() const {
    return play_order;
}

//This function returns a generic CardValue 
CardValues Table::get_card_values()
{
    CardValues result
    {
        {Card(Suit::Golds,Rank::One),8},
        {Card(Suit::Golds,Rank::Two),9},
        {Card(Suit::Golds,Rank::Three),10}, 
        {Card(Suit::Golds,Rank::Four),1},
        {Card(Suit::Golds,Rank::Five),2},
        {Card(Suit::Golds,Rank::Six),3},
        {Card(Suit::Golds,Rank::Seven),11},
        {Card(Suit::Golds,Rank::Ten),5},
        {Card(Suit::Golds,Rank::Eleven),6},
        {Card(Suit::Golds,Rank::Twelve),7},

        {Card(Suit::Cups,Rank::One),8},
        {Card(Suit::Cups,Rank::Two),9},
        {Card(Suit::Cups,Rank::Three),10},
        {Card(Suit::Cups,Rank::Four),1},
        {Card(Suit::Cups,Rank::Five),2},
        {Card(Suit::Cups,Rank::Six),3},
        {Card(Suit::Cups,Rank::Seven),4},
        {Card(Suit::Cups,Rank::Ten),5},
        {Card(Suit::Cups,Rank::Eleven),6},
        {Card(Suit::Cups,Rank::Twelve),7},

        {Card(Suit::Spades,Rank::One),14},
        {Card(Suit::Spades,Rank::Two),9},
        {Card(Suit::Spades,Rank::Three),10},
        {Card(Suit::Spades,Rank::Four),1},
        {Card(Suit::Spades,Rank::Five),2},
        {Card(Suit::Spades,Rank::Six),3},
        {Card(Suit::Spades,Rank::Seven),12},
        {Card(Suit::Spades,Rank::Ten),5},
        {Card(Suit::Spades,Rank::Eleven),6},
        {Card(Suit::Spades,Rank::Twelve),7},

        {Card(Suit::Clubs,Rank::One),13},
        {Card(Suit::Clubs,Rank::Two),9},
        {Card(Suit::Clubs,Rank::Three),10},
        {Card(Suit::Clubs,Rank::Four),1},
        {Card(Suit::Clubs,Rank::Five),2},
        {Card(Suit::Clubs,Rank::Six),3},
        {Card(Suit::Clubs,Rank::Seven),4},
        {Card(Suit::Clubs,Rank::Ten),5},
        {Card(Suit::Clubs,Rank::Eleven),6},
        {Card(Suit::Clubs,Rank::Twelve),7}
    };

    return result;
}

// Calculate the staircase based on which is the vira(I suggest to go from 1-n, the greater the number,
// the greater the power)(Burnt cards should have a value of 0, but it is okay if it is not included on the staircase)
CardValues Table::calculate_staircase() {

    CardValues result = get_card_values();

    result[Card(vira.get_suit(), Rank::Ten)] = 15;
    result[Card(vira.get_suit(), Rank::Eleven)] = 16;

    if (vira.get_rank() == Rank::Ten)
        result[Card(vira.get_suit(), Rank::Twelve)] = 15;
    else if (vira.get_rank() == Rank::Eleven)
        result[Card(vira.get_suit(), Rank::Twelve)] = 16;

    return result;
};

// If the play_order list is not initialized already, initialize it(Suggestion: use the teams array
// to create it), if the play_order list is initialized, just crop the first item and append it at the end
void Table::update_play_order() {

    if (play_order.size() == 0) 
    {
        play_order.push_back(teams[0].players[0]);
        play_order.push_back(teams[1].players[0]);
        play_order.push_back(teams[0].players[1]);
        play_order.push_back(teams[1].players[1]);
    }
    else 
    {
        play_order.push_back(play_order.front());
        play_order.pop_front();
    }
};

// current_player is a node on the play_order list, executing std::next on that node should get you the next on the list
// be aware that play_order is not a circular list, once you reach the end of the list, return *std::begin
PlayerNode Table::get_next_player() {

    PlayerNode current = std::next(current_player);

    if (current == play_order.end())
        current = play_order.begin();

    return current;
};

// This function should add the card and the current player to plays array(The current player node, not
// the player in the node)
void Table::play_card(Card& card, bool burnt) {
    current_player->play_card(card);
    if (!card.is_visible() && !burnt) card.flip();
    plays.push_back(Play(current_player, card, burnt));
    current_player = get_next_player();
};

// This function should get who wins based on plays array
PlayerNode* Table::get_round_winner() {

    CardValues card_values = calculate_staircase(); 

    int p1_points = plays[0].burnt ? 0 : card_values[plays[0].card];
    int p2_points = plays[1].burnt ? 0 : card_values[plays[1].card];
    int p3_points = plays[2].burnt ? 0 : card_values[plays[2].card];
    int p4_points = plays[3].burnt ? 0 : card_values[plays[3].card];

    if (p1_points > p2_points && p1_points > p3_points && p1_points > p4_points)
    {
        return &plays[0].player;
    }
    else if (p2_points > p1_points && p2_points > p3_points && p2_points > p4_points)
    {
        return &plays[1].player;
    }
    else if (p3_points > p1_points && p3_points > p2_points && p3_points > p4_points)
    {
        return &plays[2].player;
    }
    else if (p4_points > p1_points && p4_points > p2_points && p4_points > p3_points)
    {
        return &plays[3].player;
    }
    else
        return nullptr;
};

//This function returns the player's team position on the teams vector. It'll return just 0 or 1
//since teams vector just contains 2 elements. 
int Table::get_team_position(Player player) 
{
    for (size_t i = 0; i < 2; i++)
    {
        for (size_t j = 0; j < 2; j++)
        {
            if (teams[i].players[j].get_name() == player.get_name())
                return i;
        }
    }
    return -1;
};
// This function should get the round winner, set the winner as current_player, and add round_winners
// array which team won(round_winners array works in the way that, nullptr is a tie, ptr to team1 is team1 winner and so on)
void Table::update_round_winners() {

    auto winner = get_round_winner();

    if (winner != nullptr) 
    {
        current_player = *winner;
        round_winners.push_back(&teams[get_team_position(*current_player)]);
    }
    else 
    {
        current_player = get_next_player();
        round_winners.push_back(nullptr);
    }
};

// This function should calculate which team won the table based on the round_winners array
Team Table::get_table_winner() {

    //No tie case

    std::unordered_map<Team*, int> counter;

    for (auto winner : round_winners)
    {
        if (winner != nullptr) {
            counter[winner]++;

            if (counter[winner] == 2) {
                return *winner;
            }
        }       
    }

    //Tie cases

    if (round_winners[0] == nullptr && round_winners[1] != nullptr)
        return *round_winners[1];
    else if (round_winners[1] == nullptr && round_winners[0] != nullptr)
        return *round_winners[0];
    else if(round_winners[2] == nullptr && round_winners[0] != nullptr)
        return *round_winners[0];
    else if(round_winners[0] == nullptr && round_winners[1] == nullptr && round_winners[2] != nullptr)
        return *round_winners[2];
    else
        return teams[get_team_position(*plays[0].player)];
};

// This function should check if there's a winner, if the points of one of the teams is greater than twelve
// then return a pointer to that theam, otherwise, just return nullptr
Team* Table::get_game_winner() {

    if (teams[0].points > 12) return &teams[0];
    else if (teams[1].points > 12) return &teams[1];
    else return nullptr;
};

//This function returns the team with the highest envido 
Team* Table::get_envido_winner() {

    int player_1 = (*plays[0].player).get_envido_value();
    int player_2 = (*plays[1].player).get_envido_value();
    int player_3 = (*plays[2].player).get_envido_value();
    int player_4 = (*plays[3].player).get_envido_value();

    if (player_1 == player_2 == player_3 == player_4)
        return &teams[get_team_position(*plays[0].player)];

    int team_1 = player_1 > player_3 ? player_1 : player_3;
    int team_2 = player_2 > player_4 ? player_2 : player_4;

    if (team_1 > team_2)
       return &teams[get_team_position(*plays[0].player)];
    else
       return &teams[get_team_position(*plays[1].player)];
}

// update_table should get the table winner, update the play_order, set the current_player as the beginning of the list
// add the value of the table to the points of the team, add the envido value, in case there was envido
// set the value again as 1, set the envido as false, this function should do a lot of shit xd, once you get here call me
void Table::update_table() {

    Team winner = get_table_winner();
    winner.points += value;

    if (envido) {
        Team* envido_winner = get_envido_winner();
        envido_winner->points += 2;
    }

    //current_player as the beginning of the list

    update_play_order();
    current_player = play_order.begin();

    value = 1;
    envido = false;
};

