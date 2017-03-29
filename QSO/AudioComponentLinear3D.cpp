#include "AudioComponentLinear3D.h"

AudioComponentLinear3D::AudioComponentLinear3D(std::string name) : AudioComponent(name)
{
	active = false;
	init();
}

AudioComponentLinear3D::~AudioComponentLinear3D()
{
	engine->drop(); // deletes the engine.
}

void AudioComponentLinear3D::init()
{
	// start the sound engine:
	engine = irrklang::createIrrKlangDevice();

	if (!engine) //If the engine failed to startup:
	{
		printf("ERROR: Engine failed to start up\n");
	}
}

void AudioComponentLinear3D::playSound(char * file)
{
	if (!active)
		engine->play2D(file); //Plays the Audio file once.
	determineVolume();
	active = true;
}

void AudioComponentLinear3D::playMusic(char * file)
{
	determineVolume();
	if(!active)
	{
		musicStream = engine->play2D(file, true, false, true); //Plays the Audio file on a loop.
	}
	determineVolume();
	active = true;
}

void AudioComponentLinear3D::stopSound()
{
	engine->stopAllSounds();
	active = false;
}

void AudioComponentLinear3D::setSoundPosition(glm::vec3 pos)
{
	soundPosition = pos;
	determineVolume();
	//engine->setSoundVolume(linearVolume);
}

void AudioComponentLinear3D::setListenerPosition(glm::vec3 pos)
{
	listenerPosition = pos;
	determineVolume();
	//engine->setSoundVolume(linearVolume);
}


void AudioComponentLinear3D::determineVolume()
{

	
	float distanceBetween = sqrt(((soundPosition.x - listenerPosition.x)*(soundPosition.x - listenerPosition.x)) +
								((soundPosition.y - listenerPosition.y)*(soundPosition.y - listenerPosition.y)) +
								((soundPosition.z - listenerPosition.z)*(soundPosition.z - listenerPosition.z)));

	if (distanceBetween > 100.0f) {
		linearVolume = 0.0f;
	} else {
		linearVolume = ((100.0f - distanceBetween) / 100);
		//linearVolume = 1.0f;
	}

	if (musicStream)
		musicStream->setVolume(linearVolume);

	printf("Volume: %f \n", distanceBetween);

}

