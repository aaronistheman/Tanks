#ifndef TANKS_MENUSTATE_HPP
#define TANKS_MENUSTATE_HPP

#include <Tanks/State.hpp>
#include <Tanks/Container.hpp>

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
};

#endif // TANKS_MENUSTATE_HPP