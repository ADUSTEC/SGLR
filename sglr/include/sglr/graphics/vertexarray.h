#pragma once
#include "vertexbuffer.h"
#include <GL/glew.h>

namespace sglr
{
	class vertexarray
	{
	public:
		vertexarray();
		~vertexarray();

		void link(vertexbuffer& vbuffer, GLuint lindex, GLuint compnum, GLenum datatype, GLsizeiptr vattoffset, GLuint offset);

		// binding and cleanup
		inline void bind() const
		{
			glBindVertexArray(m_varrID); // bind vao
		}
		inline void unbind() const
		{
			glBindVertexArray(0); // unbind curently binded vao
		}
		inline void destroy() const
		{
			glDeleteVertexArrays(1, &m_varrID); // delete vao
		}

	private:
		GLuint m_varrID{};
	};

}