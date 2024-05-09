#define _USE_MATH_DEFINES
#define IMGUI_DEFINE_MATH_OPERATORS

#include <math.h>

#include "hello_imgui/hello_imgui.h"
#include "src/lib/include/Settings.hpp"
#include "src/lib/include/RenderUtilities.hpp"
#include "src/lib/include/CardDeck.hpp"
#include "config.hpp"
#include "Utilities.hpp"

bool is_integer(float k)
{
    return std::floor(k) == k;
}

void hand(const CardDeck& cards, const ImVec2& starting_position, double radians = (M_PI / 2), const ImVec2& card_size = Config::default_card_size) {
    bool vertical = std::remainder(radians, M_PI) == 0;
    int i = 0;
    for (const auto& card: cards) {
        float x = vertical ? starting_position.x : starting_position.x + (i * Config::card_spacing);
        float y = vertical ? starting_position.y + (i * Config::card_spacing): starting_position.y;

        ImVec2 position = ImVec2(x, y);
        ImGui::SetCursorPos(position);
        ImRotateStart();
        HelloImGui::ImageFromAsset(get_card_image(card).c_str(), card_size);
        ImRotateEnd(radians);
        ++i;
    }
}

int main(int , char *[])
{
    HelloImGui::RunnerParams params;
    ImVec2 card_size = Config::default_card_size;

    params.appWindowParams.windowTitle = Config::title;
    params.imGuiWindowParams.backgroundColor = Config::background_color;
    params.appWindowParams.windowGeometry.fullScreenMode = Config::screen_mode;

    rng_t seed(time(nullptr));
    std::vector<CardDeck> hands;
    CardDeck full_deck = CardDeck::create_full_deck();
    full_deck.shuffle(seed);
    for (int i = 0; i < 4; ++i) {
        CardDeck deck;
        for (int j = 0; j < 3; ++j) {
            Card card = full_deck.back();
            // if (i != 3) card.flip();
            deck.push_front(card);
            full_deck.pop_back();
        }
        hands.push_back(deck);
    }

    int n = 0;
    auto guiFunction = [&]() {
        ImVec2 position1 = ImVec2((ImGui::GetWindowSize().x / 2) - ((card_size.x * 3) / 2), 0.0F);
        ImVec2 position2 = ImVec2(card_size.y / 2 - 28, (ImGui::GetWindowSize().y / 2 - (card_size.x * 3 / 2)));
        ImVec2 position3 = ImVec2(ImGui::GetWindowSize().x - card_size.y + 20, (ImGui::GetWindowSize().y / 2 - card_size.x * 3 / 2));
        ImVec2 position4 = ImVec2(ImGui::GetWindowSize().x / 2 - (card_size.x * 3 / 2), ImGui::GetWindowSize().y - card_size.y);
        hand(hands[0], position1, M_PI * 3 / 2);
        hand(hands[1], position2, 0.0);
        hand(hands[2], position3, M_PI);
        hand(hands[3], position4);
    };

    params.callbacks.ShowGui = guiFunction;
    HelloImGui::Run(params);
    return 0;
}

// if (ImGui::Button("Bye!"))
//     HelloImGui::GetRunnerParams()->appShallExit = true;
