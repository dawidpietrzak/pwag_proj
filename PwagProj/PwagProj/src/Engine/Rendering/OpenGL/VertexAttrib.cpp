#include "VertexAttrib.h"

namespace engine
{
	VertexAttrib::VertexAttrib()
	{
		
	}

	VertexAttrib::~VertexAttrib()
	{

	}

	void VertexAttrib::Create(const std::vector<GLuint>& count)
	{
		m_layout = count;
		m_stride = 0;
		for (size_t i = 0; i < m_layout.size(); i++)
		{
			m_stride += m_layout[i] * sizeof(GLfloat);
		}
	}

	void VertexAttrib::Bind()
	{
		size_t currentOffset = 0;
		for (size_t i = 0; i < m_layout.size(); i++)
		{
			glVertexAttribPointer((GLuint)i, m_layout[i], GL_FLOAT, GL_FALSE, m_stride, (void*)currentOffset);
			glEnableVertexAttribArray((GLuint)i);
			currentOffset += (size_t)m_layout[i] * sizeof(GLfloat);
		}
	}

	void VertexAttrib::Unbind()
	{
		for (size_t i = 0; i < m_layout.size(); i++)
		{
			glDisableVertexAttribArray((GLuint)i);
		}
	}
}