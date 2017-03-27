#include "AssimpLoader.h"

vector<Mesh*> AssimpLoader::meshes;
vector<AssimpTexture>  AssimpLoader::textures_loaded;
string AssimpLoader::directory;

vector<Mesh*> AssimpLoader::loadModel(string path, vector<Material> &material)
{
	// Clears all mesh data
	AssimpLoader::meshes.clear();

	// Import Assimp
	Assimp::Importer import;

	const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate |aiProcess_GenSmoothNormals | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)	// Detect if there's a problem
	{
		cout << "ERROR::ASSIMP::" << import.GetErrorString() << endl;	// Output an error.
		return vector<Mesh*>();
	}

	AssimpLoader::directory = path.substr(0, path.find_last_of('/'));

	return AssimpLoader::processNode(scene->mRootNode, scene, material);
}

vector<Mesh*> AssimpLoader::processNode(aiNode * node, const aiScene * scene, vector<Material> &material)
{
	// Process all the node's meshes (if any)

	for (GLuint i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* meshes = scene->mMeshes[node->mMeshes[i]];
		AssimpLoader::meshes.push_back(AssimpLoader::processMesh(meshes, scene, material));
	}

	// Then do the same for each of its children
	for (GLuint i = 0; i < node->mNumChildren; i++)
	{
		AssimpLoader::processNode(node->mChildren[i], scene, material);
	}

	return AssimpLoader::meshes;
}

Mesh* AssimpLoader::processMesh(aiMesh* mesh, const aiScene* scene, vector<Material> &material)
{
	int meshType = 3;
	//Vertex vertices;
	vector<Texture> textures;
	int numVerts = mesh->mNumVertices;
	int numIndices = mesh->mNumFaces;
	GLfloat* normals = new GLfloat[3 * numVerts];
	GLfloat* postition = new GLfloat[3 * numVerts];
	GLfloat* texCoords = new GLfloat[2 * numVerts];

	vector<GLuint>indices;
	//vector<Texture> textures;
	float divedThree = 1 / 3.0f;
	for (GLuint i = 0; i < 3 * numVerts; i += 3)
	{
		int aiIndex = (int)((i + 2)*divedThree);
		//Vertex vertex;
		// Process vertex positions, normals and texture coordinates:
		//Vertex Positions:
		//GLfloat vector[3];
		postition[i] = mesh->mVertices[aiIndex].x;
		postition[i + 1] = mesh->mVertices[aiIndex].y;
		postition[i + 2] = mesh->mVertices[aiIndex].z;
		//vertex.Position = vector;
		//Vertex Normals:
		normals[i] = mesh->mNormals[aiIndex].x;
		normals[i + 1] = mesh->mNormals[aiIndex].y;
		normals[i + 2] = mesh->mNormals[aiIndex].z;
		//vertex.Normal = vector;

	}

	for (GLuint i = 0; i < 2 * numVerts; i += 2)
	{
		int aiIndex = (int)((i + 1)*0.5f);
		//Texture Coordinates:
		if (mesh->mTextureCoords[0]) //Check for texture coordinates.
		{
			GLfloat vec[2];
			texCoords[i] = mesh->mTextureCoords[0][aiIndex].x;
			texCoords[i + 1] = mesh->mTextureCoords[0][aiIndex].y;
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
	for (GLuint i = 0; i < numIndices; i++)
	{
		aiFace face = mesh->mFaces[i];

		for (GLuint j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	GLuint *tIndices = new GLuint[indices.size()];

	for (int i = 0; i < indices.size(); i++) {
		tIndices[i] = indices[i];
	}

	// Process materials
	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		// We assume a convention for sampler names in the shaders. Each diffuse texture should be named
		// as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
		// Same applies to other texture as the following list summarizes:
		// Diffuse: texture_diffuseN
		// Specular: texture_specularN
		// Normal: texture_normalN

		// 1. Diffuse maps
		vector<Texture> diffuseMaps = AssimpLoader::loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		// 2. Specular maps
		vector<Texture> specularMaps = AssimpLoader::loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}
	//Load the Bones
	for (int i = 0; i < mesh->mNumBones; i++){
		aiBone *aibone = mesh->mBones[i];
		aibone->mOffsetMatrix.
		printf("Found Bone: %s \n", aibone->mName.C_Str());
		//Find associating Bone, Parent and Child
	}

	for (int i = 0; i < scene->mNumAnimations; i++) {
		aiAnimation * animation = scene->mAnimations[i];
		printf("Found Animation: %s \n", animation->mName.C_Str());
	}

	Material mat;
	mat.textures = textures;
	material.push_back(mat);

	Mesh *meshData = new Mesh("assimpModel");

	meshData->data.normals = normals;
	meshData->data.vertices = postition;
	meshData->data.indices = tIndices;
	meshData->data.uv = texCoords;
	meshData->data.indexCount = indices.size();
	meshData->data.vertexCount = numVerts;
	meshData->setupMesh();

	return meshData;
}

vector<Texture> AssimpLoader::loadMaterialTextures(aiMaterial * mat, aiTextureType type, string typeName)
{
	vector<Texture> textures;
	int number = 0;
	for (GLuint i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		// Check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
		GLboolean skip = false;
		for (GLuint j = 0; j < textures_loaded.size(); j++)
		{
			if (std::strcmp(textures_loaded[j].path.C_Str(), str.C_Str()) == 0)
			{
				textures.push_back(textures_loaded[j].texture);
				skip = true; // A texture with the same filepath has already been loaded, continue to next one. (optimization)
				break;
			}
		}
		if (!skip)
		{   // If texture hasn't been loaded already, load it
			Texture texture{
				AssimpLoader::directory + '/'+ str.C_Str(),
				convertFromTypeAssimp(type),
				number++
			};
			textures.push_back(texture);
			AssimpTexture aTexture{
				str,
				texture
			};
			AssimpLoader::textures_loaded.push_back(aTexture);  // Store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
		}
	}
	return textures;
}

TEXTURE_TYPE AssimpLoader::convertFromTypeAssimp(aiTextureType type)
{
	TEXTURE_TYPE tType;
	switch (type) {
	case aiTextureType_DIFFUSE:
		tType = DIFFUSE;
		break;
	case aiTextureType_SPECULAR:
		tType = SPECULAR;
		break;
	default:
		tType = NO_TEXTURE_TYPE;
	}

	return tType;
}
