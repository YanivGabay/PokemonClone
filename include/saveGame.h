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

#include "Pokemon\Party.h"
#include "Level.h"
#include "entity\NPC.h"


using json = nlohmann::json;
namespace fs = std::filesystem;

class saveGame
{
public:
    saveGame()
        : m_directoryPath(".\\savingFiles"),
          m_fileName("1")
    {
        if (!fs::exists(m_directoryPath) &&
            !fs::is_directory(m_directoryPath))
        {
            fs::create_directory(m_directoryPath);
        }
    }

	~saveGame() = default;

	void updatePlayer(int playerPosX, int playerPosY, enum LevelID levelId, int encounterRate, float cameraCenterX, float cameraCenterY)
    {
        m_savingBuf["player"]["position"]["x"] = playerPosX;
        m_savingBuf["player"]["position"]["y"] = playerPosY;

        m_savingBuf["player"]["EncounterRate"] = encounterRate;

        m_savingBuf["player"]["camera"]["x"] = cameraCenterX;
        m_savingBuf["player"]["camera"]["y"] = cameraCenterY;
    }

    void updateParty(int partySize)
    {
        m_savingBuf["Party"]["Size"] = partySize;
    }
    void updateParty (Pokemon partyPokemon)
    {
        m_savingBuf["Party"][partyPokemon.getPokemonName()]["getAttack"] = partyPokemon.getAttack();
        m_savingBuf["Party"][partyPokemon.getPokemonName()]["getAttackIV"] = partyPokemon.getAttackIV();
        m_savingBuf["Party"][partyPokemon.getPokemonName()]["getBaseAttack"] = partyPokemon.getBaseAttack();
        m_savingBuf["Party"][partyPokemon.getPokemonName()]["getBaseDefense"] = partyPokemon.getBaseDefense();
        m_savingBuf["Party"][partyPokemon.getPokemonName()]["getBaseHP"] = partyPokemon.getBaseHP();
        m_savingBuf["Party"][partyPokemon.getPokemonName()]["getBaseSpeed"] = partyPokemon.getBaseSpeed();
        m_savingBuf["Party"][partyPokemon.getPokemonName()]["getCurrentExp"] = partyPokemon.getCurrentExp();
        m_savingBuf["Party"][partyPokemon.getPokemonName()]["getCurrentHP"] = partyPokemon.getCurrentHP();
        m_savingBuf["Party"][partyPokemon.getPokemonName()]["getDefense"] = partyPokemon.getDefense();
        m_savingBuf["Party"][partyPokemon.getPokemonName()]["getDefenseIV"] = partyPokemon.getDefenseIV();
        m_savingBuf["Party"][partyPokemon.getPokemonName()]["getExpToLevel"] = partyPokemon.getExpToLevel();
        m_savingBuf["Party"][partyPokemon.getPokemonName()]["getHP"] = partyPokemon.getHP();
        m_savingBuf["Party"][partyPokemon.getPokemonName()]["getHpPercent"] = partyPokemon.getHpPercent();
        m_savingBuf["Party"][partyPokemon.getPokemonName()]["getLevel"] = partyPokemon.getLevel();
        m_savingBuf["Party"][partyPokemon.getPokemonName()]["getName"] = partyPokemon.getName();
        m_savingBuf["Party"][partyPokemon.getPokemonName()]["getSpeed"] = partyPokemon.getSpeed();
        m_savingBuf["Party"][partyPokemon.getPokemonName()]["getSpeedIV"] = partyPokemon.getSpeedIV();
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

    void loadingFromFile(std::string inFileName)
    {
        m_fileName = inFileName;
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
            
            openingJsonFile.close();
        }
    }

private:
	json m_savingBuf;
    std::string m_directoryPath,
                m_fileName;
};
