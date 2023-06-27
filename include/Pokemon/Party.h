#pragma once

#include "Pokemon.h"
#include <array>
#include <iterator>
#include "Utilities/PokemonIndex.h"
#include <optional>
const int STARTER = 0;
const int PARTY_SIZE = 6;

class Party
{
public:
    Party()
        : m_CurrentPokemonIndex(std::nullopt)
    {
    }

    ~Party()
    {
    }
    void healPokemon()
    {
        for (auto& pokemon : m_pokemons)
        {
            pokemon->setCurrentHP(pokemon->getHP());
        }
    }

    int getPartySize()
    {
        return PARTY_SIZE;
    }
    void addPokemon(std::shared_ptr<Pokemon> pokemon)
    {
        if (!pokemon)
        {
            std::cerr << "Passed pokemon shared_ptr is null." << std::endl;
            return;
        }

        for (int pokemonIndex = 0; pokemonIndex < PARTY_SIZE; pokemonIndex++)
        {
          
            if (!m_pokemons[pokemonIndex])
            {
               
                m_pokemons[pokemonIndex] = std::move(pokemon);
               
                // Set the current Pokemon index if it's the first Pokemon added
                if (!m_CurrentPokemonIndex)
                {
                   
                    m_CurrentPokemonIndex = pokemonIndex;

                }
               
                return;
            }
        }
        std::cout << "Party is full. Cannot add more Pokemon." << std::endl;
    }
    void checkIndex(const int index)
    {
        if (index >= PARTY_SIZE)
        {
            throw std::runtime_error("Index out of range.");
        }

        if (!m_pokemons[index])
        {
            ;
            //throw std::runtime_error("No Pokemon found at the specified index.");
        }
    }
    std::shared_ptr<Pokemon> getPokemon(int index)
    {
        checkIndex(index);
        return m_pokemons[index];
    }
    std::shared_ptr<Pokemon> getCurrPokemon()
    {
        checkIndex(m_CurrentPokemonIndex.value());
        return m_pokemons[m_CurrentPokemonIndex.value()];
    }
    void setCurrentPokemon(int index)
    {
        checkIndex(index);

        m_CurrentPokemonIndex = index;
    }

    std::shared_ptr<Pokemon> getStarterPokemon()
    {
        std::shared_ptr<Pokemon> ptr = getPokemon(STARTER);
        if (!ptr)
        {
            throw std::runtime_error("No current Pokemon selected.");
        }

        return ptr;
    }

private:
    std::array<std::shared_ptr<Pokemon>, PARTY_SIZE> m_pokemons{{nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}};
    std::optional<int> m_CurrentPokemonIndex;
};
