#pragma once

#include <iostream>
#include <vector>
#include <random>
#include "Resources.h"

class Pokemon
{
public:
    Pokemon() = default;
    Pokemon(enum PokemonIndex name,
            int baseHP,
            int baseAttack,
            int baseDefense,
            int baseSpeed,
            int HPIV,
            int attackIV,
            int defenseIV,
            int speedIV,
            int HP,
            int attack,
            int defense,
            int speed,
            int level,
            int currentExp,
            float expToLevel,
            int currentHP)
        : m_name(name),
        m_baseHP(baseHP),
        m_baseAttack(baseAttack),
        m_baseDefense(baseDefense),
        m_baseSpeed(baseSpeed),
        m_HPIV(HPIV),
        m_attackIV(attackIV),
        m_defenseIV(defenseIV),
        m_speedIV(speedIV),
        m_HP(HP),
        m_attack(attack),
        m_defense(defense),
        m_speed(speed),
        m_level(level),
        m_currentExp(currentExp),
        m_expToLevel(expToLevel),
        m_currentHP(currentHP)
    {
        setSprites();
    }
    
    ~Pokemon() = default;
    
    std::vector<int> levelUp()
    {
        m_level++;
        m_expToLevel = m_level * m_level * 5 * 0.75f;
        return statsLevelUp();
    }
    //will return a vector to display to the player
    std::vector<int> statsLevelUp()
    {
        int HPIncrease = 0;
        for (int j = 1; j <= 3; j++)
        {
            if (std::rand() % 6 + 1 <= m_HPIV)
            {
                m_HP++;
                HPIncrease++;
            }
        }

        int attackIncrease = 0;
        for (int j = 1; j <= 3; j++)
        {
            if (std::rand() % 6 + 1 <= m_attackIV)
            {
                m_attack++;
                attackIncrease++;
            }
        }

        int defenseIncrease = 0;
        for (int j = 1; j <= 3; j++)
        {
            if (std::rand() % 6 + 1 <= m_defenseIV)
            {
                m_defense++;
                defenseIncrease++;
            }
        }

        int speedIncrease = 0;
        for (int j = 1; j <= 3; j++)
        {
            if (std::rand() % 6 + 1 <= m_speedIV)
            {
                m_speed++;
                speedIncrease++;
            }
        }

        return { HPIncrease, attackIncrease, defenseIncrease, speedIncrease };
    }

    //gets:
    enum PokemonIndex getName() const
    {
        return m_name;
    }

    std::string getPokemonName()
    {
        return PokemonNames.at(m_name);
    }
    int getBaseHP() const
    {
        return m_baseHP;
    }

    int getBaseAttack() const
    {
        return m_baseAttack;
    }

    int getBaseDefense() const
    {
        return m_baseDefense;
    }

    int getBaseSpeed() const
    {
        return m_baseSpeed;
    }

    int getHPIV() const
    {
        return m_HPIV;
    }

    int getAttackIV() const
    {
        return m_attackIV;
    }

    int getDefenseIV() const
    {
        return m_defenseIV;
    }

    int getSpeedIV() const
    {
        return m_speedIV;
    }

    int getHP() const
    {
        return m_HP;
    }

    int getAttack() const
    {
        return m_attack;
    }

    int getDefense() const
    {
        return m_defense;
    }

    int getSpeed() const
    {
        return m_speed;
    }

    int getLevel() const
    {
        return m_level;
    }

    int getCurrentExp() const
    {
        return m_currentExp;
    }

    float getExpToLevel() const
    {
        return m_expToLevel;
    }

    int getCurrentHP() const
    {
        return m_currentHP;
    }
    float getHpPercent() const
    {
       
        float percentage = (static_cast<float>(m_currentHP) / static_cast<float>(m_HP)) * 100.0f;
      
        return percentage;
    }
    //sets::
    void applyDamage(const int damage)
    {
        
        m_currentHP -= damage;
        if (m_currentHP < 0)
        {
            m_currentHP = 0;
            
        }
       

    }
    void setName(const  enum PokemonIndex name)
    {
        m_name = name;
    }

    void setBaseHP(int baseHP)
    {
        m_baseHP = baseHP;
    }

    void setBaseAttack(int baseAttack)
    {
        m_baseAttack = baseAttack;
    }

    void setBaseDefense(int baseDefense)
    {
        m_baseDefense = baseDefense;
    }

    void setBaseSpeed(int baseSpeed)
    {
        m_baseSpeed = baseSpeed;
    }

    void setHPIV(int HPIV)
    {
        m_HPIV = HPIV;
    }

    void setAttackIV(int attackIV)
    {
        m_attackIV = attackIV;
    }

    void setDefenseIV(int defenseIV)
    {
        m_defenseIV = defenseIV;
    }

    void setSpeedIV(int speedIV)
    {
        m_speedIV = speedIV;
    }

    void setHP(int HP)
    {
        m_HP = HP;
    }

    void setAttack(int attack)
    {
        m_attack = attack;
    }

    void setDefense(int defense)
    {
        m_defense = defense;
    }

    void setSpeed(int speed)
    {
        m_speed = speed;
    }

    void setLevel(int level)
    {
        m_level = level;
    }

    void setCurrentExp(int currentExp)
    {
        m_currentExp = currentExp;
    }

    void setExpToLevel(float expToLevel)
    {
        m_expToLevel = expToLevel;
    }

    void setCurrentHP(int currentHP)
    {
        m_currentHP = currentHP;
    }
    void setSprites()
    {
        std::pair<sf::Sprite,sf::Sprite> spritePair = Resources::getInstance().getPokemonSprites(m_name);
        m_battleSpriteFront = spritePair.first;
        m_battleSpriteBack = spritePair.second;
        if (!m_battleSpriteFront.getTexture()||!m_battleSpriteBack.getTexture())
        {
            std::cout << "no texture of pokemon" << "enum value:" << static_cast<int> (m_name) << std::endl;
        }
        m_battleSpriteFront.setScale(2.0f, 2.0f);
        m_battleSpriteBack.setScale(2.0f, 2.0f);
    }
    std::pair<sf::Sprite, sf::Sprite> getSprites()
    {
        return std::make_pair(m_battleSpriteFront, m_battleSpriteFront);
    }
    sf::Sprite& getBackSprite()
    {
        return m_battleSpriteBack;
    }
    sf::Sprite& getFrontSprite()
    {
        return m_battleSpriteFront;
    }
    bool isAlive()
    {
        if (m_currentHP <= 0)
        { 
            m_currentHP = 0;
            return false;
        }
        return true;
    }
    bool levelUpCheck()
    {
        if (m_currentExp > m_expToLevel)
        {
            m_currentExp = 0;
            return true;
        }
        return false;
    }
    float getCurrentExpPercent() const
    {
        if (m_expToLevel == 0)
        {
            return 0.0f;
        }
        return (static_cast<float>(m_currentExp) / m_expToLevel) * 100.0f;
    }

private:
    enum PokemonIndex m_name;
    sf::Sprite m_battleSpriteFront;
    sf::Sprite m_battleSpriteBack;

    int m_baseHP{ 0 };
    int m_baseAttack{ 0 };
    int m_baseDefense{ 0 };
    int m_baseSpeed{ 0 };

    int m_HPIV{ 0 };
    int m_attackIV{ 0 };
    int m_defenseIV{ 0 };
    int m_speedIV{ 0 };

    int m_HP{ 0 };
    int m_attack{ 0 };
    int m_defense{ 0 };
    int m_speed{ 0 };

    int m_level{ 0 };
    int m_currentExp{ 0 };
    float m_expToLevel{ 0 };
    int m_currentHP{ 0 };

    
};
