#include "Framebuffer.h"

namespace engine
{
	void Framebuffer::CreateDepthBuffer(uint32_t width, uint32_t height)
	{
		m_width = width;
		m_height = height;

		glGenFramebuffers(1, &m_id);

		m_texture.CreateDepthTexture(width, height);

		glBindFramebuffer(GL_FRAMEBUFFER, m_id);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_texture.GetId(), 0);
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

	}

	void Framebuffer::Destroy()
	{
		glDeleteFramebuffers(1, &m_id);
		m_texture.Destroy();
	}

	void Framebuffer::Bind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_id);
	}

	void Framebuffer::Unbind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}