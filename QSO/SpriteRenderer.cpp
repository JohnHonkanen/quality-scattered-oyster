#include "SpriteRenderer.h"


SpriteRenderer::SpriteRenderer(string fileLocation, string name, TextureManager * textureeManager, Transform * position, Shader * program, Camera *camera)
{
	SpriteRenderer::fileLocation = fileLocation;
	SpriteRenderer::name = name;
	SpriteRenderer::textureManager = textureeManager;
	SpriteRenderer::position = position;
	SpriteRenderer::program = program;
	SpriteRenderer::camera = camera;
	
}

SpriteRenderer::~SpriteRenderer()
{
}

void SpriteRenderer::init() {

	//Draw Quad

	GLfloat data[] = {
		// Positions          // Colors           // Texture Coords
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // Top Right
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // Bottom Right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // Bottom Left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // Top Left 
	};

	GLuint indices[] = {  // Note that we start from 0!
		0, 1, 3, // First Triangle
		1, 2, 3  // Second Triangle
	};

	//SpriteRenderer::VAO = MeshGenerator::createMesh(data, sizeof(data), indices, sizeof(indices));

}

void SpriteRenderer::renderObject() {

	SpriteRenderer::program->Use();

	// Get matrix's uniform location, get and set matrix
	GLuint modelLoc = glGetUniformLocation(SpriteRenderer::program->program, "model");
	GLuint viewLoc = glGetUniformLocation(SpriteRenderer::program->program, "view");
	GLuint projectionLoc = glGetUniformLocation(SpriteRenderer::program->program, "projection");
	GLuint alphaLoc = glGetUniformLocation(SpriteRenderer::program->program, "ourAlpha");

	// glBindTexture call will bind that texture to the currently active texture unit.
	glBindTexture(GL_TEXTURE_2D, textureManager->getTexture(name));

	// By setting them via glUniform1i we make sure each uniform sampler corresponds to the proper texture unit.
	glUniform1i(glGetUniformLocation(program->program, "ourTexture"), 0);

	//Draw Container
	glBindVertexArray(VAO);

	//Pass to Shader
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(position->get()));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(Renderer::view.get()));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(Renderer::projection.get()));
	glUniform1f(alphaLoc, Renderer::alpha);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}


void SpriteRenderer::destroy() {

	//Properly de-allocate all resources once they've outlived their purpose
	//A VAO stores the glBindBuffer calls when the target is GL_ELEMENT_ARRAY_BUFFER. This means it stores its unbind calls
	//so make sure you don't unbind the element array buffer before unbinding your VAO, otherwise it doesn't have an EBO
	//configured. 

	delete this;
}