#pragma once
#include <GL/glew.h>

namespace sglr
{

	class vertexbuffer
	{
		public:
			vertexbuffer(GLfloat* vertexdata, GLsizeiptr size);
			~vertexbuffer();

			// binding and cleanup
			void const bind();
			void const unbind();

			void const destroy();

		private:
			GLuint m_vbufferID{};
	};

}