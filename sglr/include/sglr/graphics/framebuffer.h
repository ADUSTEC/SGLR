#pragma once

#include <GL/glew.h>
#include <glm.hpp>

namespace sglr
{
	class framebuffer
	{
	public:
		framebuffer(glm::vec2 size);
		~framebuffer();
		void bind() const;
		void unbind() const;
		void destroy() const;
		GLuint returnFrame();
		void rescale(glm::vec2 size);
	private:
		GLuint fbo = NULL;
		GLuint texture = NULL;
		GLuint rbo = NULL;
	};

}