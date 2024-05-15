#define _USE_MATH_DEFINES
#define IMGUI_DEFINE_MATH_OPERATORS

#include <math.h>

#include "hello_imgui/hello_imgui.h"
#include "src/lib/include/Settings.hpp"
#include "src/lib/include/RenderUtilities.hpp"
#include "src/lib/include/Table.hpp"
#include "config.hpp"
#include "Utilities.hpp"

using OnCardClick = std::function<void(const Card&)>;
using PositionsMap = std::unordered_map<HandPosition, std::pair<ImVec2, double>>;
using PlayersMap = std::unordered_map<Player, HandPosition, PlayerHash>;

void card(Card& card, ImVec2 position, double radians = M_PI / 2, ImVec2 card_size = Config::default_card_size) {
    ImGui::SetCursorPos(position);
    ImRotateStart();
    HelloImGui::ImageFromAsset(get_card_image(card).c_str(), card_size);
    ImRotateEnd(radians);
}

void placeholder_card_click(const Card& card) {
    return;
}

void hand(CardDeck& cards, const ImVec2& starting_position, double radians = (M_PI / 2), OnCardClick on_card_click = placeholder_card_click, bool active = false, const ImVec2& card_size = Config::default_card_size) {
    bool horizontal_cards = std::remainder(radians, M_PI) == 0;
    bool playable_cards = active && radians == M_PI / 2;
    int i = 0;
    for (const auto& card: cards) {
        float x = horizontal_cards ? starting_position.x : starting_position.x + (i * Config::card_spacing);
        float y = horizontal_cards ? starting_position.y + (i * Config::card_spacing): starting_position.y;
        ImVec2 position = ImVec2(x, y);
        ImVec2 card_end = ImVec2(x + (horizontal_cards ? card_size.y : card_size.x), y + (horizontal_cards ? card_size.x : card_size.y));

        if (playable_cards && ImGui::IsMouseHoveringRect(position, card_end))
            position.y -= 20;
        ImGui::SetCursorPos(position);
        ImRotateStart();
        bool clicked = false;
        if (playable_cards) clicked = HelloImGui::ImageButtonFromAsset(get_card_image(card).c_str(), card_size, ImVec2(0,0), ImVec2(1,1), 0);
        else HelloImGui::ImageFromAsset(get_card_image(card).c_str(), card_size);
        ImRotateEnd(radians);
        ++i;
        if (clicked) {
            on_card_click(card);
            break;
        };
    }
}

// Only use inside ui function
PositionsMap get_positions(int card_amount) {
    PositionsMap positions_map;
    ImVec2 window = ImGui::GetWindowSize();
    ImVec2 center = window / 2;
    ImVec2 card_size = Config::default_card_size;
    double offset = (card_amount * card_size.x / 2);
    for (HandPosition position = HandPosition::Bottom; position < HandPosition::End; ++position) {
        std::pair<ImVec2, double> result;
        ImVec2 vector;
        if (position == HandPosition::Bottom || position == HandPosition::Top) {
            bool is_bottom = position == HandPosition::Bottom;
            vector.x = center.x - offset;
            vector.y = is_bottom ? window.y - card_size.y : 0.0F;
            result = std::make_pair(vector, is_bottom ? M_PI / 2 : M_PI * 3 / 2);
        }
        else {
            bool is_right = position == HandPosition::Right;
            vector.y = center.y - offset;
            vector.x = is_right ? window.x - card_size.y + 20 : 20;
            result = std::make_pair(vector, is_right ? M_PI : 0.0);
        }
        positions_map[position] = result;
    }
    return positions_map;
}

PositionsMap get_vira_positions() {
    PositionsMap positions_map;
    ImVec2 window = ImGui::GetWindowSize();
    int i = 0;
    for (HandPosition position = HandPosition::Bottom; position < HandPosition::End; ++position) {
        std::pair<ImVec2, double> result;
        ImVec2 vector;
        if (position == HandPosition::Right || position == HandPosition::Top) {
            bool is_right = position == HandPosition::Right;
            vector.x = window.x * 3 / 4;
            vector.y = window.y * (is_right ? (2 / 3.0) : (1 / 6.0));
        }
        else {
            bool is_left = position == HandPosition::Left;
            vector.x = window.x * 1 / 6;
            vector.y = window.y * (is_left ?  1 / 6.0 : 2 / 3.0);
        }
        result = std::make_pair(vector, (M_PI / 4) + (i++ * (M_PI / 2)));
        positions_map[position] = result;
    }
    return positions_map;
}

PositionsMap get_plays_positions() {
    PositionsMap positions_map;
    ImVec2 center = ImGui::GetWindowSize() / 2;
    ImVec2 card_size = Config::default_card_size;
    for (HandPosition position = HandPosition::Bottom; position < HandPosition::End; ++position) {
        std::pair<ImVec2, double> result;
        ImVec2 vector;
        if (position == HandPosition::Bottom || position == HandPosition::Top) {
            bool is_bottom = position == HandPosition::Bottom;
            vector.x = center.x - (card_size.x / 2);
            vector.y = center.y;
            if (is_bottom) vector.y += 70;
            else vector.y -= (70 + card_size.y);
            result = std::make_pair(vector, is_bottom ? M_PI / 2 : M_PI * 3 / 2);
        }
        else {
            bool is_right = position == HandPosition::Right;
            vector.y = center.y - (card_size.x - 20);
            vector.x = center.x + 25;
            if (is_right) vector.x += 70;
            else vector.x -= (70 + card_size.y);
            result = std::make_pair(vector, is_right ? M_PI : 0.0);
        }
        positions_map[position] = result;
    }
    return positions_map;
}

PlayersMap get_players_positions(const std::vector<Player>& players) {
    PlayersMap players_positions;
    int i = 0;
    for (HandPosition position = HandPosition::Bottom; position < HandPosition::End; ++position) {
        players_positions[players[i]] = position;
        ++i;
    }
    return players_positions;
}

Table initialize_game(rng_t& seed) {
    std::vector<Player> players;
    CardDeck full_deck = CardDeck::create_full_deck();
    full_deck.shuffle(seed);
    Card vira = full_deck.get_card();
    for (int i = 0; i < 4; ++i) {
        CardDeck deck;
        for (int j = 0; j < 3; ++j) {
            Card card = full_deck.get_card();
            if (i != 0) card.flip();
            deck.push_front(card);
        }
        players.push_back(Player(deck, "Jugador " + std::to_string(i + 1), vira));
    }
    Table table = Table(vira, players);
    return table;
}

int main(int , char *[])
{
    HelloImGui::RunnerParams params;
    HelloImGui::SetAssetsFolder("assets");
    ImVec2 card_size = Config::default_card_size;
    int game_delay = Config::game_delay;
    rng_t seed(time(NULL));

    Table table = initialize_game(seed);
    std::vector<Player> players = table.get_players();
    Player game_player = players[0];
    
    PlayersMap players_positions = get_players_positions(players);

    params.appWindowParams.windowTitle = Config::title;
    params.imGuiWindowParams.backgroundColor = Config::background_color;
    params.appWindowParams.windowGeometry.fullScreenMode = Config::screen_mode;
    params.fpsIdling.enableIdling = Config::idling;
    int i = 0;
    auto guiFunction = [&]() {
        players = table.get_players();
        PositionsMap vira_positions = get_vira_positions();
        PositionsMap plays_positions = get_plays_positions();

        Card vira = table.get_vira();
        Player first_player = table.get_first_player();
        Player current_player = table.get_current_player();
        HandPosition first_player_position = players_positions[first_player];
        std::vector<Play> plays = table.get_plays();

        std::vector<Team> teams = table.get_teams();
        ImGui::SetCursorPos(ImVec2(ImGui::GetWindowSize().x * 10 / 12, 20));
        if (ImGui::BeginTable("team_counter", 2, ImGuiTableFlags_NoHostExtendX)) {
            ImGui::TableSetupColumn("Team 1", ImGuiTableColumnFlags_WidthFixed);
            ImGui::TableSetupColumn("Team 2", ImGuiTableColumnFlags_WidthFixed);
            ImGui::TableHeadersRow();
            ImGui::TableNextRow();
            for (int column = 0; column < teams.size(); ++column) {
                ImGui::TableSetColumnIndex(column);
                ImGui::Text("%d", teams[column].points);
            }
            ImGui::EndTable();
        }

        bool is_player_turn = game_player == current_player;
        bool all_players_played = plays.size() >= 4;

        auto play_card = [&](Card card) {
            table.play_card(card);
        };
        for (auto& player: players) {
            CardDeck cards = player.get_cards();
            PositionsMap positions = get_positions(cards.size());
            HandPosition player_position = players_positions[player];
            auto [position, radians] = positions[player_position];
            hand(cards, position, radians, play_card, (is_player_turn && !all_players_played));
        }

        for (const auto& play: plays) {
            HandPosition player_position = players_positions[*(play.player)];
            auto [position, radians] = plays_positions[player_position];
            Card play_card = play.card;
            card(play_card, position, radians);
        }

        auto [vira_position, vira_radians] = vira_positions[first_player_position];
        card(vira, vira_position, vira_radians);

        Team* game_winner = table.get_game_winner();
        if (game_winner != nullptr) {
            plays.clear();
            ImGui::SetCursorPos(ImGui::GetWindowSize() / 2);
            bool team1_won = table.get_team_by_player(players[0]) == game_winner;
            ImGui::Text("%s %d! Terminando el juego...", "Ha ganado el equipo", team1_won ? 1 : 2);
            for (int a = 0; a < game_delay; ++a) {
                HelloImGui::GetRunnerParams()->appShallExit = true;
            }
        }

        if (all_players_played) {
            if (++i == game_delay) {
                table.update_round_winners();
                table.update_table(seed);
                i = 0;
            }
        }

        if (is_player_turn || all_players_played) return;
        if (++i == game_delay) {
            if (table.get_current_player().get_cards().size() < 1) return;
            play_card(table.get_current_player().get_cards().front());
            i = 0;
        }
    };

    params.callbacks.ShowGui = guiFunction;
    HelloImGui::Run(params);
    return 0;
}