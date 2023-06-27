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
    std::shared_ptr<Pokemon> createRandomPokemon(LevelID level)
    {
          std::shared_ptr<Pokemon> pokemon = std::make_shared<Pokemon>();
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
          pokemon->levelUp(); // Level up the Pokemon to level 1
          pokemon->setCurrentHP(pokemon->getHP());
          // Set other attributes of the Pokemon as needed

        
          enum PokemonIndex name = PokemonIndex::END;
          switch (level)
          { //attach the string and sprite for pool of this level
              case LevelID::START_TOWN:
                  name = getRandom(FirstLevel);
                  break;
              case LevelID::START_FIELD:
                  name = getRandom(SecondLevel);
                  break;
              case LevelID::SECOND_TOWN:
                  name = getRandom(ThirdLevel);
                  break;
              default:
                  // Handle any other level if needed
                  break;
          }

          pokemon->setName(name);
          pokemon->setSprites();
        

          return pokemon;
    }
    std::shared_ptr<Pokemon> createRandomPokemonByLevel(LevelID id,int level)
    {
        std::shared_ptr<Pokemon> pokemon = createRandomPokemon(id);
        if (level < 1)
            throw std::range_error("level under 1");
        for (int i = 0; i < level; i++)
        {
            pokemon->levelUp();
        }
        return pokemon;
    }
    std::shared_ptr<Pokemon> createPokemon(enum PokemonIndex name)
    {
        std::shared_ptr<Pokemon> pokemon = std::make_shared<Pokemon>();
        // Set the base attributes
        pokemon->setBaseHP(generateRandomNumber(8, 12));
        pokemon->setBaseAttack(generateRandomNumber(6, 12));
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
        pokemon->levelUp(); // Level up the Pokemon to level 1
        pokemon->setCurrentHP(pokemon->getHP());

       

        pokemon->setName(name);
        pokemon->setSprites();
     
        return pokemon;
    }
private:

};
