#pragma once

#include "Resources.h"

enum class AnimationMode
{
    SingleLoop,
    Continuous
};

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
    void setAnimationMode(AnimationMode mode)
    {
        if (mode == AnimationMode::SingleLoop)
        {
            m_active = false;
        }
        m_mod = mode;
    }
	void addSequence(T animationType, const std::vector<sf::IntRect>& frames, float duration)
	{
		sequences[animationType] = std::make_pair(frames, duration);
	}
    const AnimationMode getMod()
    {
        return m_mod;
    }
    void setToActive()
    {
        m_active = true;
   }
    void setToNotActive()
    {
        m_active = false;
    }
    void playAnimation(T animationType, sf::Time elapsedTime, sf::Sprite& sprite)
    {
        if (sequences.empty() || !m_active)
            return;

        auto& sequence = sequences[animationType];
        auto& frames = sequence.first;
        float duration = sequence.second;

        // Convert elapsedTime to seconds and accumulate
        m_total += elapsedTime.asSeconds();
        
        // Check if it's time to advance to the next frame
        if (m_total > duration)
        {
            frameIndex++;
            if (frameIndex >= frames.size())
            {
                if (getMod() == AnimationMode::SingleLoop)
                {
                    setToNotActive();
                }
                frameIndex = 0;
            }
               
            
            if (frameIndex < frames.size())
            {
                sprite.setTextureRect(frames[frameIndex]);
            }
            
            // Reset the accumulator
            m_total -= duration;
        }
    }
    bool getActiveState()
    {
        return m_active;
    }

private:
	// <class of animations, pairs of squares for spritesheet, and a float for that animation time
	std::unordered_map<T, std::pair<std::vector<sf::IntRect>, float>> sequences;
	
    float m_total{ 0 };
	size_t frameIndex{ 0 };
    bool m_active{ true };
    AnimationMode m_mod{ AnimationMode::Continuous };

};
