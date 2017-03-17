#include "MeshRenderer.h"

MeshRenderer::MeshRenderer(Material material, TextureManager * textureManager, Transform * transform, Shader * program, Camera * camera)
{
	MeshRenderer::material = material;
	MeshRenderer::textureManager = textureManager;
	MeshRenderer::transform = transform;
	MeshRenderer::program = program;
	MeshRenderer::camera = camera;
	//MeshRenderer::mesh = mesh;
}

MeshRenderer::~MeshRenderer()
{
}

void MeshRenderer::init()
{

}


void MeshRenderer::renderObject(Mesh *mesh)
{
	/*Draw Cube*/
	/*Use Material*/

	MeshRenderer::program->Use();

	mat4 view = camera->getView();
	mat4 projection = camera->getProjection();
	mat4 model = transform->get();

	//Get matrix's uniform location, get and set matrix
	GLuint modelLoc = glGetUniformLocation(MeshRenderer::program->program, "model");
	GLuint viewLoc = glGetUniformLocation(MeshRenderer::program->program, "view");
	GLuint projectionLoc = glGetUniformLocation(MeshRenderer::program->program, "projection");
	GLuint alphaLoc = glGetUniformLocation(MeshRenderer::program->program, "ourAlpha");

	

	//glBindTexture call will bind that texture to the currently active texture unit.
	glBindTexture(GL_TEXTURE_2D, textureManager->getTexture(MeshRenderer::material.texture));
	//By setting them via glUniform1i we make sure each uniform sampler corresponds to the proper texture unit.
	
	if (MeshRenderer::material.diffuse != "") {
		glUniform1i(glGetUniformLocation(program->program, "material.diffuse"), POSITION);
	}

	if (MeshRenderer::material.color != "") {
		glUniform1i(glGetUniformLocation(program->program, "material.color"), COLOR);
	}

	if (MeshRenderer::material.specular != "") {
		glUniform1i(glGetUniformLocation(program->program, "material.specular"), UV);
		//glUniform3f(glGetUniformLocation(program->program, "material.specular"), 0.5f, 0.5f, 0.5f);

	}

	if (MeshRenderer::material.emission != "") {
		glUniform1i(glGetUniformLocation(program->program, "material.emission"), NORMAL);
	}

	//Draw Prefabs
	glBindVertexArray(mesh->glObjects.VAO);
	glLineWidth(5.0f);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//Pass to Shader
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
	glUniform1f(alphaLoc, 1.0f);

	//glDrawArrays(GL_TRIANGLES, 0, 8);
	glDrawElements(GL_TRIANGLES, mesh->mesh.indexCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	
}

void MeshRenderer::renderObject(Polygon * polygon)
{
	/*Draw Cube*/
	/*Use Material*/

	MeshRenderer::program->Use();

	mat4 view = camera->getView();
	mat4 projection = camera->getProjection();
	mat4 model = transform->get();

	//Get matrix's uniform location, get and set matrix
	GLuint modelLoc = glGetUniformLocation(MeshRenderer::program->program, "model");
	GLuint viewLoc = glGetUniformLocation(MeshRenderer::program->program, "view");
	GLuint projectionLoc = glGetUniformLocation(MeshRenderer::program->program, "projection");
	GLuint alphaLoc = glGetUniformLocation(MeshRenderer::program->program, "ourAlpha");

	//glBindTexture call will bind that texture to the currently active texture unit.
	glBindTexture(GL_TEXTURE_2D, textureManager->getTexture(MeshRenderer::material.texture));
	//By setting them via glUniform1i we make sure each uniform sampler corresponds to the proper texture unit.
	glUniform1i(glGetUniformLocation(program->program, "ourTexture"), 0);

	for (int i = 0; i < 6; i++) {
		//Draw Prefabs
		glBindVertexArray(polygon->mesh[i]->glObjects.VAO);
		glLineWidth(5.0f);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		//Pass to Shader
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniform1f(alphaLoc, 1.0f);

		//glDrawArrays(GL_TRIANGLES, 0, 8);
		glDrawElements(GL_TRIANGLES, polygon->mesh[i]->mesh.indexCount, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}

void MeshRenderer::renderObject()
{
}
