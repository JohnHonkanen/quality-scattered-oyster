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
		glDeleteVertexArrays(1, &it->first);
		glDeleteBuffers(1, &it->second[STORED_VERTEX]);
		glDeleteBuffers(1, &it->second[STORED_COLOR]);
		glDeleteBuffers(1, &it->second[STORED_UV]);
		glDeleteBuffers(1, &it->second[STORED_NORMAL]);
		glDeleteBuffers(1, &it->second[STORED_INDEX]);
		glDeleteBuffers(1, &it->second[STORED_TANGENT]);
		glDeleteBuffers(1, &it->second[STORED_BITANGENT]);

	}
}

GLuint MeshGenerator::createMesh(MeshData data)
{
	GLuint VAO;
	GLuint vertexBuffer, colorBuffer, uvBuffer, normalBuffer, elementBuffer, tangentBuffer, bitangentBuffer;
	GLuint* meshBuffers = new GLuint[7];

	//VBO = Vertex Buffer Object
	//VAO = Vertex Array Object
	//EBO = Element Buffer Object - EBO is a buffer, just like the vertex buffer object, that stores indices that OpenGL uses to
	//decide what vertices to draw. This is done by storing only the unique vertices and then 
	//specify the order at which we want to draw these vertices in. 
	//Example: Use 4 vertices to draw a square using 2 triangles instead of 6. 

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &vertexBuffer);
	glGenBuffers(1, &elementBuffer);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, 3 * data.vertexCount * sizeof(GLfloat), data.vertices, GL_STATIC_DRAW);

	meshBuffers[STORED_VERTEX] = vertexBuffer;

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.indexCount * sizeof(GLuint), data.indices, GL_STATIC_DRAW);

	meshBuffers[STORED_INDEX] = elementBuffer;

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Color attribute
	if (data.color != nullptr) {
		glGenBuffers(1, &colorBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
		glBufferData(GL_ARRAY_BUFFER, 3 * data.vertexCount*sizeof(GLfloat), data.color, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
		glEnableVertexAttribArray(1);
		meshBuffers[STORED_COLOR] = colorBuffer;
	}
	
	// TexCoord attribute
	if (data.uv != nullptr) {
		glGenBuffers(1, &uvBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
		glBufferData(GL_ARRAY_BUFFER, 2 * data.vertexCount*sizeof(GLfloat), data.uv, GL_STATIC_DRAW);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0); 
		glEnableVertexAttribArray(2);
		meshBuffers[STORED_UV] = uvBuffer;
	}

	// Normals attribute
	if (data.normals != nullptr) {
		glGenBuffers(1, &normalBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
		glBufferData(GL_ARRAY_BUFFER, 3 * data.vertexCount*sizeof(GLfloat), data.normals, GL_STATIC_DRAW);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0); //3 * sizeof(GLfloat)
		glEnableVertexAttribArray(3); // Set location in shader
		meshBuffers[STORED_NORMAL] = normalBuffer;
	}

	// Tangent attribute
	if (data.tangents != nullptr) {
		glGenBuffers(1, &tangentBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, tangentBuffer);
		glBufferData(GL_ARRAY_BUFFER, 3 * data.vertexCount*sizeof(GLfloat), data.tangents, GL_STATIC_DRAW);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0); //3 * sizeof(GLfloat)
		glEnableVertexAttribArray(4); // Set location in shader
		meshBuffers[STORED_TANGENT] = tangentBuffer;
	}

	// Bitangent attribute
	if (data.bitangents != nullptr) {
		glGenBuffers(1, &bitangentBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, bitangentBuffer);
		glBufferData(GL_ARRAY_BUFFER, 3 * data.vertexCount*sizeof(GLfloat), data.bitangents, GL_STATIC_DRAW);
		glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0); //3 * sizeof(GLfloat)
		glEnableVertexAttribArray(5); // Set location in shader
		meshBuffers[STORED_BITANGENT] = bitangentBuffer;
	}
	
	
	glBindVertexArray(0); // Unbind VAO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// return the identifier needed to draw this mesh

	VAOMap.insert(pair<GLuint, GLuint *>(VAO, meshBuffers));

	return VAO;

}


