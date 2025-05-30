#include "sglr/graphics/renderer/texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "sglr/core/log/log.h"

namespace sglr
{

	texture::texture(const char* file, int desc, uint16_t index, int filtermode)
	{
		m_texturedesc = desc;
		stbi_set_flip_vertically_on_load(true);

		m_bytes = stbi_load(file, &m_imgw, &m_imgh, &m_imgcolch, 0);
		if (m_bytes == nullptr)
		{
			LOG_WARN("TEXTURE ERROR: FAILED TO LOAD FILE FROM LOCATION {}", file);
			m_bytes = stbi_load("textures/sglr/t_missingtexture.png", &m_imgw, &m_imgh, &m_imgcolch, 0);
		}


		glGenTextures(1, &m_textureid);
		glActiveTexture(GL_TEXTURE + index);
		m_index = index;
		glBindTexture(GL_TEXTURE_2D, m_textureid);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filtermode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filtermode);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		// try to define the texture color format based on m_imgcolch
		switch (m_imgcolch)
		{
		case 4:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_imgw, m_imgh, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_bytes);
			break;
		case 3:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_imgw, m_imgh, 0, GL_RGB, GL_UNSIGNED_BYTE, m_bytes);
			break;
		case 1:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_imgw, m_imgh, 0, GL_RED, GL_UNSIGNED_BYTE, m_bytes);
			break;
		default:
			LOG_ASSERT(false, "TEXTURE ERROR: UNKNOWN IMAGE COLOR FORMAT");
		}

		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(m_bytes);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	texture::~texture()
	{
		destroy();
	}

	void texture::textureIndex(shader* shader, const char* name, uint16_t index) const
	{
		shader->enable();
		shader->setUniformInt(name, index);
		shader->disable();
	}

}