#pragma once

#include <optional>
#include <iostream>
#include "BaseState.h"
#include "FadeInState.h"
#include "FadeOutState.h"
#include "StartMenuState.h"
#include "TransitionState.h"
#include "PlayState.h"
#include <future>
#include "saveManager.h"


class StartState : public BaseState
{
public:
	StartState(Stack<BaseState>& states)
		: BaseState(states),m_texture(Resources::getInstance().getTexture("resources/background.png"))
	{
		entry();
	}

	virtual ~StartState() = default;

	void entry() override
	{
		m_sprite.setTexture(m_texture);
		m_startMenu = std::move(std::make_unique<StartMenuState>(getStateStack()));
	}
	
	void exit() override
	{
		auto playstate = m_loadingFuture.get();

		sf::View view = playstate->getView();
		
		// Now that PlayState is created, push it to the queue
		auto transition = std::make_unique<TransitionState>(getStateStack().get(), std::move(playstate), Resources::getInstance().getColor(BLACK));
		
		getStateStack().get().pushQueueState(std::move(transition));
		
		m_startMenu->resetText();
		m_loadingStarted = false;
		
	}
	
	void update(sf::Time dt) override
	{
		m_startMenu->update(dt);
		
		if (m_startMenu->getChoice() == QUIT)
		{
			SoundTon::getInstance().playSound(soundNames::CLICK);
			
			m_choice = std::nullopt;
			
			std::this_thread::sleep_for(std::chrono::seconds(1));
			
			setQuitGame();
		}
		
		if (m_startMenu->getChoice() == NEW_GAME && !m_loadingStarted)
		{
			SoundTon::getInstance().playSound(soundNames::CLICK);

			m_choice = std::nullopt;
			m_loadingStarted = true;

			// Asynchronously create PlayState
			m_loadingFuture = std::async(std::launch::async, [this]
				{
					return std::make_unique<PlayState>(getStateStack().get());
				});
			
			m_startMenu->setLoadingText();
		}

		if (m_startMenu->getChoice() == LOAD_GAME && !m_loadingStarted)
		{
			SoundTon::getInstance().playSound(soundNames::CLICK);
			
			m_choice = std::nullopt;
			m_loadingStarted = true;
			
			// Asynchronously create PlayState
			m_loadingFuture = std::async(std::launch::async, [this]
				{
					return std::move( m_saveManager.loadingFromFile(getStateStack().get()));
				});
			
			m_startMenu->setLoadingText();
		}

		if (m_loadingStarted &&
			m_loadingFuture.valid() &&
			m_loadingFuture.wait_for(std::chrono::seconds(0)) == std::future_status::ready)
		{
			exit();
		}
	}
	
	void handleEvents(sf::Event event) override
	{
		m_startMenu->handleEvents(event);
	}
	
	void draw(sf::RenderWindow& window) override
	{
		window.draw(m_sprite);
		m_startMenu->draw(window);
	}

private:
	saveManager m_saveManager;
	
	std::optional<StartMenuOptions> m_choice{ std::nullopt };
	std::unique_ptr<StartMenuState> m_startMenu;
	sf::Texture& m_texture;
	sf::Sprite m_sprite;
	std::future<std::unique_ptr<PlayState>> m_loadingFuture;
	std::atomic<bool> m_loadingStarted {false};
};
