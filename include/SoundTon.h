#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System/Vector2.hpp>
#include "tileson/tileson.hpp"

#include <vector>
#include <memory>
#include <iostream>
#include <array>
#include <string>
#include "utilities.h"


class SoundTon
{
public:
	static SoundTon& getInstance()
	{
		static SoundTon instance;
		return instance;
	}

	void playSound(soundNames soundName)
	{
		m_sound[soundName].play();
	}

	void stopSound(soundNames soundName)
	{
		m_sound[soundName].stop();
	}

	void setVolume(soundNames soundName, float vol)
	{
		m_sound[soundName].setVolume(vol);
	}

private:
	std::vector<sf::SoundBuffer> m_soundBuffer;
	std::vector<sf::Sound> m_sound;

	//------

	SoundTon(const SoundTon&) = delete;
	SoundTon& operator=(const SoundTon&) = delete;

	SoundTon()
		: m_soundBuffer(sound_files.size()),
		  m_sound(sound_files.size())
	{
		loadSound();
	}

	void loadSound()
	{
		for (size_t i = 0; i < sound_files.size(); ++i)
		{
			m_soundBuffer[i].loadFromFile(sound_files[i]);
			
			// ------------
			
			m_sound[i].setBuffer(m_soundBuffer[i]);

			m_sound[i].setVolume(SOUND_VOLUME);
			m_sound[i].setLoop(true);
		}
		
		m_sound[soundNames::PORTAL].setVolume(20.f);
		m_sound[soundNames::PORTAL].setLoop(false);
		m_sound[soundNames::NM_CLICK].setVolume(10.f);
		m_sound[soundNames::NM_CLICK].setLoop(false);
		m_sound[soundNames::POKEMON_CHOOSE].setVolume(10.f);
		m_sound[soundNames::POKEMON_CHOOSE].setLoop(false);
		m_sound[soundNames::MENU].setVolume(10.f);
		m_sound[soundNames::MENU].setLoop(false);
		m_sound[soundNames::CLICK].setVolume(20.f);
		m_sound[soundNames::CLICK].setLoop(false);
		m_sound[soundNames::HEAL].setVolume(10.f);
		m_sound[soundNames::HEAL].setLoop(false);
		m_sound[soundNames::SAVING].setVolume(10.f);
		m_sound[soundNames::SAVING].setLoop(false);
	}
};
