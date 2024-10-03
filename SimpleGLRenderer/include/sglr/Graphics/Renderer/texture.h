#pragma once
#include <GL/glew.h>
#include "../shader.h"

#define SGLR_TEXTURE_FILTERMODE_LINEAR 0x2601
#define SGLR_TEXTURE_FILTERMODE_NEAREST 0x2600

namespace sglr
{
	class texture
	{
	public:
		texture(const char* file, int index, int filtermode = SGLR_TEXTURE_FILTERMODE_LINEAR);
		~texture();

		void const bind();
		void const unbind();
		void const destroy();

		void const textureIndex(shader* shader, const char* name, int unit);

		GLuint getTexture() { return m_textureid; }

	private:
		int m_imgw, m_imgh, m_imgcolch;
		unsigned char* m_bytes;
		int m_unit;

		GLuint m_textureid;
	};

}