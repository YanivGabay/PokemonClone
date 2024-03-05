https://www.youtube.com/watch?v=OIVr442yd1w

# oop - Project - Pokémon

# MiniMons

### Students:

> Yaniv Gabay - 205745615

> Shahar Asher - 209305408

### In General:
```
This is Our Final project on OOP course, we did a pokemon clone, where you need to defeat
the green nightmare, which is located at the fourth map, who is a very strong pokemon,
you get to choose your starter, and train him on your quest to defeat the nightmare.
```


# List of files created:
### Entity:
- Entity.h - base class.
- Player.h - derived from entity, the player itself. 
### Guis:
- Button.h - button,who is an object inside gui.
- Gui.h - the "base" gui object, can add to it a progress bar.
- ProgressBar.h - progressBar to use in life and exp of pokemons, added as a ability to gui.
### Pokemon:
- Party.h - a party of pokemons, basicly a prepration for adding catching and having more than 1.
- Pokemon.h - pokmeon itself, base stats ivs, currs.
- PokemonFactory.h - a factory to eaisly create pokemons, randomly or not,based on stage or not.
### States:
- AddExpState.h - when you defeat a pokemon, you gain expreince and can level up.
- BaseState.h - the base state which all states derived from.
- ChoosePokemon.h - when you start, you choose your starter pokemon.
- EncounterBattle.h - when you walk on grass, you can trigger a battle.
- FadeinState.h - will fade into a color.
- FadeOutState.h - will fade out into a texture or state.
- GuideState.h - basic guide lines when you start your game.
- PlayerMenuState.h - user menu triggered by M,see your pokemon,heal,save game or quit.
- PlayState.h - the "main" state, where you walk and explore the world.
- PokemonMenuState.h - the menu option of showing your pokemon information.
- StartMenuState.h - the starting menu which its options, its an object within startstate.
- StartState.h - the first state, choose your options.
- TakeDamageState.h - calculation of damage and when you or the enemy take damage.
- TakeTurnState.h - when you completed a choice, like attack, the actual movements.
- TransitionState.h - can be pushed a state, and will handle fade in and out into that state.
### Utilities:
- Fades.h - utilities information for fades.
- PokemonIndex - enums,hashmaps,for pokemon sprites strings and loading.
- StartMenuOptions - operators for easier readble code.
### World:
- TilesMap.h - the tiles map, using tileson API, will parse the json file with all the tiles information.
### General:
- Animation.h - a template class to hold the animation from tileson API.
- Battle.h - the basic structure of the battle, positions, sprites etc.
- Camera.h - to control the view.
- Game.h - the main game loop runs here.
- Level.h - a level has a vector of tilesMap.
- PhysicsMove.h - despite no need, we implemnted some physics movments in the player.
- Resources.h - a singelton who has the textures,rects,fonts etc.
- saveManager.h - class to help save and load the game.
- SoundTon.h - singelton class to manipulate sounds.
- Stack.h - a template class, which acts as a statestack.
- StateMachine.h - runs the game using the States stack.
- Tile.h - a general tile, can add ability to be animated.
- utilities.h - general utilities.
- main.cpp
### Main data structure
- Stack, which is a vector of states, which is controlled as a stack, we only update and handle events of the state on the top of the stack, and we draw everything from the buttom to the top, which gives us a layered game.
- nlohmann json API , save the game into json and parse it back to load it.
- tileson API , to get the json file from Tiled application, and parse it into the game and into our objects
- 6 hash maps in resourcses, to control textures, rects,and sprites
- hashmaps inside tilemap, to get faster running time when checking for specfic tile in a specific location
- std::array when we have a fixed size structures.




### Design
- We researched based on CS50 game development harvard couse, which though us about state machine,and how to build a layered game.
- The maps are designed with the Tiled application, which help create maps.
- we collected spritesheets from several sourcses, and edited them in photoshop.
- using tileson API , we parse the files of maps we get from Tiled, and convert them into our game objects.
- this help us predefine animations and their time, and create layer maps easily.
- At the current stage of the project, its very easy to add more states, add more abilities and functionality.
- Gui class is used everywhere, as a bar, as a message box, and a choice box.
- Sounds are important indicator for the player when certain actions are done, instead of using stright msgs.
- we wanted to add alot more functionality, but we didnt find enough time for everything we wanted:
- NPC using openAi API to generate strings.
- Catching pokemons (the "foundations" are there).
- interacting with objects beside tallgrass.
- Gym, Shop,HealCenter.
- Attacks for pokemons beside a basic physical one
- Npc trainers
  

 

 ### Known bugs
- after battle, the charcter still does the previous pressed key, so can "jump" one more space than needed.
- some resizesing problems with ceratin menu when you change the window size.
- some fadein and fadeout arent perfect ):
### Other comments
  - hope you read this readme file :kissing_smiling_eyes: :smile: :wink:


 
