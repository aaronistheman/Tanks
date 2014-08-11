#include <Tanks/Player.hpp>
#include <Tanks/CommandQueue.hpp>
#include <Tanks/Tank.hpp>
#include <Tanks/Foreach.hpp>
#include <Tanks/LevelIdentifiers.hpp>

#include <map>
#include <string>
#include <algorithm>

using namespace std::placeholders;


struct TankMover
{
	TankMover(float vx, float vy)
	: velocity(vx, vy)
	{
	}

	void operator() (Tank& tank, sf::Time) const
	{
		tank.accelerate(velocity * tank.getMaxMovementSpeed());
	}

	sf::Vector2f velocity;
};

struct TankRotator
{
  TankRotator(float angle)
  : offset(angle)
  {
  }

  void operator() (Tank& tank, sf::Time) const
  {
    tank.rotate(offset * tank.getMaxRotationSpeed());
  }

  float offset;
};

Player::Player()
: mCurrentMissionStatus(MissionRunning)
, mLevel(GameType::Default)
{
	// Set initial key bindings
	mKeyBinding[sf::Keyboard::Left] = MoveLeft;
	mKeyBinding[sf::Keyboard::Right] = MoveRight;
	mKeyBinding[sf::Keyboard::Up] = MoveUp;
	mKeyBinding[sf::Keyboard::Down] = MoveDown;
  mKeyBinding[sf::Keyboard::S] = RotateLeft;
  mKeyBinding[sf::Keyboard::D] = RotateRight;
  mKeyBinding[sf::Keyboard::Space] = Fire;

	// Set initial action bindings
	initializeActions();	

	// Assign all categories to player's tank
	FOREACH(auto& pair, mActionBinding)
		pair.second.category = Category::PlayerTank;
}

void Player::handleEvent(const sf::Event& event, CommandQueue& commands)
{
	if (event.type == sf::Event::KeyPressed)
	{
		// Check if pressed key appears in key binding, trigger command if so
		auto found = mKeyBinding.find(event.key.code);
		if (found != mKeyBinding.end() && !isRealtimeAction(found->second))
			commands.push(mActionBinding[found->second]);
	}
}

void Player::handleRealtimeInput(CommandQueue& commands)
{
	// Traverse all assigned keys and check if they are pressed
	FOREACH(auto pair, mKeyBinding)
	{
		// If key is pressed, lookup action and trigger corresponding command
    if (sf::Keyboard::isKeyPressed(pair.first) && isRealtimeAction(pair.second))
			commands.push(mActionBinding[pair.second]);
	}
}

void Player::assignKey(Action action, sf::Keyboard::Key key)
{
	// Remove all keys that already map to action
	for (auto itr = mKeyBinding.begin(); itr != mKeyBinding.end(); )
	{
		if (itr->second == action)
			mKeyBinding.erase(itr++);
		else
			++itr;
	}

	// Insert new binding
	mKeyBinding[key] = action;
}

sf::Keyboard::Key Player::getAssignedKey(Action action) const
{
	FOREACH(auto pair, mKeyBinding)
	{
		if (pair.second == action)
			return pair.first;
	}

	return sf::Keyboard::Unknown;
}

void Player::setMissionStatus(MissionStatus status)
{
	mCurrentMissionStatus = status;
}

Player::MissionStatus Player::getMissionStatus() const
{
	return mCurrentMissionStatus;
}

Level Player::getLevel() const
{
  return mLevel;
}

void Player::initializeActions()
{
	mActionBinding[MoveLeft].action	 = derivedAction<Tank>(TankMover(-1,  0));
	mActionBinding[MoveRight].action = derivedAction<Tank>(TankMover(+1,  0));
	mActionBinding[MoveUp].action    = derivedAction<Tank>(TankMover( 0, -1));
	mActionBinding[MoveDown].action  = derivedAction<Tank>(TankMover( 0, +1));
  mActionBinding[RotateLeft].action  = derivedAction<Tank>(TankRotator(-1));
  mActionBinding[RotateRight].action = derivedAction<Tank>(TankRotator( 1));
	mActionBinding[Fire].action        = derivedAction<Tank>([] (Tank& a, sf::Time){ a.fire(); });
}

bool Player::isRealtimeAction(Action action)
{
	switch (action)
	{
		case MoveLeft:
		case MoveRight:
		case MoveDown:
		case MoveUp:
    case RotateLeft:
    case RotateRight:
    case Fire:
			return true;

		default:
			return false;
	}
}
