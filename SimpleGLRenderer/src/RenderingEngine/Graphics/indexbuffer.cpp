#include "indexbuffer.h"

namespace SGLR
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


	void const indexbuffer::bind() 
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibufferID); // bind ibo
	}

	void const indexbuffer::unbind() 
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // unbind currently binded ibo
	}

	void const indexbuffer::destroy() 
	{
		glDeleteBuffers(1, &m_ibufferID); // delete ibo
	}

	

}