#include "AudioComponent3D.h"

AudioComponent3D::AudioComponent3D(std::string name, glm::vec3 isoundPosition) : AudioComponent(name)
{
	soundPosition = convertToVec3df(isoundPosition);
	minimumDistance = 8.0f;
	active = false;
	init();
}

AudioComponent3D::~AudioComponent3D()
{
	if (musicStream)
	{
		musicStream->drop(); // deletes the musicstream if it exists.
	}
	engine->drop(); // deletes the engine.
}

void AudioComponent3D::init()
{
	// start the sound engine:
	engine = irrklang::createIrrKlangDevice();

	if (!engine) //If the engine failed to startup:
	{
		printf("ERROR: Engine failed to start up\n");
	}
}

void AudioComponent3D::playSound(char * file)
{
	if(!active)
	engine->play3D(file, soundPosition); //Plays the Audio file once at the soundLocation.
	active = true;
}

void AudioComponent3D::playMusic(char * file)
{
	if (!active)
	{
		musicStream = engine->play3D(file, soundPosition, true,false,true); //Plays the Audio file on a loop at the soundLocation.
	}
	if (musicStream) {
		musicStream->setMinDistance(minimumDistance);
		musicStream->setPosition(soundPosition);
	}
	active = true;

}

void AudioComponent3D::stopSound()
{
	engine->stopAllSounds();
	active = false;
}

void AudioComponent3D::setSoundPosition(glm::vec3 pos)
{
	soundPosition = convertToVec3df(pos);
}

void AudioComponent3D::setSoundPosition(irrklang::vec3df pos)
{
	soundPosition = pos;
}

void AudioComponent3D::setListenerPosition(glm::vec3 pos, glm::vec3 rot)
{
	//vec3 dts = convertToVec3(AudioComponent3D::soundPosition) - pos;
	//printf("Listener Posotion: %f,%f,%f \n", dts.x, dts.y, dts.z);
	//printf("Music Volume %f", musicStream->getVolume());
	setListenerPosition(AudioComponent3D::soundPosition, convertToVec3df(rot));
}

void AudioComponent3D::setListenerPosition(irrklang::vec3df pos, irrklang::vec3df rot)
{
	engine->setListenerPosition(pos, rot);
}

glm::vec3 AudioComponent3D::convertToVec3(irrklang::vec3df convertVec)
{
	return glm::vec3(convertVec.X, convertVec.Y, convertVec.Z);
}

irrklang::vec3df AudioComponent3D::convertToVec3df(glm::vec3 convertVec)
{
	return irrklang::vec3df(convertVec.x, convertVec.y, convertVec.z);
}
