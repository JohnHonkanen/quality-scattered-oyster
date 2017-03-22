#include "AssimpModel.h"

void AssimpModel::init()
{
	//Shape::numberOfMeshs = 1;
	buildModel();
}

void AssimpModel::buildModel()
{

}

void AssimpModel::loadModel(string path)
{
	Assimp::Importer import;
	const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)	//If there was a problem:
	{
		cout << "ERROR::ASSIMP::" << import.GetErrorString() << endl;	//Output an error.
		return;
	}
	this->directory = path.substr(0, path.find_last_of('/'));

	this->processNode(scene->mRootNode, scene);
}

void AssimpModel::processNode(aiNode * node, const aiScene * scene)
{
	// Process all the node's meshes (if any)
	for (GLuint i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* meshes = scene->mMeshes[node->mMeshes[i]];
		AssimpModel::meshes.push_back(AssimpModel::processMesh(meshes, scene));
	}
	// Then do the same for each of its children
	for (GLuint i = 0; i < node->mNumChildren; i++)
	{
		this->processNode(node->mChildren[i], scene);
	}
}

Mesh* AssimpModel::processMesh(aiMesh* meshes, const aiScene* scene)
{
	int meshType = 3;
	//Vertex vertices;
	int numVerts = meshes->mNumVertices;
	int numIndeces = meshType * meshes->mNumFaces;
	GLfloat* normals = new GLfloat[3*numVerts];
	GLfloat* postition = new GLfloat[3*numVerts];
	GLfloat* texCoords = new GLfloat[2*numVerts];
	
	GLuint* indices = new GLuint[numIndeces];
	//vector<Texture> textures;

	float divedThree = 1 / 3.0f;
	for (GLuint i = 0; i < 3 * numVerts; i + 3)
	{
		int aiIndex = (int)((i+2)*divedThree);
		//Vertex vertex;
		// Process vertex positions, normals and texture coordinates:
		//Vertex Positions:
		//GLfloat vector[3];
		postition[i] = meshes->mVertices[aiIndex].x;
		postition[i+1] = meshes->mVertices[aiIndex].y;
		postition[i+2] = meshes->mVertices[aiIndex].z;
		//vertex.Position = vector;
		//Vertex Normals:
		normals[i] = meshes->mNormals[aiIndex].x;
		normals[i+1] = meshes->mNormals[aiIndex].y;
		normals[i+2] = meshes->mNormals[aiIndex].z;
		//vertex.Normal = vector;
		
	}

	for (GLuint i = 0; i < 2 * numVerts; i + 2)
	{
		int aiIndex = (int)((i + 1)*0.5f);
		//Texture Coordinates:
		if (meshes->mTextureCoords[0]) //Check for texture coordinates.
		{
			GLfloat vec[2];
			texCoords[i] = meshes->mTextureCoords[0][aiIndex].x;
			texCoords[i+1] = meshes->mTextureCoords[0][aiIndex].y;
			//vertex.TexCoords = vec;
		}
		else
		{
			texCoords[i] = 0;
			texCoords[i + 1] = 0;
		}
		//vertices.push_back(vertex); //Add the current vertex to the vector array of model vertices.
	}

	// Process indices
	for (GLuint i = 0; i < numIndeces; i + 3)
	{
		aiFace face = meshes->mFaces[i];
	
		for (GLuint j = 0; j < face.mNumIndices; j++)
			indices[i + j] = face.mIndices[j];
	}
	/*
		// Process material
		if (mesh->mMaterialIndex >= 0)
		{
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
			vector<Texture> diffuseMaps = this->loadMaterialTextures(material,
				aiTextureType_DIFFUSE, "texture_diffuse");
			textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
			vector<Texture> specularMaps = this->loadMaterialTextures(material,
				aiTextureType_SPECULAR, "texture_specular");
			textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		}
*/
	
		Mesh *mesh = new Mesh("NotACube");

		mesh->data.normals = normals;
		mesh->data.vertices = postition;
		mesh->data.indices = indices;
		mesh->data.uv = texCoords;
		mesh->data.indexCount = numIndeces;
		mesh->data.vertexCount = numVerts;
		mesh->setupMesh();

		Shape::meshes.push_back(mesh);
	//return Mesh(vertices, indices, textures);
	return mesh;
}