#include "hello_imgui/hello_imgui.h"
#include "src/lib/include/CardDeck.hpp"
#include <time.h>

class Config
{
public:
  static constexpr char* title = (char*)"Truco Venezolano";
  static constexpr ImVec2 default_card_size = ImVec2(100.0F, 153.5F);
  static constexpr int card_spacing = 108;
  static constexpr int game_delay = 70;
  static constexpr bool idling = false;
  static constexpr ImVec4 background_color = ImVec4(0/255.0F, 112/255.0F, 30/255.0F, 0.0F);
  static constexpr HelloImGui::FullScreenMode screen_mode = HelloImGui::FullScreenMode::FullMonitorWorkArea;
};
