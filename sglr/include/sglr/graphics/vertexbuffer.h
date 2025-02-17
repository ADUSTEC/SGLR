#pragma once
#include <GL/glew.h>
#include <vector>
#include <glm.hpp>

namespace sglr
{

	class vertexbuffer
	{
		public:
			vertexbuffer(GLfloat* vertexdata, GLsizeiptr size);
			vertexbuffer(GLsizeiptr size);
			~vertexbuffer();

			// binding and cleanup
			inline void bind() const
			{
				glBindBuffer(GL_ARRAY_BUFFER, m_vbufferID); // bind vbo
			}
			inline void unbind() const
			{
				glBindBuffer(GL_ARRAY_BUFFER, 0); // unbind currently binded vbo
			}

			inline void assign(const void* data, uint32_t size) const
			{
				bind();
				glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
				unbind();
			}

			inline void destroy() const
			{
				glDeleteBuffers(1, &m_vbufferID); // delete vbo
			}

		private:
			GLuint m_vbufferID{};
	};

}