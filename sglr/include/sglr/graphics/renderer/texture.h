#pragma once
#include <GL/glew.h>
#include "../shader.h"

#define SGLR_TEXTURETYPE_DIFFUSE 0x2604
#define SGLR_TEXTURETYPE_SPECULAR 0x2603
#define SGLR_TEXTURETYPE_NORMAL 0x2602

#define SGLR_TEXTURE_FILTERMODE_LINEAR 0x2601
#define SGLR_TEXTURE_FILTERMODE_NEAREST 0x2600

namespace sglr
{
	class texture
	{
	public:
		texture(const char* file, int desc, uint16_t index, int filtermode = SGLR_TEXTURE_FILTERMODE_LINEAR);
		~texture();

		inline void bind() const
		{
			glActiveTexture(GL_TEXTURE0 + m_index);
			glBindTexture(GL_TEXTURE_2D, m_textureid);
		}
		inline void unbind() const
		{
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		inline void destroy() const
		{
			glDeleteTextures(1, &m_textureid);
		}

		void textureIndex(shader* shader, const char* name, uint16_t index) const;

		inline GLuint getTexture() { return m_textureid; }
		inline GLuint getTextureDescription() { return m_texturedesc; }

	private:
		int m_imgw, m_imgh, m_imgcolch;
		unsigned char* m_bytes;
		uint16_t m_index;

		GLuint m_textureid;
		int m_texturedesc;
	};

}