#include "TextureManager.h"

TextureManager *TextureManager::inst;
TextureManager::TextureManager()
{
}


TextureManager::~TextureManager()
{
}

TextureManager *TextureManager::instance()
{
	if (TextureManager::inst != nullptr)
		return TextureManager::inst;

	TextureManager::inst = new TextureManager();
	return TextureManager::inst;
}

void TextureManager::saveTextureMap(const string fileLocation, const string textureName, GLint min, GLint max)
{
	pair<string, GLuint>texturePair = pair<string, GLuint>(textureName, TextureGenerator::createTextureMap(fileLocation, min, max));
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
	delete this;
}

GLuint TextureManager::getTexture(const string textureName) {
	GLuint texture;
	map<string, GLuint>::iterator it = textures.find(textureName);
	if (it != textures.end()) {
		texture = it->second;
	}
	else {
		TextureManager::saveTextureMap(textureName, textureName);
		texture = textures[textureName];
	}
	return texture;
}