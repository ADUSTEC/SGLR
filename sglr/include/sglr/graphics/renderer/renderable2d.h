#pragma once

#include <glm.hpp>

namespace sglr
{
	struct vertexdata2d
	{
		glm::vec3 vertexpos;
	};

	class renderable2d 
	{
	public:
		renderable2d(const glm::vec3& position, const glm::vec2& size)
			: m_positionxyz(position), m_sizexy(size)
		{}

		inline glm::vec3 getPosition() const { return m_positionxyz; }
		inline void setPosition(glm::vec3 position) { m_positionxyz = position; }

		inline glm::vec2 getSize() const { return m_sizexy; }
		inline void setSize(glm::vec2 size) { m_sizexy = size; }
	protected:
		glm::vec3 m_positionxyz;
		glm::vec2 m_sizexy;
	};

}