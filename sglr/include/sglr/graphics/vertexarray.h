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
		void const bind();
		void const unbind();
		void const destroy();

	private:
		GLuint m_varrID{};
	};

}