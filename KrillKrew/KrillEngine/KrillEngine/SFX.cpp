#include "SFX.h"
#include "Log.h"

SFX::SFX(const std::string& filePath) : chunk(nullptr) 
{
    chunk = Mix_LoadWAV(filePath.c_str());

    if (!chunk) {
        KK_ERROR("Failed to load sound effect: {0}", Mix_GetError());
    }
}

SFX::~SFX() 
{
    Mix_FreeChunk(chunk);
}

void SFX::Play(bool isLoop) 
{
    Mix_PlayChannel(-1, chunk, isLoop);
}

void SFX::Stop() 
{
    Mix_HaltChannel(-1);
}

void SFX::SetVolume(int volume) 
{
    Mix_VolumeChunk(chunk, volume);
}