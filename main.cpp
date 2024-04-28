#include "hello_imgui/hello_imgui.h"

int main(int , char *[])
{
    auto guiFunction = []() {
        ImVec2 vec(0, 0);
        ImVec2 vec2(1, 1);
        ImVec2 vec3(1, 0);
        ImVec2 vec4(0, 1);

        HelloImGui::ImageFromAsset("images/espadilla.png", vec2); ImGui::SameLine();
        HelloImGui::ImageFromAsset("images/espadilla.png"); ImGui::SameLine();
        HelloImGui::ImageFromAsset("images/espadilla.png"); ImGui::SameLine();
        if (ImGui::Button("Bye!"))
            HelloImGui::GetRunnerParams()->appShallExit = true;
    };
    HelloImGui::Run(guiFunction, "Trucardovich");
    return 0;
}
