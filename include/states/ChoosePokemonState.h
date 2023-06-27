#pragma once
#include "BaseState.h"
#include "entity/Player.h"
#include "Pokemon/PokemonFactory.h"
#include "guis/Gui.h"
#include "Resources.h"
#include "FadeOutState.h"
const int SELECTION = 3;

class ChoosePokemonState : public BaseState
{ 
public:
	ChoosePokemonState(Stack<BaseState>& states,sf::Vector2f cameraCenter,std::shared_ptr<Player> player) : BaseState(states),
		m_cameraCenter(cameraCenter), m_player(player), m_starters{
			m_pokemonFactory.createPokemon(PokemonIndex::CHARIZARD),
			m_pokemonFactory.createPokemon(PokemonIndex::VENASUR),
			m_pokemonFactory.createPokemon(PokemonIndex::BLASTOISE)
		},m_prompt(std::move(std::make_unique<Gui>(Resources::getInstance().getFont(),sf::Vector2f(m_windowSize.x, m_windowSize.y),
												   sf::Vector2f(m_cameraCenter.x-m_windowSize.x/2,m_cameraCenter.y)
												  )))
	{
		
		int counter = 0;
		for (auto& pokemon : m_starters)
		{
			pokemon->getFrontSprite().setPosition(m_prompt->getPosition().x + 200 * counter+25, m_cameraCenter.y + 100);
			counter++;
		}
		m_prompt->setResetColor();
		m_prompt->setText("Choose Your Starter Pokemon! Use Arrows Keys to change, and Enter To choose");
	};

	~ChoosePokemonState() {};
	 void entry() {
	 
	 
	 }
	 void exit() {
	 
	 
	 }
	 void update(sf::Time dt) {
		 int hover = m_hover.value();

		 for (int i = 0; i < SELECTION; i++)
		 {
			 if (i == hover)
			 {
				 m_starters[i]->getFrontSprite().setScale(sf::Vector2f(1.5f, 1.5f));
			 }
			 else
			 {
				 m_starters[i]->getFrontSprite().setScale(sf::Vector2f(1.0f, 1.0f));
			 }
		 }
		 if (m_selection != std::nullopt)
		 {
			 m_starters[m_selection.value()]->getFrontSprite().setScale(sf::Vector2f(1.0f, 1.0f));
			 m_player->addPokemon(m_starters[m_selection.value()]);
			 auto state = (std::make_unique<FadeOutState>(getStateStack().get(), sf::Color::White, false));
			 getStateStack().get().pushQueueState(std::move(state));
			 setStatus(false);
		 }
	 
	 }
	 void handleEvents(sf::Event event) {
		 if (event.type == sf::Event::KeyReleased)
		 {
			 if (event.key.code == sf::Keyboard::Enter)
			 {
				 m_selection = m_hover;
			 }
			 if (event.key.code == sf::Keyboard::Down
				 || event.key.code == sf::Keyboard::Right)
			 {
				 m_hover = (m_hover.value() + 1) % 3;
			 }
			 if (event.key.code == sf::Keyboard::Up||
				 event.key.code == sf::Keyboard::Left)
			 {
				 m_hover = (m_hover.value() - 1 + 3) % 3;
			 }
			 			
		 }
	 
	 }
	 void draw(sf::RenderWindow& window) {
	 
		 m_prompt->draw(window);
		 for (auto& pokemon : m_starters)
		 {
			 window.draw(pokemon->getFrontSprite());
		 }
	 }
private:
	std::optional<int> m_selection{ std::nullopt };
	std::optional<int> m_hover {0};
	sf::Vector2i m_windowSize{ Resources::getInstance().getWindow().getSize() };
	PokemonFactory m_pokemonFactory;
	sf::Vector2f m_cameraCenter;
	std::array<std::shared_ptr<Pokemon>, SELECTION> m_starters;
	std::shared_ptr<Player> m_player;
	std::unique_ptr<Gui> m_prompt;
};
