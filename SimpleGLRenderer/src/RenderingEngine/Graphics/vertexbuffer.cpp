#include "vertexbuffer.h"

namespace SGLR
{

	vertexbuffer::vertexbuffer(GLfloat* vertexdata, GLsizeiptr size)
	{
		// vbo generation
		glGenBuffers(1, &m_vbufferID);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbufferID);
		glBufferData(GL_ARRAY_BUFFER, size, vertexdata, GL_STATIC_DRAW);
	}

	vertexbuffer::~vertexbuffer()
	{
		destroy();
	}

	void const vertexbuffer::bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_vbufferID); // bind vbo
	}

	void const vertexbuffer::unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0); // unbind currently binded vbo
	}

	void const vertexbuffer::destroy()
	{
		glDeleteBuffers(1, &m_vbufferID); // delete vbo
	}

}