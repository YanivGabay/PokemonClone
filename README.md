
# MiniMons - Pokémon Clone

## Overview

**MiniMons** is a Pokémon-inspired game developed as the final project for our Object-Oriented Programming (OOP) course. Players embark on a journey to train their starter Pokémon and ultimately face the powerful Green Nightmare on the fourth map. Through exploration, battles, and leveling up, players prepare to take on this ultimate challenge.

## Team

- **Yaniv Gabay** - ID: 205745615
- **Shahar Asher** - ID: 209305408

---

## Project Description

MiniMons is a Pokémon-style game engine designed to offer classic monster-battling gameplay. Players can explore four unique maps, encounter wild Pokémon, level up their own, and test their strategies in battles. Maps are crafted with the [Tiled](https://www.mapeditor.org/) application and seamlessly integrated into our game using the [Tileson API](https://github.com/SSBMTonberry/Tileson).

### Features
- **Multiple Maps**: Traverse four maps with various wild Pokémon encounters.
- **Battle System**: Engage in turn-based battles and level up your Pokémon.
- **Dynamic Environments**: Animations, fades, and transitions create an immersive experience.

---

## Installation

### Prerequisites
- **Git**: Install from [here](https://git-scm.com/).
- **Visual Studio or Visual Studio Code**: Recommended for CMake projects.
- **SFML 2.5.1**: Download and extract from [SFML](https://www.sfml-dev.org/download.php).
  - Extract to:
    ```bash
    C:\SFML\SFML-2.5.1
    ```

### Setup and Build Instructions

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/YanivGabay/PokemonClone
   ```

2. **Open the Project**:
   - **Visual Studio**: Open the repository folder via "Open a Local Folder."
   - **VSCode**: Open the repository folder via "Open Folder."

3. **Confirm SFML Installation**:
   Ensure SFML is located at:
   ```bash
   C:\SFML\SFML-2.5.1
   ```

4. **Build the Project**:
   - In Visual Studio, select **CMake -> Build All** to compile.

5. **Run the Game**:
   After building, the executable will be available to run from Visual Studio.

---

## Project Structure

### Entity
- `Entity.h`: Base class for all entities.
- `Player.h`: Represents the player character.

### GUIs
- `Button.h`: Button elements.
- `Gui.h`: Base class for GUI components, with support for progress bars.
- `ProgressBar.h`: Displays progress bars.

### Pokémon
- `Party.h`: Represents a Pokémon party.
- `Pokemon.h`: Defines individual Pokémon with base stats, IVs, and current stats.
- `PokemonFactory.h`: Factory pattern for Pokémon creation.

### States
- `AddExpState.h`: Handles experience gain and leveling.
- `BaseState.h`: Base class for game states.
- `ChoosePokemon.h`: State for selecting a starter Pokémon.
- `EncounterBattle.h`: Manages wild Pokémon encounters.
- `GuideState.h`: Initial game guide for players.
- `PlayerMenuState.h`: Activated by pressing "M" for menu options.
- `PlayState.h`: Primary gameplay state.
- `PokemonMenuState.h`: Menu for viewing Pokémon details.
- `StartMenuState.h`: Main menu.
- `TakeDamageState.h`: Damage calculation.
- `TakeTurnState.h`: Manages turn-based actions.
- `TransitionState.h`: Handles state transitions.

### Utilities
- `Fades.h`: Functions for fade animations.
- `PokemonIndex.h`: Enum and hashmaps for Pokémon sprites.
- `StartMenuOptions.h`: Improves readability of operators.

### World
- `TilesMap.h`: Manages tile maps created with Tiled.

### General
- `Animation.h`: Animation templates.
- `Battle.h`: Battle configuration and sprite positions.
- `Camera.h`: Manages the in-game view.
- `Game.h`: Game loop and core mechanics.
- `SaveManager.h`: Manages save/load functionality.
- `SoundTon.h`: Singleton for audio.
- `Stack.h`: State stack template.
- `StateMachine.h`: Controls game state stack.
- `utilities.h`: General utilities.
- `main.cpp`: Application entry point.

---

## Main Data Structures

- **State Stack**: Manages states as a stack using `Stack`.
- **nlohmann JSON API**: Saves/loads game data.
- **Tileson API**: Parses JSON data from Tiled maps.
- **Resource Hashmaps**: Manages textures, sprites, etc., within `Resources`.
- **Tilemap Hashmaps**: Optimize tile lookups in `TilesMap`.
- **`std::array`**: Utilized for fixed-size structures.

## Design and Inspiration

Inspired by the CS50 game development course, MiniMons incorporates assets from various sources to create a visually engaging world. The Tileson API translates Tiled JSON data into in-game objects. The design is modular and extendable, making it easy to add new features.

Planned features (yet to be implemented):
- **NPC interaction** with OpenAI API.
- **Pokémon catching system**.
- **Object interaction** beyond tall grass.
- **Facilities** like Gyms, Shops, and Pokémon Centers.
- **Enhanced battle mechanics** with additional attacks and trainers.

---

## Known Bugs

- Character may move an extra space after battle.
- Resizing issues in menus when window size changes.
- Minor imperfections in fade-in and fade-out effects.

---

## Acknowledgements

Thank you for exploring MiniMons! We hope you enjoy it as much as we enjoyed creating it. 😊👍
