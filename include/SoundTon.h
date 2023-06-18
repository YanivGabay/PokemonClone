#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System/Vector2.hpp>
#include <unordered_map>
#include <memory>
#include <iostream>
#include <array>
#include <string>

#include "tileson/tileson.hpp"
#include "utilities.h"


class SoundTon
{
public:
	static SoundTon& getInstance()
	{
		static SoundTon instance;
		return instance;
	}

	void playSound(std::string soundName)
	{
		m_sound[soundName].play();
	}

	void stopSound(std::string soundName)
	{
		if (m_sound.find(soundName) != m_sound.end()) {
			m_sound[soundName].stop();
		}
	}

private:
	std::unordered_map<std::string, sf::SoundBuffer> m_soundBuffer;
	std::unordered_map<std::string, sf::Sound> m_sound;

	//------

	SoundTon(const SoundTon&) = delete;
	SoundTon& operator=(const SoundTon&) = delete;

	SoundTon()
		: m_soundBuffer{ {"OPEN", sf::SoundBuffer()} },
		  m_sound{ {"OPEN", sf::Sound()} }
	{
		loadSound();

		// m_sound["OPEN"].play();
	}

	void loadSound()
	{
		m_soundBuffer["OPEN"].loadFromFile("resources/pokemonOpening.ogg");

		// --------------

		m_sound["OPEN"].setBuffer(m_soundBuffer["OPEN"]);
		m_sound["OPEN"].setLoop(true);
	}
};
