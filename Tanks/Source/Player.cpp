#include <Tanks/Player.hpp>
#include <Tanks/CommandQueue.hpp>
#include <Tanks/Tank.hpp>
#include <Tanks/Foreach.hpp>

#include <map>
#include <string>
#include <algorithm>


struct TankMover
{
	TankMover(float vx, float vy)
	: velocity(vx, vy)
	{
	}

	void operator() (Tank& tank, sf::Time) const
	{
		tank.accelerate(velocity);
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
    tank.rotate(offset);
  }

  float offset;
};

Player::Player()
{
	// Set initial key bindings
	mKeyBinding[sf::Keyboard::Left] = MoveLeft;
	mKeyBinding[sf::Keyboard::Right] = MoveRight;
	mKeyBinding[sf::Keyboard::Up] = MoveUp;
	mKeyBinding[sf::Keyboard::Down] = MoveDown;
  mKeyBinding[sf::Keyboard::S] = RotateLeft;
  mKeyBinding[sf::Keyboard::D] = RotateRight;

	// Set initial action bindings
	initializeActions();	

	// Assign all categories to player's tank
	FOREACH(auto& pair, mActionBinding)
		pair.second.category = Category::PlayerAircraft;
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

void Player::initializeActions()
{
	const float playerSpeed = 200.f;
  const float playerRotationSpeed = 80.0f;

	mActionBinding[MoveLeft].action	 = derivedAction<Tank>(TankMover(-playerSpeed, 0.f));
	mActionBinding[MoveRight].action = derivedAction<Tank>(TankMover(+playerSpeed, 0.f));
	mActionBinding[MoveUp].action    = derivedAction<Tank>(TankMover(0.f, -playerSpeed));
	mActionBinding[MoveDown].action  = derivedAction<Tank>(TankMover(0.f, +playerSpeed));
  mActionBinding[RotateLeft].action  = derivedAction<Tank>(TankRotator(-playerRotationSpeed));
  mActionBinding[RotateRight].action = derivedAction<Tank>(TankRotator(playerRotationSpeed));
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
			return true;

		default:
			return false;
	}
}
