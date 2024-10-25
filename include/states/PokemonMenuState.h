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
    std::unique_ptr<Gui> textGui;
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
        if (!m_player)
        {
            std::cerr << "Error: Player is nullptr!" << std::endl;
            return;
        }

        const sf::Font& font = Resources::getInstance().getFont();

        // Determine the actual number of Pokémon to display
        size_t numPokemon = m_player->getPartySize();

        if (numPokemon == 0)
        {
            std::cerr << "Error: No Pokémon in the party!" << std::endl;
            return;
        }

        // Define padding and calculate container size
        float padding = 50.0f; // Adjust padding as needed
        sf::Vector2u windowSize = Resources::getInstance().getWindow().getSize();
        // Correct container size: window size minus padding on each side

        sf::Vector2f containerSize(windowSize.x - 2 * padding, windowSize.y - 2 * padding);
        sf::Vector2f containerPosition = m_cameraCenter - (containerSize / 2.0f);


        // Create container GUI
        m_containerGui = std::make_unique<Gui>(font, containerSize, containerPosition);
        m_containerGui->setText(""); // Clear any text if necessary

        // Define inner padding within container
        float innerPadding = 20.0f;

        // Calculate positions within the container
        float textWidth = containerSize.x * 0.3f; // 30% for text
        float spriteWidth = containerSize.x * 0.5f; // 50% for sprite and bars
        float textStartX = containerPosition.x + innerPadding; // Slight offset from left
        float textStartY = containerPosition.y - innerPadding;

        for (size_t i = 0; i < numPokemon; ++i)
        {
            auto pokemon = m_player->getPokemon(i); // Fetch Pokémon by index

            if (!pokemon)
            {
                std::cerr << "Error: Pokémon at index " << i << " is nullptr!" << std::endl;
                continue; // Skip to the next Pokémon
            }

            PokemonUI ui; // Instantiate inside the loop

            // ----------- Text GUI (Left Side) -----------
            sf::Vector2f textGuiSize(textWidth, containerSize.y / numPokemon - 2 * innerPadding); // Adjust height as needed
            sf::Vector2f textGuiPosition(textStartX, textStartY + i * (textGuiSize.y - innerPadding)); // Vertical stacking with spacing
            ui.mainGui = std::make_unique<Gui>(font, textGuiSize, textGuiPosition);

            // Set Text for the main GUI
            setText(ui.mainGui.get(), pokemon);

            // ----------- Sprite and Bars GUI (Right Side) -----------
            float spriteStartX = containerPosition.x + containerSize.x * 0.3f + innerPadding; // 30% + offset
            float spriteStartY = containerPosition.y + innerPadding + i * (containerSize.y / numPokemon);

            // Pokémon Sprite
            ui.frontSprite = pokemon->getFrontSprite();
            ui.frontSprite.setPosition(spriteStartX + spriteWidth / 2.0f, spriteStartY + 100.0f); // Center of the sprite area
            ui.frontSprite.setScale(2.0f, 2.0f); // Adjust scale as needed

            // Health Bar
            sf::Vector2f barSize(300.0f, 30.0f);
            sf::Vector2f lifeBarPosition(spriteStartX, spriteStartY + 200.0f);
            ui.lifeBar = std::make_unique<Gui>(font, barSize, lifeBarPosition);
            ui.lifeBar->addProgressBar(
                lifeBarPosition.x - 10.0f,
                lifeBarPosition.y - 10.0f,
                barSize.x,
                barSize.y,
                sf::Color::Black,
                sf::Color::Green,
                pokemon->getHpPercent());
            
            // Experience Bar
            sf::Vector2f expBarPosition(spriteStartX, lifeBarPosition.y + 50.0f);
            ui.expBar = std::make_unique<Gui>(font, barSize, expBarPosition);
            ui.expBar->addProgressBar(
                expBarPosition.x - 10.0f,
                expBarPosition.y - 10.0f,
                barSize.x,
                barSize.y,
                sf::Color::Black,
                sf::Color::Blue,
                pokemon->getCurrentExpPercent());
           

            // Add to the vector
            m_pokemonUIs.emplace_back(std::move(ui));
        }
    }


    void setText(Gui* gui, const std::shared_ptr<Pokemon>& pokemon)
    {
        gui->setResetColor();
        std::ostringstream textStream;

        textStream << "Name: " << (pokemon->getPokemonName()) << "\n";
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
        // Draw the container GUI first to act as a background
        if (m_containerGui)
        {
            m_containerGui->draw(window);
        }

        // Draw each Pokémon's UI elements
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
    std::unique_ptr<Gui> m_containerGui;
    // Other member variables as needed
};
