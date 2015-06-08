#include <Tanks/MenuState.hpp>
#include <Tanks/Button.hpp>
#include <Tanks/Utility.hpp>
#include <Tanks/ResourceHolder.hpp>
#include <Tanks/LevelIdentifiers.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>


MenuState::MenuState(StateStack& stack, Context context)
: State(stack, context)
, mGUIContainer()
, mPlayer(*context.player)
{
	sf::Texture& texture = context.textures->get(Textures::TitleScreen);
	mBackgroundSprite.setTexture(texture);
  setSize(mBackgroundSprite, sf::Vector2f(context.window->getSize()));

	auto playDefaultButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	playDefaultButton->setPosition(100, 250);
	playDefaultButton->setText("Play");
	playDefaultButton->setCallback([this] ()
	{
		requestStackPop();
		requestStackPush(States::Game);
    mPlayer.setGameType(GameType::Default);
	});

  auto playSurvivalButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
  playSurvivalButton->setPosition(100, 300);
  playSurvivalButton->setText("Survival");
  playSurvivalButton->setCallback([this] ()
  {
    requestStackPop();
    requestStackPush(States::Game);
    mPlayer.setGameType(GameType::Survival);
  });

	auto settingsButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	settingsButton->setPosition(100, 350);
	settingsButton->setText("Settings");
	settingsButton->setCallback([this] ()
	{
		requestStackPush(States::Settings);
	});

	auto exitButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	exitButton->setPosition(100, 400);
	exitButton->setText("Exit");
	exitButton->setCallback([this] ()
	{
		requestStackPop();
	});

	mGUIContainer.pack(playDefaultButton);
  mGUIContainer.pack(playSurvivalButton);
	mGUIContainer.pack(settingsButton);
	mGUIContainer.pack(exitButton);
}

void MenuState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.setView(window.getDefaultView());

	window.draw(mBackgroundSprite);
	window.draw(mGUIContainer);
}

bool MenuState::update(sf::Time)
{
	return true;
}

bool MenuState::handleEvent(const sf::Event& event)
{
	mGUIContainer.handleEvent(event);
	return false;
}
