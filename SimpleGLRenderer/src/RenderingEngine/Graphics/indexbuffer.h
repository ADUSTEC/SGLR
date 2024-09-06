#pragma once
#include <GL/glew.h>

namespace SGLR
{

	class indexbuffer
	{
	public:
		indexbuffer(GLuint* indices, GLsizeiptr size);
		~indexbuffer();

		// binding and cleanup
		void const bind();
		void const unbind();
		void const destroy();

	private:
		GLuint m_ibufferID{};
	};

}