#pragma once
#include "BaseState.h"
#include "Battle.h"
#include "Resources.h"

enum class WhosAttack
{
	Enemy,
	Player
};

class TakeTurnState : public BaseState
{
public:
	TakeTurnState(Stack<BaseState>& states, Battle& battle, std::shared_ptr<Pokemon> playerPokemon,
				  std::shared_ptr<Pokemon> enemyPokemon, WhosAttack ID)
		: BaseState(states), m_battle(battle), m_playerPokemon(playerPokemon), m_wildPokemon(enemyPokemon),
		m_id(ID), m_attackingPokemon(ID == WhosAttack::Player ? playerPokemon->getBackSprite() : enemyPokemon->getFrontSprite()),
		m_defendingPokemon(ID == WhosAttack::Player ? enemyPokemon->getFrontSprite() : playerPokemon->getBackSprite()),
		m_originalPos(m_attackingPokemon.getPosition()), m_speed(ID == WhosAttack::Player ? 100.0f : -100.0f)
	{
		entry();

	}

	~TakeTurnState() = default;
	void entry()override
	{

		m_id == WhosAttack::Player ?
			m_battle.setAdviceText("Attack!!") : m_battle.setAdviceText("Be Careful!");


	}

	void exit()override
	{

	}
	void moveTowards(sf::Time dt)
	{


		m_distance += (m_speed * dt.asSeconds());
		sf::Vector2f targetPos = m_originalPos + sf::Vector2f(m_distance, -m_distance);
		m_attackingPokemon.setPosition(targetPos);


	}

	void moveBack(sf::Time dt)
	{

		
		m_distance += (m_speed * dt.asSeconds());
		sf::Vector2f targetPos = m_afterMove + sf::Vector2f(m_distance, -m_distance);
		m_attackingPokemon.setPosition(targetPos);

	}
	void update(sf::Time dt)override
	{
		m_elapsedTime += dt;

		// If the sprite hasn't reached the target position, move it towards the target
		if (!m_movmentCompleted)
		{
			moveTowards(dt);
			float threshold = 60.0f;
			if (m_id == WhosAttack::Enemy)
			{
				threshold = -threshold; // For the enemy, we have to check for negative distance
			}
			m_movmentCompleted = (m_distance >= threshold);
		}
		// If the sprite reached the target, start blinking
		else if (!m_blinkingCompleted)
		{
			m_afterMove = m_attackingPokemon.getPosition();
			m_total += dt.asSeconds();
			if (m_elapsedTime.asSeconds() >= m_blinkTime.asSeconds())
			{
				m_blinkColor.a = (m_blinkColor.a == 255) ? 64 : 255;
				m_defendingPokemon.setColor(m_blinkColor);
				m_elapsedTime -= m_blinkTime;
			}

			// Check if blinking duration has passed
			sf::Time blinkDuration = sf::seconds(2.5f);
			if (m_total >= blinkDuration.asSeconds())
			{
				m_blinkColor.a = 255;
				m_defendingPokemon.setColor(m_blinkColor);

				m_blinkingCompleted = true;
				m_elapsedTime = sf::seconds(0.0f); // Reset elapsedTime for the next phase
				m_distance = 0.0f; // Reset the distance to the point where we started blinking
				m_speed = -m_speed;
			}
		}
		// Move the sprite back
		else
		{

			moveBack(dt);

			// Check if the sprite is back to its original position (or close enough)
			if (m_distance <= -60.0f)
			{
				m_attackingPokemon.setPosition(m_originalPos);

				setStatus(false);
				// Insert code here to transition to next state or perform some other action
			}
		}
	}


	void handleEvents(sf::Event event)override
	{

	}
	void draw(sf::RenderWindow& window)override
	{

		m_battle.draw(window);
	}
private:
	bool m_guiUpdateCompleted {false};
	bool m_blinkingCompleted{ false };
	bool m_movmentCompleted{ false };
	float m_distance{ 0 };
	float m_speed{ 0 };
	WhosAttack m_id;

	std::shared_ptr<Pokemon> m_playerPokemon;
	std::shared_ptr<Pokemon> m_wildPokemon;

	sf::Sprite& m_attackingPokemon;
	sf::Sprite& m_defendingPokemon;
	Battle& m_battle;

	sf::Vector2f m_originalPos;
	sf::Vector2f m_afterMove;
	float m_total{ 0 };
	sf::Time m_elapsedTime {sf::seconds(0.0f)};
	sf::Time m_blinkTime {sf::seconds(0.15f)};
	sf::Color m_blinkColor {sf::Color::White};
};
