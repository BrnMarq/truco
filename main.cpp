#include "hello_imgui/hello_imgui.h"

int main(int , char *[])
{
    auto guiFunction = []() {
        ImGui::Text("Hello, ");   
        ImVec2 vec(200, 300);
        HelloImGui::ImageFromAsset("images/espadilla.png"); ImGui::SameLine();  // Display a static image
        HelloImGui::ImageFromAsset("images/espadilla.png"); ImGui::SameLine();    // Display a static image
        HelloImGui::ImageFromAsset("images/espadilla.png"); ImGui::SameLine();    // Display a static image
        if (ImGui::Button("Bye!"))                 // Display a button
            // and immediately handle its action if it is clicked!
            HelloImGui::GetRunnerParams()->appShallExit = true;
    };
    HelloImGui::Run(guiFunction, "Trucardovich", true);
    return 0;
}
