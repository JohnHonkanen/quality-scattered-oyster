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

	//Set Light Matrix's uniform location
	GLint lightDirLoc = glGetUniformLocation(MeshRenderer::program->program, "light.direction");
	GLint viewPosLoc = glGetUniformLocation(MeshRenderer::program->program, "viewPos");


	//glBindTexture call will bind that texture to the currently active texture unit.
	glBindTexture(GL_TEXTURE_2D, textureManager->getTexture(MeshRenderer::material.uv));
	//By setting them via glUniform1i we make sure each uniform sampler corresponds to the proper texture unit.
	
	if (MeshRenderer::material.diffuse != "") {
		glUniform1i(glGetUniformLocation(program->program, "material.diffuse"), POSITION);
		
		//Bind Diffuse map
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureManager->getTexture(MeshRenderer::material.diffuse));

	}

	if (MeshRenderer::material.color != "") {
		glUniform1i(glGetUniformLocation(program->program, "material.color"), COLOR);
	}

	if (MeshRenderer::material.specular != "") {
		glUniform1i(glGetUniformLocation(program->program, "material.specular"), UV);

		//Bind Specular map
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, textureManager->getTexture(MeshRenderer::material.specular));

	}

	if (MeshRenderer::material.emission != "") {
		glUniform1i(glGetUniformLocation(program->program, "material.emission"), NORMAL);

		//Bind Emission map
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, textureManager->getTexture(MeshRenderer::material.emission));
	}

	//Pass to Shader
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
	glUniform1f(alphaLoc, 1.0f);

	vec3 lightPos(0);

	// Set Light Properties
	glUniform3f(lightDirLoc, lightPos.x, lightPos.y, lightPos.z);
	glUniform3f(glGetUniformLocation(MeshRenderer::program->program, "light.ambient"), 0.2f, 0.2f, 0.2f);
	glUniform3f(glGetUniformLocation(MeshRenderer::program->program, "light.diffuse"), 0.5f, 0.5f, 0.5f);
	glUniform3f(glGetUniformLocation(MeshRenderer::program->program, "light.specular"), 1.0f, 1.0f, 1.0f);

	//Set Material Properties

	glUniform3f(glGetUniformLocation(MeshRenderer::program->program, "material.specular"), 0.5f, 0.5f, 0.5f);
	glUniform1f(glGetUniformLocation(MeshRenderer::program->program, "material.shininess"), 64.0f);

	//Draw Prefabs
	glBindVertexArray(mesh->glObjects.VAO);
	glLineWidth(5.0f);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//glDrawArrays(GL_TRIANGLES, 0, 8);
	glDrawElements(mesh->mesh.mode, mesh->mesh.indexCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	
}

void MeshRenderer::renderObject(Shape *shape)
{
	/*Draw Cube*/
	/*Use Material*/
	int numberOfMeshs;
	vector<Mesh*> mesh = shape->getMesh(numberOfMeshs);

	MeshRenderer::program->Use();

	//vec3 lightPos(0.0f, 0.0f, 0.0f); // Light translation not applied

	Transform lampPos;

	mat4 model;
	//lampPos.setPosition(vec3(0.0f, 0.0f, 0.0f));
	lampPos.translate(vec3(0.0f, 10.0f, 0.0f));
	lampPos.calculateModelMatrix();
	model = lampPos.calculateModelMatrix();

	// Don't forget to 'use' the corresponding shader program first (to set the uniform)
	GLint objectColorLoc = glGetUniformLocation(MeshRenderer::program->program, "objectColor");
	GLint lightColorLoc = glGetUniformLocation(MeshRenderer::program->program, "lightColor");
	GLint lightPosLoc = glGetUniformLocation(MeshRenderer::program->program, "lightPos");
	GLint viewPosLoc = glGetUniformLocation(MeshRenderer::program->program, "viewPos");
	GLint matAmbientLoc = glGetUniformLocation(MeshRenderer::program->program, "material.ambient");
	GLint matDiffuseLoc = glGetUniformLocation(MeshRenderer::program->program, "material.diffuse");
	GLint matSpecularLoc = glGetUniformLocation(MeshRenderer::program->program, "material.specular");
	GLint matShineLoc = glGetUniformLocation(MeshRenderer::program->program, "material.shininess");
	GLint lightAmbientLoc = glGetUniformLocation(MeshRenderer::program->program, "light.ambient");
	GLint lightDiffuseLoc = glGetUniformLocation(MeshRenderer::program->program, "light.diffuse");
	GLint lightSpecularLoc = glGetUniformLocation(MeshRenderer::program->program, "light.specular");
	glUniform3f(objectColorLoc, 1.0f, 0.0f, 0.5f);
	glUniform3f(lightColorLoc, 1.0f, 0.0f, 1.0f); // Also set light's color (white)
	glUniform3f(lightPosLoc, lampPos.getPosition().x, lampPos.getPosition().y, lampPos.getPosition().z);
	glUniform3f(viewPosLoc, camera->Position.x, camera->Position.y, camera->Position.z);
	// Set Material Properties
	glUniform3f(matAmbientLoc, 1.0f, 0.5f, 0.31f);
	glUniform3f(matDiffuseLoc, 1.0f, 0.5f, 0.31f);
	glUniform3f(matSpecularLoc, 0.5f, 0.5f, 0.5f);
	glUniform1f(matShineLoc, 32.0f);
	// Set Light Properties
	glUniform3f(lightAmbientLoc, 0.2f, 0.2f, 0.2f);
	glUniform3f(lightDiffuseLoc, 0.5f, 0.5f, 0.5f); // Darken the light a bit to fit the scene
	glUniform3f(lightSpecularLoc, 1.0f, 1.0f, 1.0f);

	// Create camera transformations
	mat4 view = camera->getView();
	mat4 projection = camera->getProjection();
	model = transform->get();
	mat3 normalMatrix = transpose(inverse(mat3(model)));

	// Get matrix's uniform location, get and set matrix
	GLuint modelLoc = glGetUniformLocation(MeshRenderer::program->program, "model");
	GLuint viewLoc = glGetUniformLocation(MeshRenderer::program->program, "view");
	GLuint projectionLoc = glGetUniformLocation(MeshRenderer::program->program, "projection");
	GLuint alphaLoc = glGetUniformLocation(MeshRenderer::program->program, "ourAlpha");
	GLuint normalMatrixLoc = glGetUniformLocation(MeshRenderer::program->program, "normalMatrix");

	// Pass to Shader
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
	glUniform1f(alphaLoc, 1.0f);
	glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));

	//glBindTexture call will bind that texture to the currently active texture unit.
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureManager->getTexture(MeshRenderer::material.uv));
	glUniform1i(glGetUniformLocation(program->program, "ourUV"), 0);
	//By setting them via glUniform1i we make sure each uniform sampler corresponds to the proper texture unit.

	if (MeshRenderer::material.diffuse != "") {
		//Bind Diffuse map
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureManager->getTexture(MeshRenderer::material.diffuse));
		glUniform1i(glGetUniformLocation(program->program, "material.diffuse"), POSITION);
	}

	if (MeshRenderer::material.specular != "") {
		

		//Bind Specular map
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, textureManager->getTexture(MeshRenderer::material.specular));
		glUniform1i(glGetUniformLocation(program->program, "material.specular"), NORMAL);
	}


	if (MeshRenderer::material.color != "") {
		glUniform1i(glGetUniformLocation(program->program, "material.color"), COLOR);
	}


	if (MeshRenderer::material.emission != "") {

		//Bind Emission map
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, textureManager->getTexture(MeshRenderer::material.emission));
		glUniform1i(glGetUniformLocation(program->program, "material.emission"), UV);
	}
	

	for (int i = 0; i < numberOfMeshs; i++) {
		//Draw Prefabs
		glBindVertexArray(mesh[i]->glObjects.VAO);

		// Pass to Shader
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		
		glDrawElements(mesh[i]->mesh.mode, mesh[i]->mesh.indexCount, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}

void MeshRenderer::renderObject()
{
}
