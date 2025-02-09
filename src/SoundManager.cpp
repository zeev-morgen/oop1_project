#include "SoundManager.h"
#include <iostream>

// singleton instance
SoundManager& SoundManager::instance() {
    static SoundManager instance;
    return instance;
}

// constructor
SoundManager::SoundManager() {
}

// destructor
SoundManager::~SoundManager() {
}

// load sound files
bool SoundManager::loadSounds() {
    if (!backgroundBuffer.loadFromFile("background.wav")) {
        std::cerr << "Error loading background sound" << std::endl;
        return false;
    }
    if (!explosionBuffer.loadFromFile("explosion.wav")) {
        std::cerr << "Error loading explosion sound" << std::endl;
        return false;
    }
    if (!guardBuffer.loadFromFile("guard.ogg")) {
        std::cerr << "Error loading guard sound" << std::endl;
        return false;
    }

    backgroundSound.setBuffer(backgroundBuffer);
    backgroundSound.setLoop(true);
    backgroundSound.setVolume(30);

    explosionSound.setBuffer(explosionBuffer);
    explosionSound.setVolume(60);

    guardSound.setBuffer(guardBuffer);
    guardSound.setVolume(60);

    return true;
}

void SoundManager::playBackground() { backgroundSound.play(); }
void SoundManager::stopBackground() { backgroundSound.stop(); }
void SoundManager::playExplosion() { explosionSound.play(); }
void SoundManager::playGift() { giftSound.play(); }
void SoundManager::playMenu() { menuSound.play(); }
void SoundManager::playGuard() { guardSound.play(); }
