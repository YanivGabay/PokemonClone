#pragma once

#include <vector>
#include <memory>
#include <queue>




template <class T>
class Stack
{
public:
	Stack()
		: m_window(Resources::getInstance().getWindow()) {}
	
	~Stack() = default;
	
	void pushState(std::unique_ptr<T> state)
	{
		std::cout << "pushState" << "   pushing state: ";
		printDebugState(typeid(state).name());
	    std::cout << std::endl;

		printInfoDebug();
		m_states.push_back(std::move(state));
		std::cout << "\nafter PushState" << std::endl;
		printInfoDebug();
	}
	
	void popStart()
	{
		std::cout << "popStart" << std::endl;
		printInfoDebug();
		if (!m_states.empty())
		{
			m_states.erase(m_states.begin());
		}
		std::cout << "\nafter popStart" << std::endl;
		printInfoDebug();
	}
	
	void popState()
	{
		std::cout << "popState" << std::endl;
		printInfoDebug();;
		
		if (!m_states.empty())
		{
			m_states.pop_back();
		}
		std::cout << "\nafter popState" << std::endl;
		printInfoDebug();
	}

	std::unique_ptr<T>& back()
	{
		return m_states.back();
	}

	bool empty()
	{
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
				{
					m_window.close();
				}
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
		if (!m_states.empty())
		{
			m_states.back()->update(dt);
	
			if (!m_states.back()->getStatus())
			{
				this->popState();
			}
		}
		
		while (!m_stateQueue.empty())
		{
			m_states.push_back(std::move(m_stateQueue.front()));
			m_stateQueue.pop();
		}
	}

	void draw()
	{
		for (auto& state : m_states)
		{
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
		{
			return 0;
		}

		return m_states.size();
	}
	void printDebugState(const char* name)
	{
		std::cout << name << std::endl;
	}

	
	void printTypeOf()
	{ 


		std::cout << "//////////////////////////"
			<< " STATE STACK "
			<< "//////////////////////////\n";
		if(m_states.size())
		for (std::size_t i = 0; i < m_states.size(); ++i)
		{
			std::cout << "Item at position " << i << ": ";
			printDebugState(typeid(*m_states[i]).name());
			
		}
		std::cout << "Total stack size: " << m_states.size() << "\n\n";

		// Print queue
		printQueueTypeOf();
		
	}
	void printInfoDebug()
	{
		std::cout << "!!!! info !!!\n";
			printTypeOf();
			std::cout << "!!!! finished !!!\n";
	}
	
	
	void printQueueTypeOf()
	{
		std::cout << "//////////////////////////"
			<< " STATE QUEUE "
			<< "//////////////////////////\n";

		if (m_stateQueue.empty())
		{
			std::cout << "stateQueue is empty" << std::endl;
			return;
		}

		int position = 0;
		std::size_t originalSize = m_stateQueue.size(); // Store the original size

		for (std::size_t i = 0; i < originalSize; ++i)
		{
			// Access the front element
			const T* element = m_stateQueue.front().get(); // Get raw pointer

			if (element)
			{
				std::cout << "Item at position " << position << ": ";
				std::cout << typeid(*element).name() << std::endl;
			}
			else
			{
				std::cout << "Item at position " << position << ": " << "nullptr" << std::endl;
			}

			// Move the front element to the back to maintain queue order
			m_stateQueue.push(std::move(m_stateQueue.front()));
			m_stateQueue.pop();

			++position;
		}

		std::cout << "Total queue size: " << originalSize << "\n";
	}
	
	bool checkQuitStatus()
	{
		return m_states.back()->getQuitGameStatus();
	}

private:
	std::vector <std::unique_ptr<T>> m_states;
	sf::RenderWindow& m_window;
	std::queue<std::unique_ptr<T>> m_stateQueue;
};
