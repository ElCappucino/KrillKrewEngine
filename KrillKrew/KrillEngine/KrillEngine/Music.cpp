#include "Music.h"
#include "Log.h"

Music::Music(const std::string& filePath) : music(nullptr) 
{
    music = Mix_LoadMUS(filePath.c_str());

    if (!music) {
        KK_ERROR("Failed to load music: {0}", Mix_GetError());
    }
}

Music::~Music() 
{
    Mix_FreeMusic(music);
}

void Music::Play(bool isLoop)
{
    Mix_PlayMusic(music, isLoop);
}

void Music::Stop() 
{
    Mix_HaltMusic();
}

void Music::SetVolume(int volume) 
{
    Mix_VolumeMusic(volume);
}