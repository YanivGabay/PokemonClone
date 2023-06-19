#pragma once
#include "Pokemon.h"
#include "utilities.h"

class PokemonFactory
{
public:
	PokemonFactory()
	{
	}

	~PokemonFactory()
	{
	}
    std::unique_ptr<Pokemon> createRandomPokemon(LevelID level)
    {
          std::unique_ptr<Pokemon> pokemon = std::make_unique<Pokemon>();
          // Set the base attributes
          pokemon->setBaseHP(generateRandomNumber(5, 12));
          pokemon->setBaseAttack(generateRandomNumber(5, 12));
          pokemon->setBaseDefense(generateRandomNumber(5, 12));
          pokemon->setBaseSpeed(generateRandomNumber(5, 12));
        
          // Set the IV attributes
          pokemon->setHPIV(generateRandomNumber(0, 6));
          pokemon->setAttackIV(generateRandomNumber(0, 6));
          pokemon->setDefenseIV(generateRandomNumber(0, 6));
          pokemon->setSpeedIV(generateRandomNumber(0, 6));

         //Set current attributes
          pokemon->setAttack(pokemon->getBaseAttack());
          pokemon->setDefense(pokemon->getBaseDefense());
          pokemon->setSpeed(pokemon->getBaseSpeed());
          pokemon->setHP(pokemon->getBaseHP());
          // Set other attributes of the Pokemon as needed

          pokemon->levelUp(); // Level up the Pokemon to level 1
          switch (level)
          { //attach the string and sprite for pool of this level
              case LevelID::START_TOWN:
                  
                  break;
             
              default:
                  // Handle any other level if needed
                  break;
          }

       

          return pokemon;
    }
    std::unique_ptr<Pokemon> createPokemon(std::string name)
    {
        std::unique_ptr<Pokemon> pokemon = std::make_unique<Pokemon>();
        // Set the base attributes
        pokemon->setBaseHP(generateRandomNumber(5, 12));
        pokemon->setBaseAttack(generateRandomNumber(5, 12));
        pokemon->setBaseDefense(generateRandomNumber(5, 12));
        pokemon->setBaseSpeed(generateRandomNumber(5, 12));

        // Set the IV attributes
        pokemon->setHPIV(generateRandomNumber(0, 6));
        pokemon->setAttackIV(generateRandomNumber(0, 6));
        pokemon->setDefenseIV(generateRandomNumber(0, 6));
        pokemon->setSpeedIV(generateRandomNumber(0, 6));

        //Set current attributes
        pokemon->setAttack(pokemon->getBaseAttack());
        pokemon->setDefense(pokemon->getBaseDefense());
        pokemon->setSpeed(pokemon->getBaseSpeed());
        pokemon->setHP(pokemon->getBaseHP());
        // Set other attributes of the Pokemon as needed

        pokemon->levelUp(); // Level up the Pokemon to level 1
    }
private:

};
