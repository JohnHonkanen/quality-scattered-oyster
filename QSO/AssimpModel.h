//#include <GL/glew.h>
//#include <SDL.h>
#include "Shape.h"
#include "Mesh.h"

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing fla

#include <vector>

using namespace std;

struct Vertex {
	GLfloat* Position;
	GLfloat* Normal;
	GLfloat* TexCoords;
};

struct Texture {
	GLuint id;
	string type;
};

class AssimpModel : public Shape
{
public:

	void init();
	void buildModel();

private:

	vector<Mesh> meshes;
	string directory;

	void loadModel(string path);

	void processNode(aiNode* node, const aiScene* scene);
	Mesh* processMesh(aiMesh* mesh, const aiScene* scene);
	//vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
};