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
//#include <>

#include "Pokemon\Party.h"
#include "Level.h"
#include "entity\NPC.h"
#include "Utilities\PokemonIndex.h"
#include "states\BaseState.h"

class PlayState;
using json = nlohmann::json;
namespace fs = std::filesystem;

class saveManager
{
public:
    saveManager()
        : m_directoryPath(".\\savingFiles"),
          m_fileName("savedGame")
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
                      float cameraX, float cameraY,
                      int NpcPosX, int NpcPosY)
    {
        m_savingBuf["playState"]["Playerposition"]["x"] = playerPosX;
        m_savingBuf["playState"]["Playerposition"]["y"] = playerPosY;

        m_savingBuf["playState"]["levelId"] = levelId;
        m_savingBuf["playState"]["EncounterRate"] = encounterRate;

        m_savingBuf["playState"]["cameraPosition"]["x"] = cameraX;
        m_savingBuf["playState"]["cameraPosition"]["y"] = cameraY;

        m_savingBuf["playState"]["NpcPosition"]["x"] = NpcPosX;
        m_savingBuf["playState"]["NpcPosition"]["y"] = NpcPosY;
    }

    void updateParty(int partySize)
    {
        m_savingBuf["Party"]["Size"] = partySize;
        m_savingBuf["Party"]["RealSize"] = -1;
        // m_savingBuf["Party"]["ReallSize"] = 0;
    }
    void updateParty (std::shared_ptr<Pokemon> partyPokemon,const int index)
    {
        m_savingBuf["Party"]["RealSize"] = index;
        std::string StrCurrPokemon = std::to_string(static_cast<int>(index));
        m_savingBuf["Party"][StrCurrPokemon]["getAttack"] = partyPokemon->getAttack();
        
        m_savingBuf["Party"][StrCurrPokemon]["getAttackIV"] = partyPokemon->getAttackIV();
        
        m_savingBuf["Party"][StrCurrPokemon]["getBaseAttack"] = partyPokemon->getBaseAttack();
        
        m_savingBuf["Party"][StrCurrPokemon]["getBaseDefense"] = partyPokemon->getBaseDefense();
        
        m_savingBuf["Party"][StrCurrPokemon]["getBaseHP"] = partyPokemon->getBaseHP();
        
        m_savingBuf["Party"][StrCurrPokemon]["getBaseSpeed"] = partyPokemon->getBaseSpeed();
        
        m_savingBuf["Party"][StrCurrPokemon]["getCurrentExp"] = partyPokemon->getCurrentExp();
        
        m_savingBuf["Party"][StrCurrPokemon]["getCurrentHP"] = partyPokemon->getCurrentHP();
        
        m_savingBuf["Party"][StrCurrPokemon]["getDefense"] = partyPokemon->getDefense();
        
        m_savingBuf["Party"][StrCurrPokemon]["getDefenseIV"] = partyPokemon->getDefenseIV();
        
        m_savingBuf["Party"][StrCurrPokemon]["getExpToLevel"] = partyPokemon->getExpToLevel();
        
        m_savingBuf["Party"][StrCurrPokemon]["getHP"] = partyPokemon->getHP();
        
        m_savingBuf["Party"][StrCurrPokemon]["getHpPercent"] = partyPokemon->getHpPercent();
        
        m_savingBuf["Party"][StrCurrPokemon]["getLevel"] = partyPokemon->getLevel();
        
        m_savingBuf["Party"][StrCurrPokemon]["getName"] = partyPokemon->getName();
        
        m_savingBuf["Party"][StrCurrPokemon]["getSpeed"] = partyPokemon->getSpeed();
        
        m_savingBuf["Party"][StrCurrPokemon]["getSpeedIV"] = partyPokemon->getSpeedIV();

        m_savingBuf["Party"][StrCurrPokemon]["getHPIV"] = partyPokemon->getHPIV();
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
        std::string fileName = m_directoryPath + "\\";
        fileName += m_fileName + ".json";

        // Open the file for reading
        std::fstream openingJsonFile;
        std::cout << "111" << std::endl;
        // Check if the file opened successfully
        openingJsonFile.open(fileName, std::ios::in);
        std::cout << "222" << std::endl;
        if (openingJsonFile)
        {
            std::cout << "333" << std::endl;
            // Read the contents of the file into a string
            std::string fileContents((std::istreambuf_iterator<char>(openingJsonFile)), std::istreambuf_iterator<char>());

            // Parse the string as a JSON object
            m_savingBuf = json::parse(fileContents);
            std::cout << m_savingBuf << std::endl;
            // Access values from the JSON object
            // std::string name = m_savingBuf["name"];
            // int age = m_savingBuf["age"];
            // std::string city = m_savingBuf["city"];

            std::unique_ptr<Level> currentLevel(std::make_unique<Level>());
            std::cout << "444" << std::endl;
            currentLevel->setEncounterRate(m_savingBuf["playState"]["EncounterRate"]);
            currentLevel->setLevelId(m_savingBuf["playState"]["levelId"]);
            
            std::cout << "555" << std::endl;
            std::unique_ptr<Party> pokemons(std::make_unique<Party>());
            std::cout << "666" << std::endl;
            for (size_t i = 0; i <= m_savingBuf["Party"]["RealSize"]; ++i)
            {
                std::cout << "########" << std::endl;
                std::string StrCurrPokemon = std::to_string(static_cast<int>(i));
                std::cout << "========" << std::endl;
                std::cout << "i" << std::endl;
                /*
                std::cout << m_savingBuf.at("Party").at(StrCurrPokemon).at("getName") << std::endl;
                std::cout << m_savingBuf.at("Party").at(StrCurrPokemon).at("getBaseHP") << std::endl;
                std::cout << m_savingBuf.at("Party").at(StrCurrPokemon).at("getBaseAttack") << std::endl;
                std::cout << m_savingBuf.at("Party").at(StrCurrPokemon).at("getBaseDefense") << std::endl;
                std::cout << m_savingBuf.at("Party").at(StrCurrPokemon).at("getBaseSpeed") << std::endl;
                std::cout << m_savingBuf.at("Party").at(StrCurrPokemon).at("getHPIV") << std::endl;
                std::cout << m_savingBuf.at("Party").at(StrCurrPokemon).at("getAttackIV") << std::endl;
                std::cout << m_savingBuf.at("Party").at(StrCurrPokemon).at("getDefenseIV") << std::endl;
                std::cout << m_savingBuf.at("Party").at(StrCurrPokemon).at("getSpeedIV") << std::endl;
                std::cout << m_savingBuf.at("Party").at(StrCurrPokemon).at("getHP") << std::endl;
                std::cout << m_savingBuf.at("Party").at(StrCurrPokemon).at("getAttack") << std::endl;
                std::cout << m_savingBuf.at("Party").at(StrCurrPokemon).at("getDefense") << std::endl;
                std::cout << m_savingBuf.at("Party").at(StrCurrPokemon).at("getSpeed") << std::endl;
                std::cout << m_savingBuf.at("Party").at(StrCurrPokemon).at("getLevel") << std::endl;
                std::cout << m_savingBuf.at("Party").at(StrCurrPokemon).at("getCurrentExp") << std::endl;
                std::cout << m_savingBuf.at("Party").at(StrCurrPokemon).at("getExpToLevel") << std::endl;
                std::cout << m_savingBuf.at("Party").at(StrCurrPokemon).at("getCurrentHP") << std::endl;
                */
                pokemons->addPokemon(std::make_shared<Pokemon> (
                    static_cast<PokemonIndex>(m_savingBuf.at("Party").at(StrCurrPokemon).at("getName")),
                    m_savingBuf.at("Party").at(StrCurrPokemon).at("getBaseHP"),
                    m_savingBuf.at("Party").at(StrCurrPokemon).at("getBaseAttack"),
                    m_savingBuf.at("Party").at(StrCurrPokemon).at("getBaseDefense"),
                    m_savingBuf.at("Party").at(StrCurrPokemon).at("getBaseSpeed"),
                    m_savingBuf.at("Party").at(StrCurrPokemon).at("getHPIV"),
                    m_savingBuf.at("Party").at(StrCurrPokemon).at("getAttackIV"),
                    m_savingBuf.at("Party").at(StrCurrPokemon).at("getDefenseIV"),
                    m_savingBuf.at("Party").at(StrCurrPokemon).at("getSpeedIV"),
                    m_savingBuf.at("Party").at(StrCurrPokemon).at("getHP"),
                    m_savingBuf.at("Party").at(StrCurrPokemon).at("getAttack"),
                    m_savingBuf.at("Party").at(StrCurrPokemon).at("getDefense"),
                    m_savingBuf.at("Party").at(StrCurrPokemon).at("getSpeed"),
                    m_savingBuf.at("Party").at(StrCurrPokemon).at("getLevel"),
                    m_savingBuf.at("Party").at(StrCurrPokemon).at("getCurrentExp"),
                    m_savingBuf.at("Party").at(StrCurrPokemon).at("getExpToLevel"),
                    m_savingBuf.at("Party").at(StrCurrPokemon).at("getCurrentHP")));
                std::cout << "777" << std::endl;
            }
            std::cout << "888" << std::endl;
            std::shared_ptr<Player> player(std::make_shared<Player>(std::move(pokemons)));
            std::cout << "999" << std::endl;
            player->setPositions(sf::Vector2i(m_savingBuf["playState"]["Playerposition"]["x"],
                m_savingBuf["playState"]["Playerposition"]["y"]));

            std::shared_ptr<NPC> NPC(std::make_shared<NPC>());
            NPC->setPosition(sf::Vector2i(m_savingBuf["playState"]["NpcPosition"]["x"], m_savingBuf["playState"]["NpcPosition"]["y"]));
            std::cout << "101010" << std::endl;
            std::unique_ptr<Camera> camera(std::make_unique<Camera>(m_savingBuf["playState"]["cameraPosition"]["x"],
                m_savingBuf["playState"]["cameraPosition"]["y"]));

            std::cout << "x = " << m_savingBuf["playState"]["cameraPosition"]["x"] << " y = " << m_savingBuf["playState"]["cameraPosition"]["y"] << std::endl;
            std::cout << "111111111" << std::endl;
            openingJsonFile.close();
            std::cout << "12121212" << std::endl;
            return std::unique_ptr<PlayState>((std::make_unique<PlayState>(states, std::move(currentLevel), player, NPC, std::move(camera))));
        }
        
        return std::unique_ptr<PlayState>((std::make_unique<PlayState>(states)));
    }

private:
	json m_savingBuf;
    std::string m_directoryPath,
                m_fileName;
};
