#include "sglr/graphics/shader.h"

namespace sglr
{

	shader::shader(const char* vertexshader, const char* fragmentshader)
		: m_vertexp(vertexshader), m_fragmentp(fragmentshader)
	{
		m_shaderID = load(); // load shaders and create shader program
	}

	shader::~shader()
	{
		destroy(); // delete shaders
	}

	GLuint shader::load()
	{
		// Create shader program
		GLuint program = glCreateProgram();
		m_program = program; 
		
		// Assign shader types to variables
		GLuint vertex = glCreateShader(GL_VERTEX_SHADER); 
		GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER); 

		// load shader from specified paths
		const char* vertShader = file::read(m_vertexp); 
		const char* fragShader = file::read(m_fragmentp);

		// compile shader
		glShaderSource(vertex, 1, &vertShader, NULL); 
		glCompileShader(vertex);

		// detect any errors if any
		GLint result;

		glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);
		switch (result)
		{
			case GL_FALSE:
			{
				GLint length;
				glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
				std::vector<char> error(length);
				glGetShaderInfoLog(vertex, length, &length, &error[0]);
				LOG_ERROR("OPENGL ERROR: VERTEX SHADER FAILED TO COMPILE {}", &error[0]);
				glDeleteShader(vertex);
				return 0;
				break;
			}
		}

		// compile shader
		glShaderSource(fragment, 1, &fragShader, NULL);
		glCompileShader(fragment);

		// detect any errors if any
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);
		switch (result)
		{
			case GL_FALSE:
			{
				GLint length;
				glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
				std::vector<char> error(length);
				glGetShaderInfoLog(fragment, length, &length, &error[0]);
				LOG_ERROR("OPENGL ERROR: FRAGMENT SHADER FAILED TO COMPILE \n{}", &error[0]);
				glDeleteShader(fragment);
				return 0;
				break;
			}
		}

		// assign shaders to program
		glAttachShader(program, vertex); 
		glAttachShader(program, fragment); 

		// link program
		glLinkProgram(program);
		glValidateProgram(program);

		// cleanup
		glDeleteShader(vertex); 
		glDeleteShader(fragment); 
		return program;
	}

	GLint shader::getUniformLocation(const GLchar* name) const
	{
		auto it = m_uniformloc.find(name);
		if (it != m_uniformloc.end()) return it->second;
		GLint location = glGetUniformLocation(m_shaderID, name);
		if (location == -1) {
			LOG_ERROR("OPENGL ERROR: UNIFORM {} NOT FOUND", name);
		}
		return m_uniformloc[name] = location;
	}

}