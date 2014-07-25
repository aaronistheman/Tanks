#include <Tanks/Tank.hpp>
#include <Tanks/DataTables.hpp>
#include <Tanks/ResourceHolder.hpp>
#include <Tanks/Utility.hpp>
#include <Tanks/CommandQueue.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>


namespace
{
  const std::vector<TankData> Table = initializeTankData();
}

Tank::Tank(Type type, const TextureHolder& textures, const FontHolder& fonts)
: Entity(Table[type].hitpoints)
, mType(type)
, mSprite(textures.get(Table[type].texture))
, mTravelledDistance(0.f)
, mDirectionIndex(0)
, mHealthDisplay(nullptr)
{
	centerOrigin(mSprite);

  std::unique_ptr<TextNode> healthDisplay(new TextNode(fonts, ""));
  mHealthDisplay = healthDisplay.get();
  attachChild(std::move(healthDisplay));

  updateTexts();
}

unsigned int Tank::getCategory() const
{
	switch (mType)
	{
		case DefaultTank:
			return Category::PlayerTank;

		default:
			return Category::EnemyTank;
	}
}

sf::FloatRect Tank::getBoundingRect() const
{
	return getWorldTransform().transformRect(mSprite.getGlobalBounds());
}

float Tank::getMaxSpeed() const
{
  return Table[mType].movementSpeed;
}

void Tank::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}

void Tank::updateCurrent(sf::Time dt, CommandQueue& commands)
{
  // Update enemy movement pattern; apply velocity
	updateMovementPattern(dt);
	Entity::updateCurrent(dt, commands);

  // Update texts
  updateTexts();
}

void Tank::updateMovementPattern(sf::Time dt)
{
  const std::vector<Direction> directions = Table[mType].directions;
  if (!directions.empty())
  {
		// Moved long enough in current direction: Change direction
		if (mTravelledDistance > directions[mDirectionIndex].distance)
    {
      mDirectionIndex = (mDirectionIndex + 1) % directions.size();
      mTravelledDistance = 0.f;
    }

    // Compute velocity from direction
    float radians = toRadian(directions[mDirectionIndex].angle + 90.f);
    float vx = getMaxSpeed() * std::cos(radians);
    float vy = getMaxSpeed() * std::sin(radians);
    setVelocity(vx, vy);
    mTravelledDistance += getMaxSpeed() * dt.asSeconds();
  }
}

void Tank::updateTexts()
{
  mHealthDisplay->setString(toString(getHitpoints()) + " HP");
  mHealthDisplay->setPosition(0.f, 50.f);
  mHealthDisplay->setRotation(-getRotation());
}