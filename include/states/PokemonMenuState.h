#pragma once
#include "BaseState.h"
#include "Resources.h"
#include "entity/Player.h"
#include "guis/Gui.h"
class PokemonMenuState :public BaseState
{
public:
	PokemonMenuState(Stack<BaseState>& states,std::shared_ptr<Player> player,sf::Vector2f cameraCenter) : BaseState(states),
		m_player(player),m_cameraCenter(cameraCenter)
	{ }
	~PokemonMenuState() {};

	 void entry() {
		 sf::Vector2f buttonSize = sf::Vector2f(m_windowSize.x, m_windowSize.y);
		 // float x = (static_cast<float>(m_cameraCenter.x ) - (buttonSize.x / 2));
		 sf::Font& font = Resources::getInstance().getFont();
		 m_main = std::move(std::make_unique<Gui>(font, buttonSize,
																  sf::Vector2f(m_cameraCenter.x - m_windowSize.x / 2 , m_cameraCenter.y - m_windowSize.y / 2 )));
		 buttonSize = sf::Vector2f(300, 50);
		 /*m_playerPokemonInfo->addProgressBar(m_playerPokemonInfo->getPosition().x,
											 m_playerPokemonInfo->getPosition().y + 40, m_playerPokemonInfo->getSize().x / 3, m_playerPokemonInfo->getSize().y / 6,
											 sf::Color::Black, sf::Color::Green, m_currentPlayerPokemon->getHpPercent());*/
		 m_life = std::move(std::make_unique<Gui>(font, buttonSize,
												  sf::Vector2f(m_cameraCenter.x, m_cameraCenter.y - m_windowSize.y / 2)));
		 m_life->addProgressBar(m_life->getPosition().x, m_life->getPosition().y, buttonSize.x, buttonSize.y, sf::Color::Black,
								sf::Color::Green,m_player->getStarterPokemon()->getHpPercent());
		 m_exp = std::move(std::make_unique<Gui>(font, buttonSize,
												  sf::Vector2f(m_cameraCenter.x, m_cameraCenter.y - m_windowSize.y / 2+100)));
		 m_exp->addProgressBar(m_exp->getPosition().x, m_exp->getPosition().y, buttonSize.x, buttonSize.y, sf::Color::Black,
								sf::Color::Blue, m_player->getStarterPokemon()->getCurrentExpPercent());
		 setText();
	 }
	 void setText()
	 {
		 m_main->setResetColor();
		 std::ostringstream textStream;

		
		 // { HPIncrease, attackIncrease, defenseIncrease, speedIncrease };
		 textStream << "Level:" << m_player->getStarterPokemon()->getLevel() << "\n";
		 textStream << "Current Hp:" << m_player->getStarterPokemon()->getCurrentHP() << "\n";
		 textStream << "Hp:" << m_player->getStarterPokemon()->getHP() << "\n";
		 textStream << "Attack:" << m_player->getStarterPokemon()->getAttack() << "\n";
		 textStream << "Defense:" << m_player->getStarterPokemon()->getDefense() << "\n";
		 textStream << "Speed:" << m_player->getStarterPokemon()->getSpeed() << "\n";
		 textStream << "Exp for next level:" << m_player->getStarterPokemon()->getExpToLevel()-m_player->getStarterPokemon()->getCurrentExp() << "\n";
		 textStream << "Speed:" << m_player->getStarterPokemon()->getSpeed() << "\n";
		 m_main->setText(textStream.str());
	 }
	 void exit() {
	 
	 
	 }
	 void update(sf::Time dt) {
	 
	 
	 }
	 void handleEvents(sf::Event event) {
	 
	 
	 }
	 void draw(sf::RenderWindow& window) {
	 
	 
	 }
private:
	std::shared_ptr<Player> m_player;

	sf::Vector2f m_cameraCenter;
	std::unique_ptr<Gui> m_main;
	std::unique_ptr<Gui> m_life;
	std::unique_ptr<Gui> m_exp;
	sf::Vector2i m_windowSize{ Resources::getInstance().getWindow().getSize() };
};

