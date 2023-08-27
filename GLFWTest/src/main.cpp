#include "Window.h"

std::vector<Vertex> objectVertices = {
	{ { -1.0f, 0.0f, -1.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f } },
	{ { -1.0f, 0.0f,  1.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 1.0f } },
	{ {  1.0f, 0.0f,  1.0f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 1.0f } },
	{ {  1.0f, 0.0f, -1.0f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 0.0f } },
};

std::vector<unsigned int> objectIndecies = {
	0, 1, 2, 2, 3, 0
};

std::vector<Vertex> planeVertices = {
	{ { -0.5f, 0.0f, -0.5f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f } },
	{ { -0.5f, 0.0f,  0.5f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 1.0f } },
	{ {  0.5f, 0.0f,  0.5f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 0.0f } },
	{ {  0.5f, 0.0f, -0.5f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 1.0f } },
};

std::vector<unsigned int> planeIndecies = {
	0, 1, 2, 2, 3, 0
};

std::vector<Vertex> pyramidVertices = {
	{ { -0.5f, -0.5f, 0.5f }, { -0.5f, -0.5f, 0.5f }, { 0.0f, 0.0f } },
	{ {  0.5f, -0.5f, 0.5f }, {  0.5f, -0.5f, 0.5f }, { 1.0f, 0.0f } },
	{ {  0.5f,  0.5f, 0.5f }, {  0.5f,  0.5f, 0.5f }, { 0.0f, 1.0f } },
	{ { -0.5f,  0.5f, 0.5f }, { -0.5f,  0.5f, 0.5f }, { 1.0f, 1.0f } },

	{ { -0.5f, -0.5f, -0.5f }, { -0.5f, -0.5f, -0.5f }, { 0.0f, 0.0f } },
	{ {  0.5f, -0.5f, -0.5f }, {  0.5f, -0.5f, -0.5f }, { 1.0f, 0.0f } },
	{ {  0.5f,  0.5f, -0.5f }, {  0.5f,  0.5f, -0.5f }, { 0.0f, 1.0f } },
	{ { -0.5f,  0.5f, -0.5f }, { -0.5f,  0.5f, -0.5f }, { 1.0f, 1.0f } }
};

std::vector<unsigned int> pyramidIndecies = {
	0, 1, 2, 2, 3, 0,
	5, 4, 7, 7, 6, 5,
	3, 2, 6, 6, 7, 3,
	4, 5, 1, 1, 0, 4,
	4, 0, 3, 3, 7, 4,
	1, 5, 6, 6, 2, 1
};

std::vector<Vertex> lightVertices = {
	{ { -0.5f, -0.5f, 0.5f }, {}, {}},
	{ {  0.5f, -0.5f, 0.5f }, {}, {}},
	{ {  0.5f,  0.5f, 0.5f }, {}, {}},
	{ { -0.5f,  0.5f, 0.5f }, {}, {}},

	{ { -0.5f, -0.5f, -0.5f }, {}, {}},
	{ {  0.5f, -0.5f, -0.5f }, {}, {}},
	{ {  0.5f,  0.5f, -0.5f }, {}, {}},
	{ { -0.5f,  0.5f, -0.5f }, {}, {}}
};

std::vector<unsigned int> lightIndecies = {
	0, 1, 2, 2, 3, 0,
	5, 4, 7, 7, 6, 5,
	3, 2, 6, 6, 7, 3,
	4, 5, 1, 1, 0, 4,
	4, 0, 3, 3, 7, 4,
	1, 5, 6, 6, 2, 1
};

int main()
{
	std::string TITLE = "Testing";
	Window window(5, 35, 1350, 690, TITLE.c_str());
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	Camera camera(window.GetWindow(), 800, 600, 75.0f, 0.1f, 100.0f);
	camera.SetPosition({ 0.0f, 0.0f, 5.0f });
	Renderer renderer;
	Scene scene;

	ShaderProgram defaultShader("res/shaders/default.vert", "res/shaders/default.frag");
	ShaderProgram lightShader("res/shaders/light.vert", "res/shaders/light.frag");
	////////////////////////////
	{
		Entity entity;
		entity.SetVertices(planeVertices);
		entity.SetIndecies(planeIndecies);
		entity.AddTexture("res/textures/planks.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB);
		entity.AddTexture("res/textures/planks_specular.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGB);
		entity.SetRotation({ 90.0f, 0.0f, 0.0f });
		entity.SetScale({ 20.0f, 20.0f, 20.0f });
		entity.SetPosition({ 0.0f, 0.0f, -10.0f });
		scene.AddEntity(entity);
	}
	{
		Entity entity;
		entity.SetVertices(planeVertices);
		entity.SetIndecies(planeIndecies);
		entity.AddTexture("res/textures/planks.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB);
		entity.AddTexture("res/textures/planks_specular.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGB);
		entity.SetRotation({ -90.0f, 0.0f, 0.0f });
		entity.SetScale({ 20.0f, 20.0f, 20.0f });
		entity.SetPosition({ 0.0f, 0.0f, 10.0f });
		scene.AddEntity(entity);
	}
	{
		Entity entity;
		entity.SetVertices(planeVertices);
		entity.SetIndecies(planeIndecies);
		entity.AddTexture("res/textures/planks.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB);
		entity.AddTexture("res/textures/planks_specular.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGB);
		entity.SetRotation({ 0.0f, 0.0f, 90.0f });
		entity.SetScale({ 20.0f, 20.0f, 20.0f });
		entity.SetPosition({ 10.0f, 0.0f, 0.0f });
		scene.AddEntity(entity);
	}
	{
		Entity entity;
		entity.SetVertices(planeVertices);
		entity.SetIndecies(planeIndecies);
		entity.AddTexture("res/textures/planks.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB);
		entity.AddTexture("res/textures/planks_specular.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGB);
		entity.SetRotation({ 0.0f, 0.0f, -90.0f });
		entity.SetScale({ 20.0f, 20.0f, 20.0f });
		entity.SetPosition({ -10.0f, 0.0f, 0.0f });
		scene.AddEntity(entity);
	}
	{
		Entity entity;
		entity.SetVertices(planeVertices);
		entity.SetIndecies(planeIndecies);
		entity.AddTexture("res/textures/planks.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB);
		entity.AddTexture("res/textures/planks_specular.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGB);
		entity.SetScale({ 20.0f, 20.0f, 20.0f });
		entity.SetPosition({ 0.0f, -10.0f, 0.0f });
		scene.AddEntity(entity);
	}
	{
		Entity entity;
		entity.SetVertices(planeVertices);
		entity.SetIndecies(planeIndecies);
		entity.AddTexture("res/textures/planks.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB);
		entity.AddTexture("res/textures/planks_specular.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGB);
		entity.SetRotation({ 180.0f, 0.0f, 0.0f });
		entity.SetScale({ 20.0f, 20.0f, 20.0f });
		entity.SetPosition({ 0.0f, 10.0f, 0.0f });
		scene.AddEntity(entity);
	}
	////////////////////////////
	{
		Entity entity;
		entity.LoadFromFile("res/models/cat.obj");
		entity.AddTexture("res/textures/cat.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB);
		entity.AddTexture("res/textures/cat_specular.jpg", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGB);
		entity.SetPosition({ 0.0f, 0.0f, -1.0f });
		entity.SetShininess(1024.0f);
		scene.AddEntity(entity);
	}

	{
		Entity entity;
		entity.LoadFromFile("res/models/cube.obj");
		entity.AddTexture("res/textures/container.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB);
		entity.AddTexture("res/textures/container_specular.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGB);
		entity.SetPosition({ 5.0f, 0.0f, -1.0f });;
		scene.AddEntity(entity);
	}

	float dt = 1.0f;

	while (!glfwWindowShouldClose(window.GetWindow()) && !(glfwGetKey(window.GetWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS))
	{
		double start = glfwGetTime();

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.Resize(window.GetWidth(), window.GetHeight());
		camera.Update(dt);

		defaultShader.Activate();
		glUniform1i(glGetUniformLocation(defaultShader.GetID(), "numDirLight"), 1);
		glUniform1i(glGetUniformLocation(defaultShader.GetID(), "numPointLight"), 1);
		glUniform1i(glGetUniformLocation(defaultShader.GetID(), "numSpotLight"), 0);

		glUniform3f(glGetUniformLocation(defaultShader.GetID(), "dirLights[0].Direction"), 1.0f, -1.0f, -1.0f);
		glUniform3f(glGetUniformLocation(defaultShader.GetID(), "dirLights[0].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(defaultShader.GetID(), "dirLights[0].diffuse"), 1.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(defaultShader.GetID(), "dirLights[0].specular"), 0.5f, 0.5f, 0.5f);

		glUniform3f(glGetUniformLocation(defaultShader.GetID(), "pointLights[0].Position"), 0.0f, 0.0f, 4.0f);
		glUniform3f(glGetUniformLocation(defaultShader.GetID(), "pointLights[0].ambient"), 0.1f, 0.1f, 0.1f);
		glUniform3f(glGetUniformLocation(defaultShader.GetID(), "pointLights[0].diffuse"), 0.8f, 0.8f, 0.8f);
		glUniform3f(glGetUniformLocation(defaultShader.GetID(), "pointLights[0].specular"), 1.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(defaultShader.GetID(), "pointLights[0].a"), 0.000007f);
		glUniform1f(glGetUniformLocation(defaultShader.GetID(), "pointLights[0].b"), 0.0014f);
		glUniform1f(glGetUniformLocation(defaultShader.GetID(), "pointLights[0].c"), 1.0f);

		glUniform3f(glGetUniformLocation(defaultShader.GetID(), "spotLights[0].Position"), camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
		glUniform3f(glGetUniformLocation(defaultShader.GetID(), "spotLights[0].Direction"), camera.GetOrientation().x, camera.GetOrientation().y, camera.GetOrientation().z);
		glUniform3f(glGetUniformLocation(defaultShader.GetID(), "spotLights[0].ambient"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(defaultShader.GetID(), "spotLights[0].diffuse"), 1.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(defaultShader.GetID(), "spotLights[0].specular"), 1.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(defaultShader.GetID(), "spotLights[0].a"), 0.032f);
		glUniform1f(glGetUniformLocation(defaultShader.GetID(), "spotLights[0].b"), 0.09f);
		glUniform1f(glGetUniformLocation(defaultShader.GetID(), "spotLights[0].c"), 1.0f);
		glUniform1f(glGetUniformLocation(defaultShader.GetID(), "spotLights[0].cutOff"), glm::cos(glm::radians(12.5f)));
		glUniform1f(glGetUniformLocation(defaultShader.GetID(), "spotLights[0].outerCutOff"), glm::cos(glm::radians(17.5f)));
		defaultShader.Deactivate();

		renderer.Render(scene, defaultShader, camera);

		window.Update();

		dt = (float) (glfwGetTime() - start);
		float fps = 1.0f / dt;
		glfwSetWindowTitle(window.GetWindow(), (TITLE + " | " + std::to_string(dt) + " | " + std::to_string(fps)).c_str());
	}

	scene.Clear();
	defaultShader.Delete();
	window.Delete();

	return 0;
}