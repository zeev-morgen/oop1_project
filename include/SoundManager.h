#pragma once

#include <SFML/Audio.hpp>
#include <string>

class SoundManager {
public:
    // Get the singleton instance
    static SoundManager& instance();

    // Load sound files
    bool loadSounds();

    // Sound playback functions
    void playBackground();
    void stopBackground();
    void playExplosion();
    void playGift();
    void playMenu();
    void playGuard();

private:
    // Private constructor and destructor
    SoundManager();
    ~SoundManager();

    // Prevent copying
    SoundManager(const SoundManager&) = delete;
    SoundManager& operator=(const SoundManager&) = delete;

    // Sound buffers
    sf::SoundBuffer backgroundBuffer;
    sf::SoundBuffer explosionBuffer;
    sf::SoundBuffer giftBuffer;
    sf::SoundBuffer menuBuffer;
    sf::SoundBuffer guardBuffer;

    // Sound objects
    sf::Sound backgroundSound;
    sf::Sound explosionSound;
    sf::Sound giftSound;
    sf::Sound menuSound;
    sf::Sound guardSound;
};
