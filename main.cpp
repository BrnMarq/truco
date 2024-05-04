#include "hello_imgui/hello_imgui.h"
#include "src/lib/include/Settings.hpp"
#include "src/lib/include/RenderUtilities.hpp"
#include "src/lib/include/CardDeck.hpp"

int main(int , char *[])
{
    std::list<int> t;
    auto y = t.begin();
    rng_t mt(time(nullptr));
    CardDeck deck = CardDeck::create_random_unique_deck(mt, 3, true);
    auto guiFunction = [&]() {
        ImVec2 vec(0, 0);
        ImVec2 vec2(1, 1);
        ImVec2 vec3(1, 0);
        ImVec2 vec4(0, 1);

        for (const auto& card: deck) {
            HelloImGui::ImageFromAsset(get_card_image(card).c_str()); ImGui::SameLine();
        }

        if (ImGui::Button("Bye!"))
            HelloImGui::GetRunnerParams()->appShallExit = true;
    };
    HelloImGui::Run(guiFunction, Settings::hand_size == 8 ? "Truquito" : "Truco");
    return 0;
}
