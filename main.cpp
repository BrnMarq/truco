#define _USE_MATH_DEFINES
#define IMGUI_DEFINE_MATH_OPERATORS

#include <math.h>

#include "hello_imgui/hello_imgui.h"
#include "src/lib/include/Settings.hpp"
#include "src/lib/include/RenderUtilities.hpp"
#include "src/lib/include/Table.hpp"
#include "config.hpp"
#include "Utilities.hpp"

using OnCardClick = std::function<void(CardDeck&, const Card&)>;
using PositionsMap = std::unordered_map<HandPosition, std::pair<ImVec2, double>>;

void placeholder_card_click(CardDeck& hand, const Card& card) {

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
            on_card_click(cards, card);
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
PositionsMap get_positions_map() {
    PositionsMap positions_map;
    ImVec2 window = ImGui::GetWindowSize();
    ImVec2 center = window / 2;
    ImVec2 card_size = Config::default_card_size;
    for (HandPosition position = HandPosition::Bottom; position < HandPosition::End; ++position) {
        std::tuple<ImVec2, double> result;
        ImVec2 vector;
        if (position == HandPosition::Bottom || position == HandPosition::Top) {
            bool is_bottom = position == HandPosition::Bottom;
            vector.x = center.x;
            vector.y = is_bottom ? window.y - card_size.y : 0.0F;
            result = std::make_pair(vector, is_bottom ? M_PI / 2 : M_PI * 3 / 2);
        }
        else {
            bool is_right = position == HandPosition::Right;
            vector.y = center.y;
            vector.x = is_right ? window.x - card_size.y + 20 : -45.0F;
            result = std::make_pair(vector, is_right ? M_PI : 0.0);
        }
        positions_map[position] = result;
    }
    return positions_map;
}

int main(int , char *[])
{
    HelloImGui::RunnerParams params;
    ImVec2 card_size = Config::default_card_size;
    rng_t seed(time(nullptr));
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
    Card vira = full_deck.back();
    full_deck.pop_back();
    Table table = Table(vira, players);

    // std::unordered_map<Player, HandPosition> players_positions;
    // int i = 0;
    // for (HandPosition position = HandPosition::Bottom; position < HandPosition::End; ++position) {
    //     players_positions[players[i]] = position;
    //     ++i;
    // }

    params.appWindowParams.windowTitle = Config::title;
    params.imGuiWindowParams.backgroundColor = Config::background_color;
    params.appWindowParams.windowGeometry.fullScreenMode = Config::screen_mode;

    auto guiFunction = [&]() {
        PositionsMap positions = get_positions_map();
        ImVec2 window = ImGui::GetWindowSize();

        // hand(hands[0], position1, M_PI * 3 / 2);
        // hand(hands[1], position2, 0.0);
        // hand(hands[2], position3, M_PI);
        // hand(hands[3], position4, M_PI / 2, remove_card_from_hand);

        ImVec2 vira_position = ImVec2(window.x * 3 / 4, window.y * 2 / 3);
        ImGui::SetCursorPos(vira_position);
        ImRotateStart();
        HelloImGui::ImageFromAsset(get_card_image(vira).c_str(), card_size);
        ImRotateEnd(3 * M_PI / 4);
    };

    params.callbacks.ShowGui = guiFunction;
    HelloImGui::Run(params);
    return 0;
}

// if (ImGui::Button("Bye!"))
//     HelloImGui::GetRunnerParams()->appShallExit = true;
