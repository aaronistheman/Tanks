#include <Tanks/GameOverState.hpp>
#include <Tanks/Utility.hpp>
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
, mMissionStatus(context.player->getMissionStatus())
{
	sf::Font& font = context.fonts->get(Fonts::Main);
	sf::Vector2f windowSize(context.window->getSize());

	mGameOverText.setFont(font);
	if (mMissionStatus == Player::MissionFailure)
  {
		mGameOverText.setString("Mission failed!");	
    context.player->setGameType(GameType::None);
  }
	else // assume mission successful
  {
		mGameOverText.setString("Mission successful!");
    context.player->incrementLevel();
  }

	mGameOverText.setCharacterSize(70);
	centerOrigin(mGameOverText);
	mGameOverText.setPosition(0.5f * windowSize.x, 0.4f * windowSize.y);

  mPromptText.setFont(font);
  if (mMissionStatus == Player::MissionFailure)
    mPromptText.setString("Enter a key to exit");
  else
    // assume mission successful
    mPromptText.setString("Enter a key to continue");
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
    if (mMissionStatus == Player::MissionFailure)
    {
		  requestStateClear();
		  requestStackPush(States::Menu);
    }
    else // assume Player::MissionSuccess
    {
      requestStateClear();
      requestStackPush(States::Game);
    }
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
