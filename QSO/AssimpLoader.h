#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing fla

#include <vector>

#include "Mesh.h"
#include "Material.h"

using namespace std;

struct AssimpTexture {
	aiString path;
	Texture texture;
};
class AssimpLoader
{
private:
	static vector<Mesh*> meshes;
	static vector<AssimpTexture> textures_loaded;
	static string directory;

	static vector<Mesh*> processNode(aiNode* node, const aiScene* scene, vector<Material> &material);
	static Mesh* processMesh(aiMesh* mesh, const aiScene* scene, vector<Material> &material);
	static vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
	static TEXTURE_TYPE convertFromTypeAssimp(aiTextureType type);

public:
	static vector<Mesh*> loadModel(string path, vector<Material> &material);

};