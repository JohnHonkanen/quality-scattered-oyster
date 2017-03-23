#include "TextureGenerator.h"



TextureGenerator::TextureGenerator()
{
}


TextureGenerator::~TextureGenerator()
{
}

GLuint TextureGenerator::createTexture(const string fileLocation)
{
	cout << "Try load texture" <<endl;
	ILuint width;
	ILuint height;

	ILuint image;

	//Generate and Bind texture to the image loader
	ilGenImages(1, &image);
	ilBindImage(image);

	if (ilLoadImage((const ILstring)fileLocation.c_str())) {
		cout << "Texture successfully "<< fileLocation << " loaded!" << endl;
	}
	else {
		cout << ilGetError() << endl;
		cout << "Failed to load image at: " << fileLocation << endl;
	}

	// Convert image to usable image type
	ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

	width = ilGetInteger(IL_IMAGE_WIDTH);
	height = ilGetInteger(IL_IMAGE_HEIGHT);

	// Load and generate the texture

	GLuint textureID;

	/* 
	glGenTextures() takes as input how many textures we want to generate and stors them in a GLuint array given as it's second
	arguement (in our case, just a single GLuint)

	*/
	glGenTextures(1, &textureID);

	// We need to bind it so that any subsequent texture commands will configure the currently bound texture:
	glBindTexture(GL_TEXTURE_2D, textureID);

	// All upcoming GL_TEXTURE_2D operations now have effect on this texture object
	// Set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//See Documentation at http://www-f9.ijs.si/~matevz/docs/DevIL/il/f00059.htm

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, ilGetData());

	// Generate mipmap here
	glGenerateMipmap(GL_TEXTURE_2D);
	ilDeleteImages(1, &image); // Deletes image
	glBindTexture(GL_TEXTURE_2D, 0); // Unbinds the texture

	return textureID;;
}


GLuint TextureGenerator::createTextureMap(const string fileLocation, GLint min, GLint max)
{
	cout << "Try load texture" << endl;
	ILuint width;
	ILuint height;

	ILuint image;

	//Generate and Bind texture to the image loader
	ilGenImages(1, &image);
	ilBindImage(image);

	if (ilLoadImage((const ILstring)fileLocation.c_str())) {
		cout << "Texture successfully " << fileLocation << " loaded!" << endl;
	}
	else {
		cout << ilGetError() << endl;
		cout << "Failed to load image at: " << fileLocation << endl;
	}

	// Convert image to usable image type
	ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

	width = ilGetInteger(IL_IMAGE_WIDTH);
	height = ilGetInteger(IL_IMAGE_HEIGHT);

	// Load and generate the texture

	GLuint textureID;

	/*
	glGenTextures() takes as input how many textures we want to generate and stors them in a GLuint array given as it's second
	arguement (in our case, just a single GLuint)

	*/
	glGenTextures(1, &textureID);

	// We need to bind it so that any subsequent texture commands will configure the currently bound texture:
	glBindTexture(GL_TEXTURE_2D, textureID);

	// All upcoming GL_TEXTURE_2D operations now have effect on this texture object
	// Set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, max);

	//See Documentation at http://www-f9.ijs.si/~matevz/docs/DevIL/il/f00059.htm

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, ilGetData());

	// Generate mipmap here
	glGenerateMipmap(GL_TEXTURE_2D);
	ilDeleteImages(1, &image); // Deletes image
	glBindTexture(GL_TEXTURE_2D, 0); // Unbinds the texture

	return textureID;
}

GLuint TextureGenerator::createCubeMap(const vector<string> faces)
{

	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	for (GLuint i = 0; i < faces.size(); i++) {
		cout << "Try load cubemap texture" << i << endl;
		ILuint width;
		ILuint height;

		ILuint image;

		//Generate and Bind texture to the image loader
		ilGenImages(1, &image);
		ilBindImage(image);

		if (ilLoadImage((const ILstring)faces[i].c_str())) {
			cout << "Cubemap Texture " << faces[i] << " successfully loaded!" << endl;
		}
		else {
			cout << ilGetError() << endl;
			cout << "Failed to load image at: " << faces[i] << endl;
		}

		// Convert image to usable image type
		ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE);

		width = ilGetInteger(IL_IMAGE_WIDTH);
		height = ilGetInteger(IL_IMAGE_HEIGHT);

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, ilGetData());

		// Unbind and De-allocate memory
		ilDeleteImages(1, &image); // Deletes image
	}
	// Set cubemap parameters
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	
	// De-allocate memory
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	return textureID;
}
