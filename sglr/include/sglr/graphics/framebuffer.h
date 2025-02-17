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
		
		void rescale(glm::vec2 size) const;

		inline GLuint returnFrame() const
		{
			return m_texture;
		}
		inline void bind() const
		{
			glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
		}
		inline void unbind() const
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
		inline void destroy() const
		{
			glDeleteFramebuffers(1, &m_fbo);
		}
		
	private:
		GLuint m_fbo;
		GLuint m_texture;
		GLuint m_rbo;
	};

}