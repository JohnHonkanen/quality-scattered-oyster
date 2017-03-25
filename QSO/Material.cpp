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
	switch (enumType)
	{
	case DIFFUSE:
		type = "diffuse";
		break;
	case SPECULAR:
		type = "specular";
		break;
	case EMISSION:
		type = "emission";
		break;
	case BACKGROUND_TEXTURE:
		type = "terrainTexture.backgroundTexture";
		break;
	case R_TEXTURE:
		type = "terrainTexture.rTexture";
		break;
	case G_TEXTURE:
		type = "terrainTexture.gTexture";
		break;
	case B_TEXTURE:
		type = "terrainTexture.bTexture";
		break;
	case BLEND_MAP:
		type = "terrainTexture.blendMap";
		break;
	case NO_TEXTURE_TYPE:
		type = "none";
		break;
	default:
		break;
	}
	return type;
}
