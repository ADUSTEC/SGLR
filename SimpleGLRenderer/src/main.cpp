#include "RenderingEngine/renderengine.h"


class renderApp : public SGLR::Application
{
	private:

		GLfloat vertices[12] = 
		{
			 0.5f,  0.5f, 0.0f,  // top right
			 0.5f, -0.5f, 0.0f,  // bottom right
			-0.5f, -0.5f, 0.0f,  // bottom left
			-0.5f,  0.5f, 0.0f   // top left 
		};

		GLuint indices[6]
		{
			0, 1, 3,
			1, 2, 3
		};

		SGLR::shader* shaders = nullptr;

		SGLR::vertexarray* vao;
		SGLR::vertexbuffer* vbo;
		SGLR::indexbuffer* ibo;

	public:
		renderApp() {}
		~renderApp() 
		{
			vao->destroy();
			vbo->destroy();
			ibo->destroy();
			shaders->destroy();

			delete shaders;
			delete vao;
			delete vbo;
			delete ibo;
		}

		void onInit() override
		{
			shaders = new SGLR::shader("shaders/basic_v.glsl", "shaders/basic_f.glsl");

			vao = new SGLR::vertexarray();

			vao->bind();

			vbo = new SGLR::vertexbuffer(vertices, sizeof(vertices));

			ibo = new SGLR::indexbuffer(indices, sizeof(indices));
			ibo->bind();

			vao->link(*vbo, 0, 3, GL_FLOAT, 3, 0);

			vao->unbind();
			vbo->unbind();
			ibo->unbind();

		}

		void onRender(float deltaTime) override
		{
			
			shaders->enable();

			vao->bind();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		}

		void onUpdate(float deltaTime) override
		{}

		void onTick(float deltaTime) override
		{}

};

int main(int argc, char** argv)
{
	SGLR::Log::Init(); // Initialize logger
	
	renderApp app;
	app.start();
	
	SGLR::Log::Shutdown(); // Destroy

	return 0;
}