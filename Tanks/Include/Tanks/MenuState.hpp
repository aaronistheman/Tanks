#ifndef TANKS_MENUSTATE_HPP
#define TANKS_MENUSTATE_HPP

#include <Tanks/State.hpp>
#include <Tanks/Container.hpp>
#include <Tanks/Player.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class MenuState : public State
{
	public:
								MenuState(StateStack& stack, Context context);

		virtual void			draw();
		virtual bool			update(sf::Time dt);
		virtual bool			handleEvent(const sf::Event& event);


	private:
		sf::Sprite				mBackgroundSprite;
		GUI::Container			mGUIContainer;
		Player&				mPlayer;
};

#endif // TANKS_MENUSTATE_HPP