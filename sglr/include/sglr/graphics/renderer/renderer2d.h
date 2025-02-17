#pragma once

// 2d batch renderer, intended use for the billboard class and postprocessing class
// could potentially be used in scene, but is not intended.

#include "renderable2d.h"
#include "../indexbuffer.h"
#include "../vertexbuffer.h"
#include "../vertexarray.h"
#include "../shader.h"

namespace sglr
{
	class renderer2d
	{
	public:
		renderer2d(shader* shader);
		~renderer2d();
		
		void begin();

		void draw(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);

		void end();
		void flush();
	private:
		bool m_init();

		shader* m_shader;

		int m_success = 1;
		std::string m_initFailReason = "";
	};
}