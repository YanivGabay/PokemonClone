#pragma once
#include "Resources.h"



template <class T >
class Animation
{
public:
	Animation()
	{
		
	}

	~Animation()
	{
	}
	void addSequence(T animationType, const std::vector<sf::IntRect>& frames, float duration)
	{
		sequences[animationType] = std::make_pair(frames, duration);
	}
	void playAnimation(T animationType, float elapsedTime,sf::Sprite& sprite)
	{
		if (sequences.empty())
			return;
	
		auto& sequence = sequences[animationType];
		auto& frames = sequence.first;
		float duration = sequence.second;

		// Calculate the index of the current frame
		size_t frameIndex = static_cast<size_t>((elapsedTime / duration) * frames.size()) % frames.size();
		sprite.setTextureRect(frames[frameIndex]);
	}
private:
	// <class of animations, pairs of squares for spritesheet, and a float for that animation time
	std::unordered_map<T, std::pair<std::vector<sf::IntRect>, float>> sequences;
	
	

};
