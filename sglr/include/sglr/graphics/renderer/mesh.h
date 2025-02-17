#pragma once
#include "../shader.h"
#include "../vertexarray.h"
#include "../vertexbuffer.h"
#include "../indexbuffer.h"
#include "texture.h"

#include <string>
#include <vector>

namespace sglr
{
    struct vertexdata
    {
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texcoord;
    };

    class mesh
    {
    public:
        mesh(shader* shader, vertexdata* vertices, GLuint* indices, texture* textures);
        ~mesh();

        void draw();

    private:
        vertexarray*  m_vao;
        vertexbuffer* m_vbo;
        indexbuffer*  m_ibo;
        shader* shader;
    };
}
