#pragma once

#include "BaseState.h"
#include "Resources.h"
#include "entity/Player.h"
#include "guis/Gui.h"
#include <vector>
#include <memory>
#include <sstream>
#include <SFML/Graphics.hpp>

struct PokemonUI
{
    std::unique_ptr<Gui> mainGui;
    std::unique_ptr<Gui> lifeBar;
    std::unique_ptr<Gui> expBar;
    sf::Sprite frontSprite;
};

class PokemonMenuState : public BaseState
{
public:
    PokemonMenuState(Stack<BaseState>& states,
                     std::shared_ptr<Player> player,
                     sf::Vector2f cameraCenter)
        : BaseState(states),
        m_player(player),
        m_cameraCenter(cameraCenter)
    {
        // Stop current sounds and play the Pokémon menu theme
        SoundTon::getInstance().stopSound(soundNames::MENU_THEME);
        SoundTon::getInstance().playSound(soundNames::POKEMON);

        entry();
    }

    virtual ~PokemonMenuState()
    {
        // Restore menu theme when exiting the Pokémon menu
        SoundTon::getInstance().stopSound(soundNames::POKEMON);
        SoundTon::getInstance().playSound(soundNames::MENU_THEME);
    }

    void entry()
    {
        const sf::Font& font = Resources::getInstance().getFont();

        // Determine the number of Pokémon to display
        size_t numPokemon = m_player->getPartySize(); // Assume this function exists

        // Calculate spacing based on the number of Pokémon
        float startX = m_cameraCenter.x - (numPokemon * 400) / 2.0f; // Adjust 400 as needed
        float yPosition = m_cameraCenter.y - m_windowSize.y / 2.0f + 100.0f; // Starting Y position

        for (size_t i = 0; i < numPokemon; ++i)
        {
            auto pokemon = m_player->getPokemon(i); // Assume this function returns a pointer or reference to a Pokémon

            PokemonUI ui;

            // Main GUI (background or container)
            sf::Vector2f mainButtonSize(400, 200); // Adjust size as needed
            sf::Vector2f mainButtonPosition(startX + i * 400, yPosition);
            ui.mainGui = std::make_unique<Gui>(font, mainButtonSize, mainButtonPosition);

            // Health Bar
            sf::Vector2f barSize(300, 30);
            sf::Vector2f lifeBarPosition(mainButtonPosition.x + 50, mainButtonPosition.y + 150);
            ui.lifeBar = std::make_unique<Gui>(font, barSize, lifeBarPosition);
            ui.lifeBar->addProgressBar(
                lifeBarPosition.x - 10,
                lifeBarPosition.y - 10,
                barSize.x,
                barSize.y,
                sf::Color::Black,
                sf::Color::Green,
                pokemon->getHpPercent()
            );

            // Experience Bar
            sf::Vector2f expBarPosition(lifeBarPosition.x, lifeBarPosition.y + 50);
            ui.expBar = std::make_unique<Gui>(font, barSize, expBarPosition);
            ui.expBar->addProgressBar(
                expBarPosition.x - 10,
                expBarPosition.y - 10,
                barSize.x,
                barSize.y,
                sf::Color::Black,
                sf::Color::Blue,
                pokemon->getExpPercent()
            );

            // Set Text for the main GUI
            setText(ui.mainGui.get(), pokemon);

            // Pokémon Sprite
            ui.frontSprite = pokemon->getFrontSprite();
            ui.frontSprite.setPosition(mainButtonPosition.x + 200, mainButtonPosition.y + 100); // Center of the main GUI
            ui.frontSprite.setScale(2.0f, 2.0f);

            // Add to the vector
            m_pokemonUIs.emplace_back(std::move(ui));
        }
    }

    void setText(Gui* gui, const std::shared_ptr<Pokemon>& pokemon)
    {
        gui->setResetColor();
        std::ostringstream textStream;

        textStream << "Name: " << pokemon->getName() << "\n";
        textStream << "Level: " << pokemon->getLevel() << "\n";
        textStream << "Current HP: " << pokemon->getCurrentHP() << "\n";
        textStream << "Attack: " << pokemon->getAttack() << "\n";
        textStream << "Defense: " << pokemon->getDefense() << "\n";
        textStream << "Speed: " << pokemon->getSpeed() << "\n";
        textStream << "Exp for Next Level: " << pokemon->getExpToLevel() - pokemon->getCurrentExp() << "\n";
        textStream << "Current Exp: " << pokemon->getCurrentExp() << "\n";
        textStream << "\nPress M again to go back to the Menu\n";

        gui->setText(textStream.str());
    }

    void exit() {}

    void update(sf::Time dt) {}

    void handleEvents(sf::Event event)
    {
        if (event.type == sf::Event::KeyReleased)
        {
            if (event.key.code == sf::Keyboard::M ||
                event.key.code == sf::Keyboard::Escape)
            {
                SoundTon::getInstance().playSound(soundNames::CLICK);
                setStatus(false);
            }
        }
    }

    void draw(sf::RenderWindow& window)
    {
        for (auto& ui : m_pokemonUIs)
        {
            ui.mainGui->draw(window);
            ui.lifeBar->draw(window);
            ui.expBar->draw(window);
            window.draw(ui.frontSprite);
        }
    }

private:
    std::shared_ptr<Player> m_player;
    sf::Vector2f m_cameraCenter;
    std::vector<PokemonUI> m_pokemonUIs;
    sf::Vector2i m_windowSize{ Resources::getInstance().getWindow().getSize() };

    // Other member variables as needed
};
