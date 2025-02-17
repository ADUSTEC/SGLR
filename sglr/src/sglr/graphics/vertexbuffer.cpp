#include "sglr/graphics/vertexbuffer.h"

namespace sglr
{
	vertexbuffer::vertexbuffer(GLfloat* vertexdata, GLsizeiptr size)
	{
		// vbo generation
		glGenBuffers(1, &m_vbufferID);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbufferID);
		glBufferData(GL_ARRAY_BUFFER, size, vertexdata, GL_STATIC_DRAW);
	}
	
	vertexbuffer::vertexbuffer(GLsizeiptr size)
	{
		// vbo generation
		glGenBuffers(1, &m_vbufferID);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbufferID);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	}

	vertexbuffer::~vertexbuffer()
	{
		destroy();
	}

}