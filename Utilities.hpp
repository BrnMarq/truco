#include "hello_imgui/hello_imgui.h"

template<typename T> static inline T ImMin(T lhs, T rhs) { return lhs < rhs ? lhs : rhs; }
template<typename T> static inline T ImMax(T lhs, T rhs) { return lhs >= rhs ? lhs : rhs; }

ImVec2 ImRotate(const ImVec2& v, float cos_a, float sin_a) {
  return ImVec2(v.x * cos_a - v.y * sin_a, v.x * sin_a + v.y * cos_a);
}

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
		l = ImVec2(ImMin(l.x, buf[i].pos.x), ImMin(l.y, buf[i].pos.y));
    u = ImVec2(ImMax(l.x, buf[i].pos.x), ImMax(l.y, buf[i].pos.y));
  }

	return ImVec2((l.x+u.x)/2, (l.y+u.y)/2); // or use _ClipRectStack?
}

ImVec2 operator-(const ImVec2& l, const ImVec2& r) { return{ l.x - r.x, l.y - r.y }; }

void ImRotateEnd(float rad, ImVec2 center = ImRotationCenter())
{
	float s=sin(rad), c=cos(rad);
	center = ImRotate(center, s, c) - center;

	auto& buf = ImGui::GetWindowDrawList()->VtxBuffer;
	for (int i = rotation_start_index; i < buf.Size; i++)
		buf[i].pos = ImRotate(buf[i].pos, s, c) - center;
}