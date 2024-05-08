#include "Table.hpp"

// As a general thought, take in mind that every member of the class Table is accesible
// in this functions, as if it were variables inside the functions

Table::Table(Card& vira, std::vector<Team> teams) : vira{ vira }, teams{ teams }
{
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
};

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
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
                 play_order.push_back(teams[i].players[j]);
    }
    else 
    {
        play_order.push_back(play_order.front());
        play_order.pop_front();
    }
};

// current_player is a node on the play_order list, executing std::next on that node should get you the next on the list
// be aware that play_order is not a circular list, once you reach the end of the list, return *std::begin
Player Table::get_next_player() {

    current_player = std::next(current_player);

    if (current_player == play_order.end())
        current_player = play_order.begin();

    return *current_player;
};

// This function should add the card and the current player to plays array(The current player node, not
// the player in the node)
void Table::play_card(Card& card, bool burnt) {

    plays.push_back(Play::Play(current_player,card,burnt));
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
}
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
        get_next_player();
        round_winners.push_back(nullptr);
    }
};

// This function should calculate which team won the table based on the round_winners array
Team Table::get_table_winner() {

    //Caso donde un equipo gana 2 veces y no hay empates

    std::unordered_map<Team*, int> counter;

    for (auto winner : round_winners)
    {
        if (winner != nullptr) {
            counter[winner]++;
        }
    }

    for (const auto& pair : counter)
    {
        if (pair.second == 2) {
            return *pair.first;
        }
    }

    //Casos de empate

    if (round_winners[0] == nullptr && round_winners[1] != nullptr)
        return *round_winners[1];
    else if (round_winners[1] == nullptr && round_winners[0] != nullptr)
        return *round_winners[0];
    else if(round_winners[2] == nullptr && round_winners[0] != nullptr)
        return *round_winners[0];
    else if(round_winners[0] == nullptr && round_winners[1] == nullptr && round_winners[2] != nullptr)
        return *round_winners[2];
    else
        return *round_winners[0];

    // Esto serviría para empate en primera ronda y empate en última pero no se me ocurrió una manera para evaluarlo con
    //empate en segunda o los otros casos de empate 

   /* auto tie = std::find_if(round_winners.begin(), round_winners.end(), std::vector<Team*>{nullptr});

    if (tie != round_winners.end()) 
    {
        auto winner = *std::next(tie);

        if (winner == *round_winners.end()) 
        {
            winner = *round_winners.begin();
            return  *winner;
        }
    }*/

};

// This function should check if there's a winner, if the points of one of the teams is greater than twelve
// then return a pointer to that theam, otherwise, just return nullptr
Team* Table::get_game_winner() {

    if (teams[0].points > 12) return &teams[0];
    else if (teams[1].points > 12) return &teams[1];
    else return nullptr;
};

// update_table should get the table winner, update the play_order, set the current_player as the beginning of the list
// add the value of the table to the points of the team, add the envido value, in case there was envido
// set the value again as 1, set the envido as false, this function should do a lot of shit xd, once you get here call me
void Table::update_table() {

};

