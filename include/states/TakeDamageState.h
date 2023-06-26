#pragma once
#include "BaseState.h"
#include "Resources.h"
#include "Battle.h"

class TakeDamageState : public BaseState
{
public:
	TakeDamageState(Stack<BaseState>& states, std::shared_ptr<Battle> battle,
					std::shared_ptr<Pokemon> attacker,
					std::shared_ptr<Pokemon> defender,
					WhosAttack id) : BaseState(states), m_battle(battle),
		m_attacker(attacker), m_defender(defender),
		m_id(id)

	{
		entry();
	}

	~TakeDamageState() =  default;
	 void entry() {
		  m_damage = m_battle->calculateDamage(*m_attacker, *m_defender);
		  m_startHPPercent = m_defender->getHpPercent();
		  m_defender->applyDamage(m_damage);
		  m_endHPPercent = m_defender->getHpPercent();
	 }
	 void exit() {
	 
	 
	 }
	 void update(sf::Time dt) {
	 
		 if (!m_guiUpdateCompleted)
		 {
			 m_elapsedTime += dt;

			 // Calculate the progress based on the elapsed time
			 float progress = m_elapsedTime.asSeconds() / m_hpUpdateDuration.asSeconds();

			 // Clamp the progress between 0 and 1
			 progress = std::max(0.0f, std::min(1.0f, progress));

			 // Calculate the current HP percentage based on the progress
			 float currentHPPercent = (1 - progress) * m_startHPPercent + progress * m_endHPPercent;
			
			 // Set the current HP progress
			 if (m_id == WhosAttack::Enemy)
			 {
				 m_battle->setPlayerHealthProgress(currentHPPercent);
			 }
			 else
			 {
				 m_battle->setEnemyHealthProgress(currentHPPercent);
			 }
			
			 // If progress is complete, set m_guiUpdateCompleted to true
			 if (progress >= 1.0f)
			 {
				 if (m_id == WhosAttack::Enemy)
				 {
					 m_battle->setPlayerHealthProgress(m_endHPPercent);
				 }
				 else
				 {
					 m_battle->setEnemyHealthProgress(m_endHPPercent);
				 }
				 m_guiUpdateCompleted = true;
			 }
		 }
		 else
		 {
			 setStatus(false);
		 }
	 }
	 void handleEvents(sf::Event event) {
	 
	 
	 }
	 void draw(sf::RenderWindow& window) {
		 std::cout << "takeDamage draw" << std::endl;
		 m_battle->draw(window);
	 
	 }
private:
	bool m_guiUpdateCompleted{false};
	int m_damage{ 0 };
	
	WhosAttack m_id;

	sf::Time m_elapsedTime;
	sf::Time m_hpUpdateDuration = sf::seconds(1.5f);

	
	float m_progress;
	float m_startHPPercent;
	float m_endHPPercent;

	std::shared_ptr<Battle> m_battle;

	std::shared_ptr<Pokemon> m_attacker;
	std::shared_ptr<Pokemon> m_defender;
};

