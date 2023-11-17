#include "Viewport.h"

namespace engine
{
	uint32_t Viewport::s_defaultWidth = 1024;
	uint32_t Viewport::s_defaultHeight = 1024;

	void Viewport::Initialize(uint32_t defaultWidth, uint32_t defaultHeight)
	{
		s_defaultWidth = defaultWidth;
		s_defaultHeight = defaultHeight;
	}

	void Viewport::SetFromFramebufferSize(const Framebuffer& framebuffer)
	{
		glViewport(0, 0, framebuffer.GetWidth(), framebuffer.GetHeight());
	}

	void Viewport::SetDefaultSize()
	{
		glViewport(0, 0, s_defaultWidth, s_defaultHeight);
	}
}