#pragma once
#include <GL/glew.h>

namespace SGLR
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