# MiniMons - Pokémon Clone

## Overview

This project is our final project for the Object-Oriented Programming (OOP) course. We've created a Pokémon clone where players embark on a journey to defeat the Green Nightmare, a powerful Pokémon located on the fourth map. Players choose their starter Pokémon and train them to prepare for this ultimate challenge.

## Team

- Yaniv Gabay - ID: 205745615
- Shahar Asher - ID: 209305408

## Project Description
This is our attemp of creating a pokemon game engine. we can go through 4 different maps, battle different pokemons, 
level up our own starter.
We've integrated the Tiled application into our workflow. Tiled allows us to design and create maps with ease.
Once the maps are created, we use the [Tileson API](https://github.com/SSBMTonberry/Tileson) to process the output and seamlessly integrate it into our game engine.

## Installation

### Prerequisites

- Git: Ensure you have Git installed. You can download it from [here](https://git-scm.com/)
- Visual Studio or Visual Studio Code: Install one of these IDEs (Visual Studio is recommended for CMake projects
- SFML 2.5.1 Download and extract SFML from https://www.sfml-dev.org/download.php.
    - Extract to:
    ```bash 
    C:\SFML\SFML-2.5.1
    ```


### **Setup and Build Instructions**

1. **Clone the Repository:**

   Open a terminal or Git Bash and run:

   ```bash
    https://github.com/YanivGabay/PokemonClone
   ```

2. **Open the Project in Visual Studio or VSCode:**

   - For **Visual Studio**:
     - Open Visual Studio and select **"Open a Local Folder"**.
     - Choose the cloned repository folder.

   - For **VSCode**:
     - Open VSCode and select **"Open Folder"**.
     - Choose the cloned repository folder.

3. **Ensure SFML is Installed Correctly:**
   - Make sure that SFML is located at:  
     ```
     C:\SFML\SFML-2.5.1
     ```

4. **Build the Project:**
   - Open the project in Visual Studio.
   - Click on **CMake -> Build All** to compile the project.

5. **Running the Game:**
   - After building, the executable will be available. Run it directly from Visual Studio.

---

### List of Files Created

#### Entity

- **Entity.h**: Base class.
- **Player.h**: Derived class representing the player.

#### GUIs

- **Button.h**: GUI element representing a button.
- **Gui.h**: Base GUI object with support for adding progress bars.
- **ProgressBar.h**: Progress bar GUI element.

#### Pokémon

- **Party.h**: Represents a party of Pokémon.
- **Pokemon.h**: Class representing individual Pokémon with base stats, IVs, and current stats.
- **PokemonFactory.h**: Factory for creating Pokémon instances.

#### States

- **AddExpState.h**: Handles experience gain and level up.
- **BaseState.h**: Base class for all states.
- **ChoosePokemon.h**: Initial state for choosing the starter Pokémon.
- **EncounterBattle.h**: State triggered when encountering wild Pokémon.
- **FadeinState.h**: Fades into a color.
- **FadeOutState.h**: Fades out into a texture or state.
- **GuideState.h**: Provides basic guidelines at the beginning of the game.
- **PlayerMenuState.h**: State triggered by the "M" key to access player menu options.
- **PlayState.h**: Main gameplay state where players explore the world.
- **PokemonMenuState.h**: Menu for viewing Pokémon information.
- **StartMenuState.h**: Initial menu state with game options.
- **StartState.h**: Initial state for choosing game options.
- **TakeDamageState.h**: Handles damage calculation.
- **TakeTurnState.h**: Handles turn-based actions.
- **TransitionState.h**: Manages transitions between states.

#### Utilities

- **Fades.h**: Utility functions for fades.
- **PokemonIndex.h**: Enums and hashmaps for Pokémon sprites.
- **StartMenuOptions.h**: Operators for easier readability.

#### World

- **TilesMap.h**: Represents the tile map parsed from Tiled application JSON files.

#### General

- **Animation.h**: Template class for animations.
- **Battle.h**: Structure for battles including positions and sprites.
- **Camera.h**: Controls the view.
- **Game.h**: Main game loop.
- **Level.h**: Represents a level with a vector of tile maps.
- **Resources.h**: Singleton class for managing textures, rects, fonts, etc.
- **SaveManager.h**: Helps with saving and loading the game.
- **SoundTon.h**: Singleton class for sound manipulation.
- **Stack.h**: Template class acting as a state stack.
- **StateMachine.h**: Manages the game using a state stack.
- **Tile.h**: Represents a tile with optional animation.
- **utilities.h**: General utility functions.
- **main.cpp**: Entry point of the application.

### Main Data Structures

- **Stack**: Vector of states managed as a stack.
- **nlohmann JSON API**: Used for saving and loading game data.
- **Tileson API**: Parses JSON files exported from Tiled application for maps.
- **6 Hashmaps in Resources**: Control textures, rects, sprites, etc.
- **Hashmaps inside Tilemap**: Improve performance when checking for specific tiles.
- **std::array**: Used for fixed-size structures.

## Design

- Inspired by CS50 game development course.
- Maps designed using Tiled application.
- Spritesheets collected from various sources and edited.
- Tileson API used for parsing map files and converting them into game objects.
- Easily extensible to add more states and functionalities.
- GUI class used extensively for various UI elements.
- Sounds used as indicators for player actions.
- Planned features not implemented due to time constraints:
  - NPC interaction using OpenAI API.
  - Pokémon catching system.
  - Interactions with objects other than tall grass.
  - Gym, shop, and Pokémon Center functionalities.
  - Additional Pokémon attacks.
  - NPC trainers.

## Known Bugs

- Character sometimes moves one extra space after battle.
- Resizing issues with certain menus when changing window size.
- Imperfections in fade-in and fade-out effects.

## Other Comments

Thank you for taking the time to read our README! 😊👍
