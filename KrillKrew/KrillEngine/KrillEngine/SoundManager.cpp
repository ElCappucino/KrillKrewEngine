#include "SoundManager.h"
#include <iostream>

namespace KrillSoundManager
{
    SoundManager* SoundManager::instance = nullptr;

    SoundManager::SoundManager() 
    {
        Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    }

    SoundManager::~SoundManager() {
        Cleanup();
    }
    SoundManager* SoundManager::GetInstance()
    {
        if (instance == nullptr) {
            instance = new SoundManager();
        }
        return instance;
    }
    void SoundManager::LoadSFX(const std::string& name, const std::string& filePath)
    {
        if (SFXSounds.find(name) == SFXSounds.end()) {
            SFXSounds[name] = new SFX(filePath);
        }
        else {
            KK_ERROR("SFX {0} already loaded!", name);
        }
    }
    void SoundManager::LoadMusic(const std::string& name, const std::string& filePath)
    {
        if (musicSounds.find(name) == musicSounds.end()) {
            musicSounds[name] = new Music(filePath);
        }
        else {
            KK_ERROR("Music {0} already loaded!", name);
        }
    }

    void SoundManager::PlaySFX(const std::string& name, bool isloop)
    {
        if (SFXSounds.find(name) != SFXSounds.end()) {
            SFXSounds[name]->Play(isloop);
        }
        else {
            KK_ERROR("SFX {0} not found!", name);
        }
    }
    void SoundManager::PlayMusic(const std::string& name, bool isloop)
    {
        if (musicSounds.find(name) != musicSounds.end()) {
            musicSounds[name]->Play(isloop);
        }
        else {
            KK_ERROR("Music {0} not found!", name);
        }
    }


    void SoundManager::StopSFX(const std::string& name)
    {
        if (SFXSounds.find(name) != SFXSounds.end()) {
            SFXSounds[name]->Stop();
        }
        else
        {
            KK_ERROR("Can't stop SFX. No SFX in list : {0}", name);
        }
    }
    void SoundManager::StopMusic(const std::string& name)
    {
        if (musicSounds.find(name) != musicSounds.end()) {
            musicSounds[name]->Stop();
        }
        else
        {
            KK_ERROR("Can't stop music. No music in list : {0}", name);
        }
    }

    void SoundManager::SetVolumeSFX(const std::string& name, int volume)
    {
        if (SFXSounds.find(name) != SFXSounds.end()) {
            SFXSounds[name]->SetVolume(volume);
        }
        else
        {
            KK_ERROR("Can't set SFX Volume. No music in list : {0}", name);
        }
    }
    void SoundManager::SetVolumeMusic(const std::string& name, int volume)
    {
        if (musicSounds.find(name) != musicSounds.end()) {
            musicSounds[name]->SetVolume(volume);
        }
        else
        {
            KK_ERROR("Can't set music Volume. No music in list : {0}", name);
        }
    }

    void SoundManager::SetVolumeAllSFX(int volume)
    {
        for (auto music : SFXSounds)
        {
            SetVolumeSFX(music.first, volume);
        }
    }
    void SoundManager::SetVolumeAllMusic(int volume)
    {
        for (auto music : musicSounds)
        {
            SetVolumeMusic(music.first, volume);
        }
    }

    void SoundManager::Cleanup()
    {
        for (auto& pair : SFXSounds) {
            delete pair.second;
        }
        SFXSounds.clear();

        for (auto& pair : musicSounds) {
            delete pair.second;
        }
        musicSounds.clear();
    }
}
