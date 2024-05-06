#include "hello_imgui/hello_imgui.h"
#include "src/lib/include/Settings.hpp"
#include "src/lib/include/RenderUtilities.hpp"
#include "src/lib/include/CardDeck.hpp"

int main(int , char *[])
{
    auto guiFunction = [&]() {
        ImVec2 vec(100.0F, 153.5F);
        rng_t mt(time(nullptr));
        CardDeck deck = CardDeck::create_random_unique_deck(mt, 3, true);

        for (const auto& card: deck) {
            HelloImGui::ImageFromAsset(get_card_image(card).c_str(), vec); ImGui::SameLine();
        }

        if (ImGui::Button("Bye!"))
            HelloImGui::GetRunnerParams()->appShallExit = true;
    };
    HelloImGui::Run(guiFunction, "Truco Venezolano");
    return 0;
}
