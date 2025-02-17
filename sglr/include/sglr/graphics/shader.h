#pragma once

#include "../core/log/log.h"
#include "../tools/readfile.h"
#include <glm.hpp>
#include <ext.hpp>
#include <GL/glew.h>
#include <unordered_map>

namespace sglr
{
	class shader 
	{
	public:
		shader(const char* vertexshader, const char* fragmentshader);
		~shader();

		// binding and cleanup
		inline void enable() const
		{
			glUseProgram(m_shaderID); // enable shader for use
		}
		inline void disable() const
		{
			glUseProgram(0); // disable shader
		}
		inline void destroy() const
		{
			glDeleteProgram(m_shaderID); // delete shader program
		}

		////////// Uniforms //////////
		// float

		inline void setUniformFloat(const GLchar* name, float value) const
		{
			glUniform1f(getUniformLocation(name), value);
		}
		inline void setUniformFloatV(const GLchar* name, float* value, int count) const
		{
			glUniform1fv(getUniformLocation(name), count, value);
		}
		inline void setUniformVec2(const GLchar* name, const glm::vec2& vector) const
		{
			glUniform2f(getUniformLocation(name), vector.x, vector.y);
		}
		inline void setUniformVec3(const GLchar* name, const glm::vec3& vector) const
		{
			glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);
		}
		inline void setUniformVec4(const GLchar* name, const glm::vec4& vector) const
		{
			glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
		}
		
		// int

		inline void setUniformInt(const GLchar* name, int value) const
		{
			glUniform1i(getUniformLocation(name), value);
		}
		inline void setUniformIntV(const GLchar* name, int* value, int count) const
		{
			glUniform1iv(getUniformLocation(name), count, value);
		}

		// matrix

		inline void setUniformMat4(const GLchar* name, const glm::mat4& matrix) const
		{
			glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
		}

		inline void setUniformMat4(const GLchar* name, const glm::mat3& matrix) const
		{
			glUniformMatrix3fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
		}

		inline void setUniformMat2(const GLchar* name, const glm::mat2& matrix) const
		{
			glUniformMatrix2fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
		}

		inline GLuint program() const { return m_program; }
	private:
		GLuint m_shaderID;
		const char* m_vertexp, * m_fragmentp;
		GLuint m_program;
		mutable std::unordered_map<const GLchar*, GLint> m_uniformloc;

		GLuint load();
		GLint getUniformLocation(const GLchar* name) const;
	};

}