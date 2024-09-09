#include "shader.h"

namespace SGLR 
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
				LOG_ERROR("OPENGL ERROR: FRAGMENT SHADER FAILED TO COMPILE {}", &error[0]);
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

	void const shader::enable()
	{
		glUseProgram(m_shaderID); // enable shader for use
	}

	void const shader::disable()
	{
		glUseProgram(0); // disable shader
	}

	void const shader::destroy()
	{
		glDeleteProgram(m_shaderID); // delete shader program
	}

	// UNIFORMS
	void shader::setUniformFloat(const GLchar* name, float value)
	{
		glUniform1f(getUniformLocation(name), value);
	}

	void shader::setUniformFloatV(const GLchar* name, float* value, int count)
	{
		glUniform1fv(getUniformLocation(name), count, value);
	}

	void shader::setUniformVec2(const GLchar* name, const glm::vec2& vector)
	{
		glUniform2f(getUniformLocation(name), vector.x, vector.y);
	}

	void shader::setUniformVec3(const GLchar* name, const glm::vec3& vector)
	{
		glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);
	}

	void shader::setUniformVec4(const GLchar* name, const glm::vec4& vector)
	{
		glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
	}

	void shader::setUniformInt(const GLchar* name, int value)
	{
		glUniform1i(getUniformLocation(name), value);
	}

	void shader::setUniformIntV(const GLchar* name, int* value, int count)
	{
		glUniform1iv(getUniformLocation(name), count, value);
	}

	void shader::setUniformMat4(const GLchar* name, const glm::mat4& matrix)
	{
		glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
	}

}