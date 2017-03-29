#pragma once
#include "AudioComponent2D.h"

class BackgroundMusicManager
{
public:
	BackgroundMusicManager();
	~BackgroundMusicManager();
	void play();			//Plays the current piece of music.
	void stop();			//Stops music from being played.
	void nextMusic();		//Cycles through music list and plays the next available file.
	void setMusic(int i);	//Plays a file at a specific place in the list.
private:
	char* musicFile[3];		//Used to store the list of songs.
	int songCount;			//How many songs are in the list;
	int currentSong;		//The song currently being played with respect to the list.

	AudioComponent2D *audioComponent;	//Audio component used to play our music.
};
