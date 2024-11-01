#pragma once

#include "../core/log/log.h"
#include "../tools/readfile.h"
#include <glm.hpp>
#include <ext.hpp>
#include <GL/glew.h>

namespace sglr
{
	class shader 
	{
	public:
		shader(const char* vertexshader, const char* fragmentshader);
		~shader();

		// binding and cleanup
		void const enable();
		void const disable();
		void const destroy();

		// float uniform
		void setUniformFloat(const GLchar* name, float value);
		void setUniformFloatV(const GLchar* name, float* value, int count);
		void setUniformVec2(const GLchar* name, const glm::vec2& vector);
		void setUniformVec3(const GLchar* name, const glm::vec3& vector);
		void setUniformVec4(const GLchar* name, const glm::vec4& vector);
		
		// int uniform
		void setUniformInt(const GLchar* name, int value);
		void setUniformIntV(const GLchar* name, int* value, int count);

		// matrix uniform
		void setUniformMat4(const GLchar* name, const glm::mat4& matrix);

		GLuint const program() { return m_program; }
		GLint getUniformLocation(const GLchar* name) { return glGetUniformLocation(m_shaderID, name); }
	private:
		GLuint m_shaderID;
		const char* m_vertexp, * m_fragmentp;
		GLuint m_program;

		GLuint load();
	};

}