#pragma once
#include <GL/glew.h>
#include <vector>

namespace sglr
{
	class indexbuffer
	{
	public:
		indexbuffer(GLuint* indices, GLsizeiptr size); // array
		~indexbuffer();

		// binding and cleanup
		inline void bind() const
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibufferID); // bind ibo
		}
		inline void unbind() const
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // unbind currently binded ibo
		}
		inline void destroy() const
		{
			glDeleteBuffers(1, &m_ibufferID); // delete ibo
		}

	private:
		GLuint m_ibufferID{};
	};

}