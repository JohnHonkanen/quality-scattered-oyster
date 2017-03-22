#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing fla

#include <vector>

#include "Mesh.h"

using namespace std;

struct Texture {
	GLuint id;
	string type;
};

class AssimpLoader
{
private:
	static vector<Mesh*> meshes;
	static string directory;

	static vector<Mesh*> processNode(aiNode* node, const aiScene* scene);
	static Mesh* processMesh(aiMesh* mesh, const aiScene* scene);
	//vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);

public:
	static vector<Mesh*> loadModel(string path);

};