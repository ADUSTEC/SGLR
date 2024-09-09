#pragma once
#include <GL/glew.h>

#define SGLR_TEXTURE_FILTERMODE_LINEAR 0x2601
#define SGLR_TEXTURE_FILTERMODE_NEAREST 0x2600

namespace SGLR
{
	class texture
	{
	public:
		texture(const char* file, int filtermode = SGLR_TEXTURE_FILTERMODE_LINEAR);
		~texture();

		void const bind();
		void const unbind();
		void const destroy();

	private:
		int m_imgw, m_imgh, m_imgcolch;
		unsigned char* m_bytes;

		GLuint m_textureid;
	};

}