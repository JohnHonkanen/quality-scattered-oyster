#include "BackgroundMusicManager.h"

BackgroundMusicManager::BackgroundMusicManager()
{
	audioComponent = new AudioComponent2D("BackgroundMusic Auido Component");
	//All music files used here were created by Tanner Helland and can be found here: http://www.tannerhelland.com/music-directory/
	musicFile[0] = "audio/music/TheHaunting.ogg";
	musicFile[1] = "audio/music/FromHere.ogg";
	musicFile[2] = "audio/music/Surreptitious.ogg";
	currentSong = 0;
	songCount = 3;
}

BackgroundMusicManager::~BackgroundMusicManager()
{
	delete audioComponent;
}


void BackgroundMusicManager::play()
{
	stop();
	audioComponent->playMusic(musicFile[currentSong]);
}

void BackgroundMusicManager::stop()
{
	audioComponent->stopSound();
}

void BackgroundMusicManager::nextMusic()
{
	if (currentSong == songCount - 1) {
		currentSong = 0;
	}
	else {
		currentSong++;
	}
	play();
}

void BackgroundMusicManager::setMusic(int i)
{
	currentSong = i;
	play();
}


