#pragma once
#include "BaseState.h"

class FadeOutState :public BaseState
{
public:

	FadeOutState(StateMachine& states,sf::Color color) : BaseState(states)
	{
		m_fadeShape.setSize(sf::Vector2f(getWindowSize()));
		m_fadeShape.setFillColor(color);
	}

	~FadeOutState()
	{
	}
	 void entry() {

	 }
	 void exit() {

	 }

	 void update(float dt) {
		 float decrement = 255.0f / 1.0f * dt; // Adjust the fade-out speed as needed

		 m_progress -= static_cast<sf::Uint8>(decrement);

		 if (m_progress <= 0)
		 {
			 m_progress = 0;
			 setStatus(false); // Set the status to false to indicate that the fade-out is complete
		 }
	 }
	 void handleEvents(sf::Event event) {

	 }
	 void draw(sf::RenderWindow& window) {
		 window.draw(m_fadeShape);
	 }

	

private:
	
	sf::RectangleShape m_fadeShape;
	sf::Uint8 m_progress {255};
	
};
