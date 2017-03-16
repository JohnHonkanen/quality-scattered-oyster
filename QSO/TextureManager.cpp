#include "TextureManager.h"

TextureManager::TextureManager()
{
}


TextureManager::~TextureManager()
{
}

void TextureManager::saveTexture(const string fileLocation, const string textureName)
{
	pair<string, GLuint>texturePair = pair<string, GLuint>(textureName, TextureGenerator::createTexture(fileLocation));
	textures.insert(texturePair);
}

void TextureManager::deleteTexture(const string textureName) {
	glDeleteTextures(1, &textures[textureName]);
}

void TextureManager::destroy() {
	map<string, GLuint>::iterator it = textures.begin();

	for (it; it == textures.end(); it++) {
		deleteTexture(it->first);
	}
}

GLuint TextureManager::getTexture(const string textureName) {
	return textures[textureName];
}