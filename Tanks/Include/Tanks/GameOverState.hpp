#ifndef TANKS_GAMEOVERSTATE_HPP
#define TANKS_GAMEOVERSTATE_HPP

#include <Tanks/State.hpp>
#include <Tanks/Container.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class GameOverState : public State
{
	public:
							GameOverState(StateStack& stack, Context context);

		virtual void		draw();
		virtual bool		update(sf::Time dt);
		virtual bool		handleEvent(const sf::Event& event);


	private:
		sf::Text			mGameOverText;
    sf::Text      mPromptText;
		sf::Time			mElapsedTime;
    sf::Time      mWaitTime;
    bool          mKeyReleased;
};

#endif // TANKS_GAMEOVERSTATE_HPP