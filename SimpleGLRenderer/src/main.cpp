#include "RenderingEngine/renderengine.h"



class renderApp : public SGLR::Application
{
	private:
		const char* vertexShaderSource = SGLR::file::read("shaders/basic_v.glsl");

		const char* fragmentShaderSource = SGLR::file::read("shaders/basic_f.glsl");

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

		GLuint vertexShader;

		GLuint fragmentShader;

		GLuint shaderProgram;


		GLuint vbo;
		GLuint ebo;
		GLuint vao;

	public:
		renderApp() {}
		~renderApp() {}

		void onInit() override
		{

			vertexShader = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
			glCompileShader(vertexShader);

			fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
			glCompileShader(fragmentShader);

			shaderProgram = glCreateProgram();

			glAttachShader(shaderProgram, vertexShader);
			glAttachShader(shaderProgram, fragmentShader);
			glLinkProgram(shaderProgram);

			glGenBuffers(1, &vbo);
			glGenBuffers(1, &ebo);

			glGenVertexArrays(1, &vao);

			glBindVertexArray(vao);

			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);

		}

		void onRender(float deltaTime) override
		{
			
			glUseProgram(shaderProgram);
			glBindVertexArray(vao);

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);

			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

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