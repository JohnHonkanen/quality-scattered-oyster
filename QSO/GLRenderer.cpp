#include "GLRenderer.h"
#include "TextureManager.h"
GLRenderer::GLRenderer()
{
}

GLRenderer::~GLRenderer()
{
}

void GLRenderer::init()
{

}

float hueshift = 0.0f;
void GLRenderer::renderObject(GameObject *obj)
{
	Material *material = obj->getComponent<Material>();
	Shape *shape = obj->getComponent<Shape>();
	vector<Material> modelMats;
	if (obj->getComponent<Model>()) {
		modelMats = obj->getComponent<Model>()->material;
	}


	if (material->isCubMap) {
		glDepthFunc(GL_LEQUAL);  // Change depth function so depth test passes when values are equal to depth buffer's content
	}

	/*Draw Cube*/
	/*Use Material*/
	int numberOfMeshs;
	vector<Mesh*> mesh = shape->getMesh(numberOfMeshs);
	TextureManager *textureManager = TextureManager::instance();
	Shader shader = material->program;
	shader.Use();

	Transform lampPos;
	Transform sunPos;

	mat4 model;
	lampPos.translate(vec3(0.0f, 25.0f, 0.0f));
	lampPos.calculateModelMatrix();

	sunPos.translate(vec3(0.0f, 100.0f, 0.0f));
	sunPos.calculateModelMatrix();

	// Don't forget to 'use' the corresponding shader program first (to set the uniform)
	GLint objectColorLoc = glGetUniformLocation(shader.program, "objectColor");
	GLint lightColorLoc = glGetUniformLocation(shader.program, "lightColor");
	GLint lightPosLoc = glGetUniformLocation(shader.program, "lightPos"); // Depreciated Code soon. May need deleting
	GLint lightPositionLoc = glGetUniformLocation(shader.program, "light.position");
	GLint viewPosLoc = glGetUniformLocation(shader.program, "viewPos");
	GLint matAmbientLoc = glGetUniformLocation(shader.program, "material.ambient");
	GLint matDiffuseLoc = glGetUniformLocation(shader.program, "material.diffuse");
	GLint matSpecularLoc = glGetUniformLocation(shader.program, "material.specular");
	GLint matShineLoc = glGetUniformLocation(shader.program, "material.shininess");
	GLint lightAmbientLoc = glGetUniformLocation(shader.program, "light.ambient");
	GLint lightDiffuseLoc = glGetUniformLocation(shader.program, "light.diffuse");
	GLint lightSpecularLoc = glGetUniformLocation(shader.program, "light.specular");
	GLint lightDirPos = glGetUniformLocation(shader.program, "light.direction");
	GLint lightConstantPos = glGetUniformLocation(shader.program, "light.constant");
	GLint lightLinearPos = glGetUniformLocation(shader.program, "light.linear");
	GLint lightQuadraticPos = glGetUniformLocation(shader.program, "light.quadratic");
	GLint ourImageLoc = glGetUniformLocation(shader.program, "ourImage"); 
	GLint hueShiftLoc = glGetUniformLocation(shader.program, "hueShift");
	GLint satBoostLoc = glGetUniformLocation(shader.program, "satBoost");
	

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
	glUniform1f(hueShiftLoc, hueshift);
	glUniform1f(satBoostLoc, 1.0f);

	hueshift += 0.0005f;



	// Create camera transformations
	mat4 view = camera->getView();
	if (material->isCubMap){
		view = mat4(mat3(view));
	}

	mat4 projection = camera->getProjection();
	model = obj->transform.get();
	mat3 normalMatrix = transpose(inverse(mat3(model)));

	// Get matrix's uniform location, get and set matrix
	GLuint modelLoc = glGetUniformLocation(shader.program, "model");
	GLuint viewLoc = glGetUniformLocation(shader.program, "view");
	GLuint projectionLoc = glGetUniformLocation(shader.program, "projection");
	GLuint alphaLoc = glGetUniformLocation(shader.program, "ourAlpha");
	GLuint normalMatrixLoc = glGetUniformLocation(shader.program, "normalMatrix");

	// Pass to Shader
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
	glUniform1f(alphaLoc, 1.0f);
	glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));

	//glBindTexture call will bind that texture to the currently active texture unit.
	//By setting them via glUniform1i we make sure each uniform sampler corresponds to the proper texture unit.
	if (!obj->getComponent<Model>()) {
		for (int i = 0; i < material->textures.size(); i++) {
			string type = material->convertTypeToString(material->textures[i].type);
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, textureManager->getTexture(material->textures[i].textureName));
			glUniform1i(glGetUniformLocation(shader.program, ("material." + type).c_str()), i);
		}
	}

	for (int i = 0; i < numberOfMeshs; i++) {
		//Draw Prefabs
		glBindVertexArray(mesh[i]->getVAO());

		if (obj->getComponent<Model>()) {
			for (int j = 0; j < modelMats[i].textures.size(); j++) {
				string type = material->convertTypeToString(modelMats[i].textures[j].type);
				string number = std::to_string(modelMats[i].textures[j].number);
				glActiveTexture(GL_TEXTURE0+j);
				glBindTexture(GL_TEXTURE_2D, textureManager->getTexture(modelMats[i].textures[j].textureName));
				glUniform1i(glGetUniformLocation(shader.program, ("material." + type).c_str()), j);
			}
		}
		if (material->isCubMap) {
			if (material->cubeMaps[0] != "") {
				glActiveTexture(GL_TEXTURE0);
				GLint skyBoxLoc = glGetUniformLocation(shader.program, "skybox");
				glUniform1i(skyBoxLoc, 0);
				glBindTexture(GL_TEXTURE_CUBE_MAP, textureManager->getCubeMap(material->cubeMaps));
			}
		}

		mesh[i]->drawMesh();
	}
	if (material->isCubMap) {
		glDepthFunc(GL_LESS); // Set depth function back to default
	}
}