#pragma once

#include <GL/glew.h>
#include <vector>

namespace engine
{
	struct VertexAttribLayout
	{
		uint8_t LayoutIndex = 0;
		uint8_t FloatsNumber = 0;
		uint8_t Divisor = 0;

		VertexAttribLayout() { }

		VertexAttribLayout(uint8_t layoutIndex, uint8_t floatsNumber) 
			: LayoutIndex(layoutIndex), FloatsNumber(floatsNumber), Divisor(0) { }

		VertexAttribLayout(uint8_t layoutIndex, uint8_t floatsNumber, uint8_t divisor) 
			: LayoutIndex(layoutIndex), FloatsNumber(floatsNumber), Divisor(divisor) { }
	};

	class VertexAttrib
	{
	public:
		VertexAttrib();
		~VertexAttrib();

		void Create(const std::vector<VertexAttribLayout>& layout);

		void Bind() const;
		void Unbind() const;

	private:
		GLuint m_id = 0;
		GLuint m_stride = 0;
		std::vector<VertexAttribLayout> m_layout;
	};
}



