#pragma once

#include <cstdint>
#include <Engine/Rendering/OpenGL/Framebuffer.h>

namespace engine
{
	class Viewport
	{
	public:
		static void Initialize(uint32_t defaultWidth, uint32_t defaultHeight);
		static void SetFromFramebufferSize(const Framebuffer& framebuffer);
		static void SetDefaultSize();

	private:
		static uint32_t s_defaultWidth;
		static uint32_t s_defaultHeight;
	};
}