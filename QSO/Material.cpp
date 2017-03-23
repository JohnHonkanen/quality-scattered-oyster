#include "Material.h"

Material::Material() :Component("") {

}

Material::Material(string name, Shader program):Component(name)
{
	Material::program = program;
}

Material::~Material()
{
}

void Material::addTexture(string textureName, TEXTURE_TYPE type, int number)
{
	Texture texture = {
		textureName,
		type,
		number,
	};

	Material::textures.push_back(texture);
}

string Material::convertTypeToString(TEXTURE_TYPE enumType)
{
	string type = "";
	switch (enumType) {
	case DIFFUSE:
		type = "diffuse";
		break;
	case SPECULAR:
		type = "specular";
		break;
	case EMISSION:
		type = "emission";
		break;
	}
	return type;
}
