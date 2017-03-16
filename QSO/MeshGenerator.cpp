#include "MeshGenerator.h"

map<GLuint, GLuint*>MeshGenerator::VAOMap;

void MeshGenerator::updateMesh(const GLuint mesh, const unsigned int bufferType, const GLfloat *data, const GLuint size) {
	GLuint *meshBuffers = VAOMap[mesh];
	glBindVertexArray(mesh);

	// Delete the old buffer data
	glDeleteBuffers(1, &meshBuffers[bufferType]);

	// Generate and set up the VBO's for the new data
	GLuint VBO;
	glGenBuffers(1, &VBO);
	
	// VBO for the data
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, size*sizeof(GLfloat), data, GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)bufferType, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(bufferType);
	meshBuffers[VBO];

	glBindVertexArray(0);
}

void MeshGenerator::destroy()
{
	//Properly de-allocate all resources once they've outlived their purpose
	//A VAO stores the glBindBuffer calls when the target is GL_ELEMENT_ARRAY_BUFFER. This means it stores its unbind calls
	//so make sure you don't unbind the element array buffer before unbinding your VAO, otherwise it doesn't have an EBO
	//configured. 

	map<GLuint, GLuint*>::iterator it = VAOMap.begin();

	for (it; it == VAOMap.end(); it++) {
		glDeleteVertexArrays(1, &it->second[STORED_VAO]);
		glDeleteBuffers(1, &it->second[STORED_VBO]);
		glDeleteBuffers(1, &it->second[STORED_EBO]);
	}
}

GLuint MeshGenerator::createMesh(MeshData data)
{
	GLuint tVAO, tVBO, tEBO;
	GLuint* meshBuffers = new GLuint[3];

	//VBO = Vertex Buffer Object
	//VAO = Vertex Array Object
	//EBO = Element Buffer Object - EBO is a buffer, just like the vertex buffer object, that stores indices that OpenGL uses to
	//decide what vertices to draw. This is done by storing only the unique vertices and then 
	//specify the order at which we want to draw these vertices in. 
	//Example: Use 4 vertices to draw a square using 2 triangles instead of 6. 

	glGenVertexArrays(1, &tVAO);
	glGenBuffers(1, &tVBO);
	glGenBuffers(1, &tEBO);

	glBindVertexArray(tVAO);

	glBindBuffer(GL_ARRAY_BUFFER, tVBO);
	glBufferData(GL_ARRAY_BUFFER, 3 * data.vertexCount * sizeof(GLfloat), data.vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.indexCount * sizeof(GLuint), data.indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Color attribute
	if (data.color != nullptr) {
		
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
		glEnableVertexAttribArray(1);

	}
	
	// TexCoord attribute
	if (data.uv != nullptr) {

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
		glEnableVertexAttribArray(2);
	}

	// Normals attribute
	if (data.normals != nullptr) {

		glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0); //3 * sizeof(GLfloat)
		glEnableVertexAttribArray(3); // Set location in shader
	}
	
	
	glBindVertexArray(0); // Unbind VAO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	meshBuffers[STORED_VAO] = tVAO;
	meshBuffers[STORED_VBO] = tVBO;
	meshBuffers[STORED_EBO] = tEBO;

	// return the identifier needed to draw this mesh

	VAOMap.insert(pair<GLuint, GLuint *>(tVAO, meshBuffers));

	return tVAO;

}


