#include "sglr/graphics/indexbuffer.h"

namespace sglr
{

	indexbuffer::indexbuffer(GLuint* indices, GLsizeiptr size)
	{
		// ibo generation
		glGenBuffers(1, &m_ibufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
	}

	indexbuffer::~indexbuffer() 
	{
		destroy();
	}

}