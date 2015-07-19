/*
  Authors of original version: Artur Moreira, Henrik Vogelius Hansson, and
    Jan Haller
*/

#ifndef TANKS_SETTINGSSTATE_HPP
#define TANKS_SETTINGSSTATE_HPP

#include <Tanks/State.hpp>
#include <Tanks/Player.hpp>
#include <Tanks/Container.hpp>
#include <Tanks/Button.hpp>
#include <Tanks/Label.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <array>


class SettingsState : public State
{
	public:
										SettingsState(StateStack& stack, Context context);

		virtual void					draw();
		virtual bool					update(sf::Time dt);
		virtual bool					handleEvent(const sf::Event& event);


	private:
		void							updateLabels();
		void							addButtonLabel(Player::Action action, float y, const std::string& text, Context context);


	private:
		sf::Sprite											mBackgroundSprite;
		GUI::Container										mGUIContainer;
		std::array<GUI::Button::Ptr, Player::ActionCount>	mBindingButtons;
		std::array<GUI::Label::Ptr, Player::ActionCount> 	mBindingLabels;
};

#endif // TANKS_SETTINGSSTATE_HPP
