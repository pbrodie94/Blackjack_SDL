#include "AudioManager.h"

AudioManager::AudioManager()
{

}

void AudioManager::Inititialize(const char* path)
{
	audioChannel = 2;
	audioBuffer = 4096;
	audioRate = 22050;
	audioFormat = AUDIO_S16;

	if (SDL_Init(SDL_INIT_AUDIO) != 0)
	{
		cerr << "Unable to initialize SDL_Audio" << endl;
		throw 1;
	}

	if (Mix_OpenAudio(audioRate, audioFormat, audioChannel, audioBuffer) != 0)
	{
		cerr << "Unable to open audio." << SDL_GetError() << endl;
		throw 1;
	}

	LoadAudio(path);
}

AudioManager::~AudioManager()
{

}

void AudioManager::LoadAudio(const char* path)
{
	Mix_QuerySpec(&audioRate, &audioFormat, &audioChannel);
	music = Mix_LoadMUS(path);

	if (music == nullptr)
	{
		cerr << "Failed to load audio." << endl;
	}
	else {
		PlayLoop();
	}
}

void AudioManager::PlayLoop()
{
	Mix_PlayMusic(music, -1);
}
