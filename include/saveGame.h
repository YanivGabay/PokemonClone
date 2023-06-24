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


using json = nlohmann::json;
namespace fs = std::filesystem;

class saveGame
{
public:
    saveGame()
        : m_directoryPath("C:\\savingFiles"),
          m_fileName("1")
    {
        if (!fs::exists(m_directoryPath) &&
            !fs::is_directory(m_directoryPath))
        {
            fs::create_directory(m_directoryPath);
        }
    }

	~saveGame() = default;

	void updateValues()
	{
		m_savingBuf["name"] = "John Doe";
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
