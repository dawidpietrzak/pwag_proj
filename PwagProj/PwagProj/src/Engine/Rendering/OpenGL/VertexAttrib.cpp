#include "VertexAttrib.h"

namespace engine
{
	VertexAttrib::VertexAttrib()
	{
		
	}

	VertexAttrib::~VertexAttrib()
	{

	}

	void VertexAttrib::Create(const std::vector<VertexAttribLayout>& layout)
	{
		m_layout = layout;
		m_stride = 0;
		for (size_t i = 0; i < m_layout.size(); i++)
		{
			m_stride += m_layout[i].FloatsNumber * sizeof(GLfloat);
		}
	}

	void VertexAttrib::Bind() const
	{
		size_t currentOffset = 0;
		for (size_t i = 0; i < m_layout.size(); i++)
		{
			const VertexAttribLayout& layout = m_layout[i];
			glVertexAttribPointer((GLuint)layout.LayoutIndex, layout.FloatsNumber, GL_FLOAT, GL_FALSE, m_stride, (void*)currentOffset);
			glEnableVertexAttribArray((GLuint)layout.LayoutIndex);
			if (layout.Divisor > 0)
			{
				glVertexAttribDivisor((GLuint)layout.LayoutIndex, layout.Divisor);
			}
			currentOffset += (size_t)layout.FloatsNumber * sizeof(GLfloat);
		}
	}

	void VertexAttrib::Unbind() const
	{
		for (size_t i = 0; i < m_layout.size(); i++)
		{
			glDisableVertexAttribArray((GLuint)i);
		}
	}
}