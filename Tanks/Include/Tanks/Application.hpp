/*
  Authors of original version: Artur Moreira, Henrik Vogelius Hansson, and
    Jan Haller
*/

#ifndef TANKS_APPLICATION_HPP
#define TANKS_APPLICATION_HPP

#include <Tanks/ResourceHolder.hpp>
#include <Tanks/ResourceIdentifiers.hpp>
#include <Tanks/Player.hpp>
#include <Tanks/StateStack.hpp>

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>


class Application : private sf::NonCopyable
{
	public:
								Application();
		void					run();
		

	private:
		void					processInput();
		void					update(sf::Time dt);
		void					render();

		void					updateStatistics(sf::Time dt);
    void          registerStates();


	private:
		static const sf::Time	TimePerFrame;

		sf::RenderWindow		mWindow;
		TextureHolder			mTextures;
	  	FontHolder				mFonts;
		Player					mPlayer;

		StateStack				mStateStack;

		sf::Text				mStatisticsText;
		sf::Time				mStatisticsUpdateTime;
		std::size_t				mStatisticsNumFrames;
};

#endif // TANKS_APPLICATION_HPP
