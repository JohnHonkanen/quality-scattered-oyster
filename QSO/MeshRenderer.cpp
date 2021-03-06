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
	
	MeshRenderer::program->Use();

	Transform lampPos;
	Transform sunPos;

	mat4 model;
	lampPos.translate(vec3(0.0f, 10.0f, 0.0f));
	lampPos.calculateModelMatrix();

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
	lampPos.translate(vec3(0.0f, 10.0f, 0.0f));
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
	GLint lightSpotLoc = glGetUniformLocation(MeshRenderer::program->program, "light.spotPosition");
	GLint lightSpotdirLoc = glGetUniformLocation(MeshRenderer::program->program, "light.spotDirection");
	GLint lightSpotCutOffLoc = glGetUniformLocation(MeshRenderer::program->program, "light.cutOff");
	GLint lightSpotOuterCutOffLoc = glGetUniformLocation(MeshRenderer::program->program, "light.outerCutOff");

	// Multi-light - dirLight
	GLint dirLightLoc = glGetUniformLocation(MeshRenderer::program->program, "dirLight.direction");
	GLint ambientDirLightLoc = glGetUniformLocation(MeshRenderer::program->program, "dirLight.ambient");
	GLint diffuseDirLightLoc = glGetUniformLocation(MeshRenderer::program->program, "dirLight.diffuse");
	GLint specularDirLightLoc = glGetUniformLocation(MeshRenderer::program->program, "dirLight.specular");
	// Multi-light - pointLight
	GLint pointLightLoc = glGetUniformLocation(MeshRenderer::program->program, "pointLight.direction");
	GLint ambientPointLightLoc = glGetUniformLocation(MeshRenderer::program->program, "pointLight.ambient");
	GLint diffusePointLightLoc = glGetUniformLocation(MeshRenderer::program->program, "pointLight.diffuse");
	GLint specularPointLightLoc = glGetUniformLocation(MeshRenderer::program->program, "pointLight.specular");
	GLint constantPointLightLoc = glGetUniformLocation(MeshRenderer::program->program, "pointLight.constant");
	GLint linearPointLightLoc = glGetUniformLocation(MeshRenderer::program->program, "pointLight.linear");
	GLint quadraticPointLightLoc = glGetUniformLocation(MeshRenderer::program->program, "pointLight.quadratic");
	// Multi-light - spotLight
	GLint spotLightPositionLoc = glGetUniformLocation(MeshRenderer::program->program, "spotLight.position");
	GLint spotLightDirectionLoc = glGetUniformLocation(MeshRenderer::program->program, "spotLight.direction");
	GLint ambientSpotLightLoc = glGetUniformLocation(MeshRenderer::program->program, "spotLight.ambient");
	GLint diffuseSpotLightLoc = glGetUniformLocation(MeshRenderer::program->program, "spotLight.diffuse");
	GLint specularSpotLightLoc = glGetUniformLocation(MeshRenderer::program->program, "spotLight.specular");
	GLint constantSpotLightLoc = glGetUniformLocation(MeshRenderer::program->program, "spotLight.constant");
	GLint linearSpotLightLoc = glGetUniformLocation(MeshRenderer::program->program, "spotLight.linear");
	GLint quadraticSpotLightLoc = glGetUniformLocation(MeshRenderer::program->program, "spotLight.quadratic");
	GLint cutOffSpotLightLoc = glGetUniformLocation(MeshRenderer::program->program, "spotLight.cutOff");
	GLint outerCutOffSpotLightLoc = glGetUniformLocation(MeshRenderer::program->program, "spotLight.outerCutOff");


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
	// These values are distance: 50
	glUniform1f(lightConstantPos, 1.0f); 
	glUniform1f(lightLinearPos, 0.022f);
	glUniform1f(lightQuadraticPos, 0.0019f);
	// Set HSV Properties
	glUniform3f(ourImageLoc, 1.0f, 1.0f, 0.0f);
	glUniform1f(hueShiftLoc, hueshift);
	glUniform1f(satBoostLoc, 1.0f);
	hueshift += 0.0005f;
	// Set Spotlight Properties
	glUniform3f(lightSpotLoc, camera->Position.x, camera->Position.y, camera->Position.z);
	glUniform3f(lightSpotdirLoc, camera->Front.x, camera->Front.y, camera->Front.z);
	glUniform1f(lightSpotCutOffLoc, glm::cos(glm::radians(12.5f)));
	glUniform1f(lightSpotOuterCutOffLoc, glm::cos(glm::radians(17.5f)));

	// Set Directional Light Properties for multi-light
	glUniform3f(dirLightLoc, sunPos.getPosition().x, sunPos.getPosition().y, sunPos.getPosition().z);
	glUniform3f(ambientDirLightLoc, 0.0f, 0.0f, 0.0f);
	glUniform3f(diffuseDirLightLoc, 0.0f, 0.0f, 0.0f); // Darken the light a bit to fit the scene
	glUniform3f(specularDirLightLoc, 1.0f, 1.0f, 1.0f);
	// Set Point Light Properties for multi-light
	glUniform3f(pointLightLoc, lampPos.getPosition().x, lampPos.getPosition().y, lampPos.getPosition().z);
	glUniform3f(ambientPointLightLoc, 0.2f, 0.2f, 0.2f);
	glUniform3f(diffusePointLightLoc, 0.5f, 0.5f, 0.5f);
	glUniform3f(specularPointLightLoc, 0.5f, 0.5f, 0.5f);
	glUniform1f(constantPointLightLoc, 1.0f);
	glUniform1f(linearPointLightLoc, 0.022f);
	glUniform1f(quadraticPointLightLoc, 0.0019f);
	// Set Spot Light Properties for multi-light
	glUniform3f(spotLightPositionLoc, camera->Position.x, camera->Position.y, camera->Position.z);
	glUniform3f(spotLightDirectionLoc, camera->Front.x, camera->Front.y, camera->Front.z);
	glUniform3f(ambientSpotLightLoc, 0.2f, 0.2f, 0.2f);
	glUniform3f(diffuseSpotLightLoc, 0.5f, 0.5f, 0.5f);
	glUniform3f(specularSpotLightLoc, 0.5f, 0.5f, 0.5f);
	glUniform1f(constantSpotLightLoc, 1.0f);
	glUniform1f(linearSpotLightLoc, 0.022f);
	glUniform1f(quadraticSpotLightLoc, 0.0019f);
	glUniform1f(cutOffSpotLightLoc, glm::cos(glm::radians(12.5f)));
	glUniform1f(outerCutOffSpotLightLoc, glm::cos(glm::radians(17.5f)));

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

void MeshRenderer::renderObject()
{
}
