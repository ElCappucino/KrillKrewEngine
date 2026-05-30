#include "SoundManager.h"
#include <iostream>
#include "nlohmann/json.hpp"
#include <fstream>

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
        volume = std::max(0, std::min(volume, 128));

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
        volume = std::max(0, std::min(volume, 128));

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

    void SoundManager::SaveVolumeConfig(const std::string& filename, float master, bool ismute_master, float music, bool ismute_music, float sfx, bool ismute_sfx)
    {
        std::ofstream file(filename);
        nlohmann::json data;

        if (!file.is_open())
        {
            KK_ERROR("SaveVolumeConfig: Cannot open volume config file");
        }
        else
        {
            data["MasterVolume"] = master;
            data["SFXVolume"] = sfx;
            data["BGMVolume"] = music;

            data["Master_isMute"] = ismute_master;
            data["SFX_isMute"] = ismute_music;
            data["BGM_isMute"] = ismute_sfx;

            file << data;

            file.close();
        }
    }
    void SoundManager::LoadVolumeConfig(const std::string& filename, float& master, bool& ismute_master, float& music, bool& ismute_music, float& sfx, bool& ismute_sfx)
    {
        std::ifstream file(filename);

        if (!file.is_open())
        {
            KK_ERROR("LoadVolumeConfig: Cannot open volume config file");
            return;
        }

        try
        {
            nlohmann::json data = nlohmann::json::parse(file);

            master = data.value("MasterVolume", master);
            sfx = data.value("SFXVolume", sfx);
            music = data.value("BGMVolume", music);

            ismute_master = data.value("Master_isMute", ismute_master);
            ismute_music = data.value("SFX_isMute", ismute_music);
            ismute_sfx = data.value("BGM_isMute", ismute_sfx);
        }
        catch (const std::exception& e)
        {
            KK_ERROR("LoadVolumeConfig: Invalid config file");
        }
    }
}
