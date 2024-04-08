#include "MusicManager.h"

void MusicManager::toggleMusic(bool state) {
    isMusicOn = state;
    if (isMusicOn && m_backgroundMusic != nullptr) {
        playBackgroundMusic();
    }
    else {
        stopBackgroundMusic();
    }
}

void MusicManager::setBackgroundMusic(const std::string& musicPath) {
    if (m_backgroundMusic != nullptr) {
        Mix_FreeMusic(m_backgroundMusic);
    }
    m_backgroundMusic = Mix_LoadMUS(musicPath.c_str());
}

void MusicManager::playBackgroundMusic() {
    if (m_backgroundMusic != nullptr) {
        Mix_PlayMusic(m_backgroundMusic, -1);
    }
}

void MusicManager::stopBackgroundMusic() {
    Mix_HaltMusic();
}