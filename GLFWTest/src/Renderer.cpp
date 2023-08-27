#include "Renderer.h"

void Renderer::Render(Entity& entity, ShaderProgram& shader, Camera& camera)
{
	shader.Activate();
	entity.Bind();

	entity.SendUniforms(shader);

	glUniformMatrix4fv(glGetUniformLocation(shader.GetID(), "view"), 1, GL_FALSE, glm::value_ptr(camera.GetView()));
	glUniformMatrix4fv(glGetUniformLocation(shader.GetID(), "proj"), 1, GL_FALSE, glm::value_ptr(camera.GetProjection()));
	glUniform3f(glGetUniformLocation(shader.GetID(), "cameraPosition"), camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
	
	glDrawElements(GL_TRIANGLES, entity.GetIndeciesCount(), GL_UNSIGNED_INT, 0);

	shader.Deactivate();
}

void Renderer::Render(Scene& scene, ShaderProgram& program, Camera& camera)
{
	for (Entity& entity : scene.GetEntities())
	{
		Render(entity, program, camera);
	}
}
