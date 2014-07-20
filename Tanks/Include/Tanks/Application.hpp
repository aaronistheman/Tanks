#ifndef TANKS_APPLICATION_HPP
#define TANKS_APPLICATION_HPP

#include <Tanks/World.hpp>
#include <Tanks/Player.hpp>

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


class Application : private sf::NonCopyable
{
	public:
								Application();
		void					run();
		

	private:
		void					processInput();
		void					update(sf::Time elapsedTime);
		void					render();
		void					updateStatistics(sf::Time elapsedTime);


	private:
		static const sf::Time	TimePerFrame;

		sf::RenderWindow		mWindow;
		World					mWorld;
		Player					mPlayer;

	  	sf::Font				mFont;
		sf::Text				mStatisticsText;
		sf::Time				mStatisticsUpdateTime;
		std::size_t				mStatisticsNumFrames;
};

#endif // TANKS_APPLICATION_HPP
