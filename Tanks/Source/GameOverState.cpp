#include <Tanks/GameOverState.hpp>
#include <Tanks/Utility.hpp>
#include <Tanks/Player.hpp>
#include <Tanks/ResourceHolder.hpp>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>


GameOverState::GameOverState(StateStack& stack, Context context)
: State(stack, context)
, mGameOverText()
, mPromptText()
, mElapsedTime(sf::Time::Zero)
, mWaitTime(sf::Time::Zero)
, mKeyReleased(false)
{
	sf::Font& font = context.fonts->get(Fonts::Main);
	sf::Vector2f windowSize(context.window->getSize());

	mGameOverText.setFont(font);
	if (context.player->getMissionStatus() == Player::MissionFailure)
		mGameOverText.setString("Mission failed!");	
	else
		mGameOverText.setString("Mission successful!");

	mGameOverText.setCharacterSize(70);
	centerOrigin(mGameOverText);
	mGameOverText.setPosition(0.5f * windowSize.x, 0.4f * windowSize.y);

  mPromptText.setFont(font);
  mPromptText.setString("Enter a key to exit");
  centerOrigin(mPromptText);
  mPromptText.setPosition(mGameOverText.getPosition().x,
                          mGameOverText.getPosition().y + 150.f);

  mWaitTime = sf::seconds(0.5);
}

void GameOverState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());

	// Create dark, semitransparent background
	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setSize(window.getView().getSize());

	window.draw(backgroundShape);
	window.draw(mGameOverText);
  if (mElapsedTime > mWaitTime)
    window.draw(mPromptText);
}

bool GameOverState::update(sf::Time dt)
{
	// Show state for certain amount of time, then wait for a
  // key to be released before returning to menu
	mElapsedTime += dt;
	if (mElapsedTime > mWaitTime && mKeyReleased)
	{
		requestStateClear();
		requestStackPush(States::Menu);
	}
	return false;
}

bool GameOverState::handleEvent(const sf::Event& event)
{
  if (!mKeyReleased &&
      mElapsedTime > mWaitTime && 
      event.type == sf::Event::KeyReleased)
    mKeyReleased = true;

	return false;
}
