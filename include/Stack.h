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
		

	void pushState(std::unique_ptr<T> state)
	{
		m_states.push_back(std::move(state));
	}
	void popStart()
	{
		if (!m_states.empty())
		{
			m_states.erase(m_states.begin());
		}
	}
	void popState()
	{
		if (!m_states.empty())
		{
			m_states.pop_back();
		}
	}

	std::unique_ptr<T>& back()
	{
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
	void pushQueueState(std::unique_ptr<T> state)
	{
		m_stateQueue.push(std::move(state));
	}
	void update(sf::Time dt)
	{

		while (!m_stateQueue.empty())
		{
			m_states.push_back(std::move(m_stateQueue.front()));
			m_stateQueue.pop();
		}
		if (!m_states.empty())
		{
			std::cout << "inside stack->update"<< std::endl;
			m_states.back()->update(dt);
			if (!m_states.back()->getStatus())
				this->popState();
		}
		std::cout << "finish stack->update" << std::endl;
	}

	void draw()
	{
		for (auto& state : m_states)
		{
			std::cout << "drawing inside the stack draw" << std::endl;
			state->draw(m_window);
		}
	}

	sf::RenderWindow& getWindow()
	{
		return m_window;
	}
	int size()
	{	
		if (m_states.empty())
			return 0;
		return m_states.size();
	}

private:
	std::vector <std::unique_ptr<T>> m_states;
	sf::RenderWindow& m_window;
	std::queue<std::unique_ptr<T>> m_stateQueue;
};