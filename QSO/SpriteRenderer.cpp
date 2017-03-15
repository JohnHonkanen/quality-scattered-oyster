#include "SpriteRenderer.h"


SpriteRenderer::SpriteRenderer(string fileLocation, string name, TextureManager * textureeManager, Transform * position, Shader * program)
{
	SpriteRenderer::fileLocation = fileLocation;
	SpriteRenderer::name = name;
	SpriteRenderer::textureManager = textureeManager;
	SpriteRenderer::position = position;
	SpriteRenderer::program = program;
	
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

	//VBO = Vertex Buffer Object
	//VAO = Vertex Array Object
	//EBO = Element Buffer Object - EBO is a buffer, just like the vertex buffer object, that stores indices that OpenGL uses to
	//decide what vertices to draw. This is done by storing only the unique vertices and then 
	//specify the order at which we want to draw these vertices in. 
	//Example: Use 4 vertices to draw a square using 2 triangles instead of 6. 


	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
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

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	delete this;
}