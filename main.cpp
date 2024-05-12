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

void hand(CardDeck& cards, const ImVec2& starting_position, double radians = (M_PI / 2), OnCardClick on_card_click = placeholder_card_click, const ImVec2& card_size = Config::default_card_size) {
    bool horizontal_cards = std::remainder(radians, M_PI) == 0;
    bool playable_cards = radians == M_PI / 2;
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

void remove_card_from_hand(CardDeck& hand, const Card& card) {
    ImVec2 card_size = Config::default_card_size;
    ImVec2 center = ImVec2(ImGui::GetWindowSize().x / 2, ImGui::GetWindowSize().y / 2);
    hand.remove(card);
    ImGui::SetCursorPos(ImVec2(center.x - (card_size.x / 2), center.y + Config::card_spacing));
    HelloImGui::ImageFromAsset(get_card_image(card).c_str(), card_size);
}

// Only use inside ui function
PositionsMap get_positions(int card_amount) {
    PositionsMap positions_map;
    ImVec2 window = ImGui::GetWindowSize();
    ImVec2 center = window / 2;
    ImVec2 card_size = Config::default_card_size;
    double offset = (card_amount * card_size.x / 2);
    for (HandPosition position = HandPosition::Bottom; position < HandPosition::End; ++position) {
        std::tuple<ImVec2, double> result;
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
        std::tuple<ImVec2, double> result;
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
        std::tuple<ImVec2, double> result;
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
    for (int i = 0; i < 4; ++i) {
        CardDeck deck;
        for (int j = 0; j < 3; ++j) {
            Card card = full_deck.get_card();
            if (i != 0) card.flip();
            deck.push_front(card);
        }
        players.push_back(Player(deck, "Jugador " + std::to_string(i + 1)));
    }
    Card vira = full_deck.get_card();
    Table table = Table(vira, players);
    return table;
}

int main(int , char *[])
{
    HelloImGui::RunnerParams params;
    ImVec2 card_size = Config::default_card_size;
    rng_t seed(time(nullptr));

    Table table = initialize_game(seed);
    std::vector<Player> players = table.get_players();
    
    PlayersMap players_positions = get_players_positions(players);

    params.appWindowParams.windowTitle = Config::title;
    params.imGuiWindowParams.backgroundColor = Config::background_color;
    params.appWindowParams.windowGeometry.fullScreenMode = Config::screen_mode;

    auto guiFunction = [&]() {
        PositionsMap vira_positions = get_vira_positions();
        PositionsMap plays_positions = get_plays_positions();

        Card vira = table.get_vira();
        Player first_player = table.get_first_player();
        HandPosition first_player_position = players_positions[first_player];
        std::vector<Play> plays = table.get_plays();

        auto play_card = [&](Card card) {
            table.play_card(card);
        };
        for (auto& player: players) {
            CardDeck cards = player.get_cards();
            PositionsMap positions = get_positions(cards.size());
            HandPosition player_position = players_positions[player];
            auto [position, radians] = positions[player_position];
            hand(cards, position, radians, play_card);
        }

        for (const auto& play: plays) {
            HandPosition player_position = players_positions[*(play.player)];
            auto [position, radians] = plays_positions[player_position];
            Card play_card = play.card;
            card(play_card, position, radians);
        }

        auto [vira_position, vira_radians] = vira_positions[first_player_position];
        card(vira, vira_position, vira_radians);
    };

    params.callbacks.ShowGui = guiFunction;
    HelloImGui::Run(params);
    return 0;
}

// if (ImGui::Button("Bye!"))
//     HelloImGui::GetRunnerParams()->appShallExit = true;
