#include "sglr/graphics/vertexarray.h"

namespace sglr
{

	vertexarray::vertexarray()
	{
		glGenVertexArrays(1, &m_varrID); // generate vao
	}
	vertexarray::~vertexarray()
	{
		destroy();
	}

	void vertexarray::link(vertexbuffer& vbuffer, GLuint lindex, GLuint compnum, GLenum datatype, GLsizeiptr vattoffset, GLuint offset)
	{
		vbuffer.bind(); // bind vbo

		//// vertex attribute - used mainly for the "layout" in a shader
		// 
		// index      : specifies the desired attribute location index of which is defined in the shader
		//
		// size       : stored number of components per variable (float = 1, vec2 = 2, vec3 = 3, vec4 = 4, etc.)
		//
		// type       : determines the data type of a variable (float, int, etc.)
		//
		// normalized : if enabled the maximum possible value is normalized to 1.0, and the most minimal value to 0.0
		//
		// stride     : the total stored data count in each vertice * its datatype (if only 3 floats are stored then the stride is 3 * the size of its datatype)
		// (etc..)    : (i.e. if only an xy (vec2) value is stored - stride = 2, if xyz & uv (vec3 value + a vec2 value) values are stored - stride = 6)
		//
		// pointer    : Offset in the index based on the component size & datatype size of the previously defined vertex attributes. 
		// (etc..)    :	(if first attribute has the size set to 3, then the second attribute will start at an offset of 3 * the size of its datatype)
		// (etc..)    : (i.e. attribute1(size = 3, offset = 0) -> attribute2(size = 2, offset = 3) -> attribute3(size = 1, offset = 5))
		// 
		/////////////// easy to understand explaination of how glVertexAttribPointer() parameters are used ////////////////
		
		glVertexAttribPointer(lindex, compnum, datatype, GL_FALSE, vattoffset * sizeof(datatype), (void*)(offset * sizeof(datatype)));
		glEnableVertexAttribArray(lindex); // enable attribute at defined index

		vbuffer.unbind(); // unbind vbo
	}

	void const vertexarray::bind()
	{
		glBindVertexArray(m_varrID); // bind vao
	}
	void const vertexarray::unbind()
	{
		glBindVertexArray(0); // unbind curently binded vao
	}

	void const vertexarray::destroy()
	{
		glDeleteVertexArrays(1, &m_varrID); // delete vao
	}


}