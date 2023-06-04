#pragma once

#include <vector>
#include <memory>


template <class T>
class Stack
{
public:
	Stack()
		: m_window(Resources::getInstance().getWindow())
	{}
	~Stack() = default;


	void pushFadeOut(std::unique_ptr<T> nextstate, std::unique_ptr<T> fadein)
	{
		this->popState();
		this->popState();
		this->pushState(std::move(nextstate));
		this->pushState(std::move(fadein));
	}

	void pushState(std::unique_ptr<T> state)
	{
		m_states.push_back(std::move(state));
	}

	void popState()
	{
		if (!m_states.empty())
		{
			m_states.pop_back();
		}
	}

	T& back() {
		return m_states.back();
	}

	bool empty(){
		return m_states.empty();
	}

	void handleEvents()
	{
		if (!m_states.empty())
		{
			sf::Event event;
			while (m_window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					m_window.close();
				else
				{
					m_states.back()->handleEvents(event);

				}
			}
		}
	}

	void update(sf::Time dt)
	{
		if (!m_states.empty())
		{
			m_states.back()->update(dt);
			if (!m_states.back()->getStatus())
				this->popState();
		}
	}

	void draw()
	{
		for (auto& state : m_states)
		{
			state->draw(getWindow());
		}
	}

	sf::RenderWindow& getWindow()
	{
		return m_window;
	}


private:
	std::vector <std::unique_ptr<T>> m_states;
	sf::RenderWindow& m_window;
};