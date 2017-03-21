#include "MeshRenderer.h"

MeshRenderer::MeshRenderer(Material material, TextureManager * textureManager, Transform * transform, Shader * program)
{
	MeshRenderer::material = material;
	MeshRenderer::textureManager = textureManager;
	MeshRenderer::transform = transform;
	MeshRenderer::program = program;
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
	
	MeshRenderer::program->Use();

	//Transform lampPos;
	Transform sunPos;

	mat4 model;
	/*lampPos.translate(vec3(0.0f, 10.0f, 0.0f));
	lampPos.calculateModelMatrix();*/

	sunPos.translate(vec3(100.0f, 100.0f, 0.0f));
	sunPos.calculateModelMatrix();

	// Don't forget to 'use' the corresponding shader program first (to set the uniform)
	GLint objectColorLoc = glGetUniformLocation(MeshRenderer::program->program, "objectColor");
	GLint lightColorLoc = glGetUniformLocation(MeshRenderer::program->program, "lightColor");
	GLint lightPositionLoc = glGetUniformLocation(MeshRenderer::program->program, "light.position"); 
	GLint viewPosLoc = glGetUniformLocation(MeshRenderer::program->program, "viewPos");
	GLint matAmbientLoc = glGetUniformLocation(MeshRenderer::program->program, "material.ambient");
	GLint matDiffuseLoc = glGetUniformLocation(MeshRenderer::program->program, "material.diffuse");
	GLint matSpecularLoc = glGetUniformLocation(MeshRenderer::program->program, "material.specular");
	GLint matShineLoc = glGetUniformLocation(MeshRenderer::program->program, "material.shininess");
	GLint lightAmbientLoc = glGetUniformLocation(MeshRenderer::program->program, "light.ambient");
	GLint lightDiffuseLoc = glGetUniformLocation(MeshRenderer::program->program, "light.diffuse");
	GLint lightSpecularLoc = glGetUniformLocation(MeshRenderer::program->program, "light.specular");
	GLint lightDirPos = glGetUniformLocation(MeshRenderer::program->program, "light.direction");
	GLint lightConstantPos = glGetUniformLocation(MeshRenderer::program->program, "light.constant");
	GLint lightLinearPos = glGetUniformLocation(MeshRenderer::program->program, "light.linear");
	GLint lightQuadraticPos = glGetUniformLocation(MeshRenderer::program->program, "light.quadratic");
	glUniform3f(objectColorLoc, 1.0f, 0.0f, 0.5f);
	glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f); // Also set light's color (white)
	glUniform3f(viewPosLoc, camera->Position.x, camera->Position.y, camera->Position.z);
	glUniform3f(lightPositionLoc, sunPos.getPosition().x, sunPos.getPosition().y, sunPos.getPosition().z);
	// Set Material Properties
	glUniform3f(matAmbientLoc, 1.0f, 0.5f, 0.31f);
	glUniform3f(matDiffuseLoc, 1.0f, 0.5f, 0.31f);
	glUniform3f(matSpecularLoc, 0.5f, 0.5f, 0.5f);
	glUniform1f(matShineLoc, 32.0f);
	// Set Light Properties
	glUniform3f(lightAmbientLoc, 0.2f, 0.2f, 0.2f);
	glUniform3f(lightDiffuseLoc, 0.5f, 0.5f, 0.5f); // Darken the light a bit to fit the scene
	glUniform3f(lightSpecularLoc, 1.0f, 1.0f, 1.0f);
	glUniform3f(lightDirPos, sunPos.getPosition().x, sunPos.getPosition().y, sunPos.getPosition().z);
	// Set Light attenuation properties <- See for value reference: http://www.ogre3d.org/tikiwiki/tiki-index.php?page=-Point+Light+Attenuation
	glUniform1f(lightConstantPos, 1.0f);
	glUniform1f(lightLinearPos, 0.09f);
	glUniform1f(lightQuadraticPos, 0.032);

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

	if (MeshRenderer::material.color != "") {
		glUniform1i(glGetUniformLocation(program->program, "material.color"), COLOR);
	}

	if (MeshRenderer::material.emission != "") {

		//Bind Emission map
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, textureManager->getTexture(MeshRenderer::material.emission));
		glUniform1i(glGetUniformLocation(program->program, "material.emission"), UV);
	}

	if (MeshRenderer::material.specular != "") {

		//Bind Specular map
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, textureManager->getTexture(MeshRenderer::material.specular));
		glUniform1i(glGetUniformLocation(program->program, "material.specular"), NORMAL);
	}

	//Draw Prefabs
	glBindVertexArray(mesh->glObjects.VAO);
	glLineWidth(5.0f);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//glDrawArrays(GL_TRIANGLES, 0, 8);
	glDrawElements(mesh->mesh.mode, mesh->mesh.indexCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	
}


float hueshift = 0.0f;
void MeshRenderer::renderObject(Shape *shape)
{
	/*Draw Cube*/
	/*Use Material*/
	int numberOfMeshs;
	vector<Mesh*> mesh = shape->getMesh(numberOfMeshs);

	MeshRenderer::program->Use();

	Transform lampPos;
	Transform sunPos;

	mat4 model;
	lampPos.translate(vec3(0.0f, 25.0f, 0.0f));
	lampPos.calculateModelMatrix();

	sunPos.translate(vec3(0.0f, 100.0f, 0.0f));
	sunPos.calculateModelMatrix();

	// Don't forget to 'use' the corresponding shader program first (to set the uniform)
	GLint objectColorLoc = glGetUniformLocation(MeshRenderer::program->program, "objectColor");
	GLint lightColorLoc = glGetUniformLocation(MeshRenderer::program->program, "lightColor");
	GLint lightPosLoc = glGetUniformLocation(MeshRenderer::program->program, "lightPos"); // Depreciated Code soon. May need deleting
	GLint lightPositionLoc = glGetUniformLocation(MeshRenderer::program->program, "light.position");
	GLint viewPosLoc = glGetUniformLocation(MeshRenderer::program->program, "viewPos");
	GLint matAmbientLoc = glGetUniformLocation(MeshRenderer::program->program, "material.ambient");
	GLint matDiffuseLoc = glGetUniformLocation(MeshRenderer::program->program, "material.diffuse");
	GLint matSpecularLoc = glGetUniformLocation(MeshRenderer::program->program, "material.specular");
	GLint matShineLoc = glGetUniformLocation(MeshRenderer::program->program, "material.shininess");
	GLint lightAmbientLoc = glGetUniformLocation(MeshRenderer::program->program, "light.ambient");
	GLint lightDiffuseLoc = glGetUniformLocation(MeshRenderer::program->program, "light.diffuse");
	GLint lightSpecularLoc = glGetUniformLocation(MeshRenderer::program->program, "light.specular");
	GLint lightDirPos = glGetUniformLocation(MeshRenderer::program->program, "light.direction");
	GLint lightConstantPos = glGetUniformLocation(MeshRenderer::program->program, "light.constant");
	GLint lightLinearPos = glGetUniformLocation(MeshRenderer::program->program, "light.linear");
	GLint lightQuadraticPos = glGetUniformLocation(MeshRenderer::program->program, "light.quadratic");
	GLint ourImageLoc = glGetUniformLocation(MeshRenderer::program->program, "ourImage"); 
	GLint hueShiftLoc = glGetUniformLocation(MeshRenderer::program->program, "hueShift");
	GLint satBoostLoc = glGetUniformLocation(MeshRenderer::program->program, "satBoost");
	

	//glUniform3f(objectColorLoc, color.x, color.y, color.z);
	glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f); // Also set light's color (white)
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
	glUniform3f(lightDirPos, lampPos.getPosition().x, lampPos.getPosition().y, lampPos.getPosition().z);
	glUniform3f(lightPositionLoc, lampPos.getPosition().x, lampPos.getPosition().y, lampPos.getPosition().z);
	// Set Light attenuation properties <- See for value reference: http://www.ogre3d.org/tikiwiki/tiki-index.php?page=-Point+Light+Attenuation
	glUniform1f(lightConstantPos, 1.0f);
	glUniform1f(lightLinearPos, 0.09f);
	glUniform1f(lightQuadraticPos, 0.032f);
	// Set HSV properties
	glUniform3f(ourImageLoc, 1.0f, 1.0f, 0.0f);
	glUniform1f(hueShiftLoc, 0.0f);
	glUniform1f(satBoostLoc, hueshift);

	hueshift += 0.0005f;



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

	if (MeshRenderer::material.color != "") {
		glUniform1i(glGetUniformLocation(program->program, "material.color"), COLOR);
	}

	if (MeshRenderer::material.emission != "") {

		//Bind Emission map
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, textureManager->getTexture(MeshRenderer::material.emission));
		glUniform1i(glGetUniformLocation(program->program, "material.emission"), UV);
	}

	if (MeshRenderer::material.specular != "") {

		//Bind Specular map
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, textureManager->getTexture(MeshRenderer::material.specular));
		glUniform1i(glGetUniformLocation(program->program, "material.specular"), NORMAL);
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