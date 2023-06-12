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
    void playAnimation(T animationType, sf::Time elapsedTime, sf::Sprite& sprite)
    {
        if (sequences.empty())
            return;

        auto& sequence = sequences[animationType];
        auto& frames = sequence.first;
        float duration = sequence.second;

        // Convert elapsedTime to seconds and accumulate
        m_total += elapsedTime.asSeconds();
       // std::cout << "duration is: " << duration << std::endl;
       // std::cout << "elapsedTime.asSeconds() is: " << elapsedTime.asSeconds() << std::endl;
       // std::cout << "m_total is: " << m_total << std::endl;
       // std::cout << "frameIndex:" << frameIndex << std::endl;
        // Check if it's time to advance to the next frame
        if (m_total > duration)
        {
           
            frameIndex++;
            if (frameIndex >= frames.size())
                frameIndex = 0;
            
            if (frameIndex < frames.size())
            {
                sprite.setTextureRect(frames[frameIndex]);
            }
            

            // Reset the accumulator
            m_total -= duration;
        }
    }

private:
	// <class of animations, pairs of squares for spritesheet, and a float for that animation time
	std::unordered_map<T, std::pair<std::vector<sf::IntRect>, float>> sequences;
	float m_total{ 0 };
	size_t frameIndex{ 0 };

};
