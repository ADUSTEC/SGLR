#pragma once

#include "camera.h"
#include "../shader.h"
#include "../vertexbuffer.h"
#include "../vertexarray.h"
#include "../indexbuffer.h"

#include <vector>

namespace sglr
{
	// ----- ideal usage: -----
	// 
	// Create a new billboard:
	// billboard mybillboard(camera, shader);
	// 
	// Add new billboard to batch:
	// mybillboard.createNew(position, size, texture);
	// 
	// ----- ( while loop ) -----
	// 
	// Draw all billboards in batch and call it a day:
	// mybillboard.draw();

	// Batch renderer used for 2D objects in 3D space that always face the camera
	class billboard
	{
	public:
		billboard(shader* shader, camera* camera);
		~billboard();

		void draw();

	private:
		shader* m_shader;
		camera* m_camera;
		vertexbuffer* m_vbo;
		vertexarray* m_vao;
		indexbuffer* m_ibo;
	}; 

}

