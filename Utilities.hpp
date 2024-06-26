#include "hello_imgui/hello_imgui.h"
#include "imgui_internal.h"

int rotation_start_index; 
void ImRotateStart() 
{ 
	rotation_start_index = ImGui::GetWindowDrawList()->VtxBuffer.Size; 
}

ImVec2 ImRotationCenter()
{
	ImVec2 l(FLT_MAX, FLT_MAX), u(-FLT_MAX, -FLT_MAX); // bounds

	const auto& buf = ImGui::GetWindowDrawList()->VtxBuffer;
	for (int i = rotation_start_index; i < buf.Size; i++) {
		l = ImVec2(ImMin(l, buf[i].pos));
    u = ImVec2(ImMax(u, buf[i].pos));
  }

	return ImVec2((l.x+u.x)/2, (l.y+u.y)/2); // or use _ClipRectStack?
}

void ImRotateEnd(float rad, ImVec2 center = ImRotationCenter())
{
	float s=sin(rad), c=cos(rad);
	center = ImRotate(center, s, c) - center;

	auto& buf = ImGui::GetWindowDrawList()->VtxBuffer;
	for (int i = rotation_start_index; i < buf.Size; i++)
		buf[i].pos = ImRotate(buf[i].pos, s, c) - center;
}