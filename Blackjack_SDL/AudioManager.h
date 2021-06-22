#pragma once

#include "Definitions.h"

class AudioManager
{
private:

	Mix_Music* music;

	Uint16 audioFormat;
	int audioRate;
	int audioChannel;
	int audioBuffer;

	void LoadAudio(const char* path);
	void PlayLoop();

public:
	AudioManager();
	void Inititialize(const char* path);
	~AudioManager();

};

