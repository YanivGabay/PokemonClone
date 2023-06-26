#pragma once

#include <nlohmann/json.hpp>

#include <ctime>
#include <sstream>
#include <string>

#include <filesystem>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <ctime>
#include <iterator>
#include <locale>
#include "states/BaseState.h"
#include "Pokemon\Party.h"
#include "Level.h"
#include "entity\NPC.h"
#include "Utilities\PokemonIndex.h"


class PlayState;
using json = nlohmann::json;
namespace fs = std::filesystem;

class saveManager
{
public:
    saveManager()
        : m_directoryPath(".\\savingFiles"),
          m_fileName("saveedGame")
    {
        if (!fs::exists(m_directoryPath) &&
            !fs::is_directory(m_directoryPath))
        {
            fs::create_directory(m_directoryPath);
        }
    }

	~saveManager() = default;

	void updatePlayer(int playerPosX, int playerPosY,
                      enum LevelID levelId, int encounterRate,
                      float cameraCenterX, float cameraCenterY,
                      int NpcPosX, int NpcPosY)
    {
        m_savingBuf["playState"]["Playerposition"]["x"] = playerPosX;
        m_savingBuf["playState"]["Playerposition"]["y"] = playerPosY;

        m_savingBuf["playState"]["levelId"] = levelId;
        m_savingBuf["playState"]["EncounterRate"] = encounterRate;

        m_savingBuf["playState"]["cameraPosition"]["x"] = cameraCenterX;
        m_savingBuf["playState"]["cameraPosition"]["y"] = cameraCenterY;

        m_savingBuf["playState"]["NpcPosition"]["x"] = NpcPosX;
        m_savingBuf["playState"]["NpcPosition"]["y"] = NpcPosY;
    }

    void updateParty(int partySize)
    {
        m_savingBuf["Party"]["Size"] = partySize;
    }
    void updateParty (std::shared_ptr<Pokemon> partyPokemon)
    {
        int currPokemon = static_cast<int>(partyPokemon->getName());
        m_savingBuf["Party"][currPokemon]["getAttack"] = partyPokemon->getAttack();
        
        m_savingBuf["Party"][currPokemon]["getAttackIV"] = partyPokemon->getAttackIV();
        
        m_savingBuf["Party"][currPokemon]["getBaseAttack"] = partyPokemon->getBaseAttack();
        
        m_savingBuf["Party"][currPokemon]["getBaseDefense"] = partyPokemon->getBaseDefense();
        
        m_savingBuf["Party"][currPokemon]["getBaseHP"] = partyPokemon->getBaseHP();
        
        m_savingBuf["Party"][currPokemon]["getBaseSpeed"] = partyPokemon->getBaseSpeed();
        
        m_savingBuf["Party"][currPokemon]["getCurrentExp"] = partyPokemon->getCurrentExp();
        
        m_savingBuf["Party"][currPokemon]["getCurrentHP"] = partyPokemon->getCurrentHP();
        
        m_savingBuf["Party"][currPokemon]["getDefense"] = partyPokemon->getDefense();
        
        m_savingBuf["Party"][currPokemon]["getDefenseIV"] = partyPokemon->getDefenseIV();
        
        m_savingBuf["Party"][currPokemon]["getExpToLevel"] = partyPokemon->getExpToLevel();
        
        m_savingBuf["Party"][currPokemon]["getHP"] = partyPokemon->getHP();
        
        m_savingBuf["Party"][currPokemon]["getHpPercent"] = partyPokemon->getHpPercent();
        
        m_savingBuf["Party"][currPokemon]["getLevel"] = partyPokemon->getLevel();
        
        m_savingBuf["Party"][currPokemon]["getName"] = partyPokemon->getName();
        
        m_savingBuf["Party"][currPokemon]["getSpeed"] = partyPokemon->getSpeed();
        
        m_savingBuf["Party"][currPokemon]["getSpeedIV"] = partyPokemon->getSpeedIV();

        m_savingBuf["Party"][currPokemon]["getHPIV"] = partyPokemon->getHPIV();
    }

    void savingIntoFile()
    {
        // Specify the file name
        std::string fileName = m_directoryPath + "\\";
        fileName += m_fileName + ".json";

        // Open the file for writing
        std::fstream savingJsonFile;

        // Check if the file opened successfully
        savingJsonFile.open(fileName, std::ios::out);
        if (savingJsonFile)
        {
            // Save the JSON object to the file
            savingJsonFile << m_savingBuf.dump(4); // Use indentation of 4 spaces

            // Close the file
            savingJsonFile.close();
        }
    }

    std::unique_ptr<PlayState> loadingFromFile(Stack<BaseState>& states)
    {
        // Specify the file name
        std::string fileName = m_directoryPath + "\\" + m_fileName;

        // Open the file for reading
        std::fstream openingJsonFile;

        // Check if the file opened successfully
        openingJsonFile.open(fileName, std::ios::in);
        if (openingJsonFile)
        {
            // Read the contents of the file into a string
            std::string fileContents((std::istreambuf_iterator<char>(openingJsonFile)), std::istreambuf_iterator<char>());

            // Parse the string as a JSON object
            m_savingBuf = json::parse(fileContents);

            // Access values from the JSON object
            // std::string name = m_savingBuf["name"];
            // int age = m_savingBuf["age"];
            // std::string city = m_savingBuf["city"];

            std::unique_ptr<Level> currentLevel(std::make_unique<Level>());
            currentLevel->setEncounterRate(m_savingBuf["playState"]["EncounterRate"]);
            currentLevel->setLevelId(m_savingBuf["playState"]["levelId"]);
            
            std::unique_ptr<Party> pokemons(std::make_unique<Party>());
            for (size_t i = 0; i < m_savingBuf["Party"]["Size"]; ++i)
            {
                int currPokemon = static_cast<int>(i);
                
                pokemons->addPokemon( std::make_unique<Pokemon> (m_savingBuf["Party"][currPokemon]["getName"],
                    m_savingBuf["Party"][currPokemon]["getBaseHP"],
                    m_savingBuf["Party"][currPokemon]["getBaseAttack"],
                    m_savingBuf["Party"][currPokemon]["getBaseDefense"],
                    m_savingBuf["Party"][currPokemon]["getBaseSpeed"],
                    m_savingBuf["Party"][currPokemon]["getHPIV"],
                    m_savingBuf["Party"][currPokemon]["getAttackIV"],
                    m_savingBuf["Party"][currPokemon]["getDefenseIV"],
                    m_savingBuf["Party"][currPokemon]["getSpeedIV"],
                    m_savingBuf["Party"][currPokemon]["getHP"],
                    m_savingBuf["Party"][currPokemon]["getAttack"],
                    m_savingBuf["Party"][currPokemon]["getDefense"],
                    m_savingBuf["Party"][currPokemon]["getSpeed"],
                    m_savingBuf["Party"][currPokemon]["getLevel"],
                    m_savingBuf["Party"][currPokemon]["getCurrentExp"],
                    m_savingBuf["Party"][currPokemon]["getExpToLevel"],
                    m_savingBuf["Party"][currPokemon]["getCurrentHP"]));
            }
            
            std::shared_ptr<Player> player(std::make_shared<Player>(pokemons));
            
            player->setPosition(sf::Vector2i(m_savingBuf["playState"]["Playerposition"]["x"],
                m_savingBuf["playState"]["Playerposition"]["y"]));

            std::shared_ptr<NPC> NPC(std::make_shared<NPC>(m_savingBuf["playState"]["NpcPosition"]["x"], m_savingBuf["playState"]["NpcPosition"]["y"]));

            std::unique_ptr<Camera> camera(std::make_unique<Camera>(m_savingBuf["playState"]["cameraPosition"]["x"],
                m_savingBuf["playState"]["cameraPosition"]["y"]));
            
            openingJsonFile.close();

            std::unique_ptr<PlayState> loadPlayState = std::make_unique<PlayState>(states, currentLevel, player, NPC, camera);

            return loadPlayState;
        }
        
        return std::unique_ptr<PlayState>(std::make_unique<PlayState>(states));
    }

private:
	json m_savingBuf;
    std::string m_directoryPath,
                m_fileName;
};
