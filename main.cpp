#define _USE_MATH_DEFINES

#include <math.h>

#include "hello_imgui/hello_imgui.h"
#include "src/lib/include/Settings.hpp"
#include "src/lib/include/RenderUtilities.hpp"
#include "src/lib/include/CardDeck.hpp"
#include "config.hpp"
#include "Utilities.hpp"

int main(int , char *[])
{
    HelloImGui::RunnerParams params;
    ImVec2 card_size = Config::default_card_size;

    params.appWindowParams.windowTitle = Config::title;
    params.imGuiWindowParams.backgroundColor = Config::background_color;
    params.appWindowParams.windowGeometry.fullScreenMode = Config::screen_mode;

    rng_t seed(time(nullptr));
    CardDeck deck = CardDeck::create_random_unique_deck(seed, 3, false);

    auto guiFunction = [&]() {
        ImGui::SameLine((ImGui::GetContentRegionAvail().x / 2) - ((card_size.x * 3) / 2));
        for (const auto& card: deck) {
            HelloImGui::ImageFromAsset(get_card_image(card).c_str(), card_size); ImGui::SameLine();
        }
        int i = 0;
        for (const auto& card: deck) {
            ImGui::SetCursorPos(ImVec2(card_size.y / 2, (((ImGui::GetContentRegionAvail().y / 2) - ((card_size.x * 3) / 2)) + i * card_size.x) +  (i * 8)));
            ImRotateStart();
            HelloImGui::ImageFromAsset(get_card_image(card).c_str(), card_size); ImGui::SameLine();
            ImRotateEnd(M_PI);
            ++i;
        }
        // for (const auto& card: deck) {
        //     ImGui::SetCursorPos(ImVec2(ImGui::GetContentRegionAvail().x + card_size.y - 55, (((ImGui::GetContentRegionAvail().y / 2) - ((card_size.x * 3) / 2)) + i * card_size.x)));
        //     ImRotateStart();
        //     HelloImGui::ImageFromAsset(get_card_image(card).c_str(), card_size); ImGui::SameLine();
        //     ImRotateEnd(M_PI);
        //     ++i;
        // }
    };

    params.callbacks.ShowGui = guiFunction;
    HelloImGui::Run(params);
    return 0;
}

// if (ImGui::Button("Bye!"))
//     HelloImGui::GetRunnerParams()->appShallExit = true;
