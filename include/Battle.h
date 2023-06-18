#pragma once
#include "Resources.h"

class Battle
{
public:
	Battle() {
		m_backGround.setScale(
			static_cast<float>(m_window.x) / m_backGround.getTexture()->getSize().x,
			static_cast<float>(m_window.y) / m_backGround.getTexture()->getSize().y
			
		);
		
	};
	~Battle() {};

private:
	sf::Sprite& m_backGround;
	const sf::Vector2u m_window{ Resources::getInstance().getWindow().getSize() };

};

