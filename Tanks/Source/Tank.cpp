#include <Tanks/Tank.hpp>
#include <Tanks/DataTables.hpp>
#include <Tanks/ResourceHolder.hpp>
#include <Tanks/Utility.hpp>
#include <Tanks/CommandQueue.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <cmath>


namespace
{
  const std::vector<TankData> Table = initializeTankData();
}

Tank::Tank(Type type, const TextureHolder& textures, const FontHolder& fonts)
: Entity(Table[type].hitpoints)
, mType(type)
, mSprite(textures.get(Table[type].texture))
, mRotationOffset(0.f)
, mFireCommand()
, mFireCountdown(sf::Time::Zero)
, mIsFiring(false)
, mFireRateLevel(1)
, mTravelledDistance(0.f)
, mAmountRotation(0.f)
, mDirectionIndex(0)
, mHealthDisplay(nullptr)
{
	centerOrigin(mSprite);

  mFireCommand.category = Category::SceneAirLayer;
  mFireCommand.action   = [this, &textures] (SceneNode& node, sf::Time)
  {
    createBullets(node, textures);
  };

  std::unique_ptr<TextNode> healthDisplay(new TextNode(fonts, ""));
  mHealthDisplay = healthDisplay.get();
  attachChild(std::move(healthDisplay));

  updateTexts();
}

void Tank::setRotationOffset(float angle)
{
  mRotationOffset = angle;
}

void Tank::rotate(float offset)
{
  mRotationOffset += offset;
}

float Tank::getRotationOffset() const
{
  return mRotationOffset;
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

bool Tank::isAllied() const
{
  return mType == Type::DefaultTank;
}

float Tank::getMaxMovementSpeed() const
{
  return Table[mType].movementSpeed;
}

float Tank::getMaxRotationSpeed() const
{
  return Table[mType].rotationSpeed;
}

void Tank::fire()
{
	// Only ships with fire interval != 0 are able to fire
	if (Table[mType].fireInterval != sf::Time::Zero)
		mIsFiring = true;
}

void Tank::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}

void Tank::updateCurrent(sf::Time dt, CommandQueue& commands)
{
  // Check if bullets are fired
  checkProjectileLaunch(dt, commands);

  // Update enemy movement pattern; apply velocity
	updateMovementPattern(dt);
	Entity::updateCurrent(dt, commands);
  sf::Transformable::rotate(mRotationOffset * dt.asSeconds());

  // Update texts
  updateTexts();
}

void Tank::updateMovementPattern(sf::Time dt)
{
  const std::vector<Direction> directions = Table[mType].directions;
  if (!directions.empty())
  {
		// Moved and rotated enough in current direction:
    // Change direction
		if (mTravelledDistance > directions[mDirectionIndex].distance &&
        mAmountRotation    > directions[mDirectionIndex].rotation)
    {
      mDirectionIndex = (mDirectionIndex + 1) % directions.size();
      mTravelledDistance = 0.f;
      mAmountRotation    = 0.f;
    }

    // Compute velocity from direction
    float radians = toRadian(directions[mDirectionIndex].angle + 90.f);
    float vx = getMaxMovementSpeed() * std::cos(radians);
    float vy = getMaxMovementSpeed() * std::sin(radians);
    setVelocity(vx, vy);
    mTravelledDistance += getMaxMovementSpeed() * dt.asSeconds();

    // Rotate (in degrees)
    setRotationOffset(directions[mDirectionIndex].rotation);
    mAmountRotation += getMaxRotationSpeed() * dt.asSeconds();
  }
}

void Tank::checkProjectileLaunch(sf::Time dt, CommandQueue& commands)
{
  // Enemies try to fire all the time
	if (!isAllied())
		fire();

  if (mIsFiring && mFireCountdown <= sf::Time::Zero)
  {
    commands.push(mFireCommand);
    mFireCountdown += Table[mType].fireInterval / (mFireRateLevel + 1.f);
    mIsFiring = false;
  }
  else if (mFireCountdown > sf::Time::Zero)
  {
    mFireCountdown -= dt;
    mIsFiring = false;
  }
}

void Tank::createBullets(SceneNode& node, 
                         const TextureHolder& textures) const
{
  Projectile::Type type = isAllied() 
    ? Projectile::AlliedBullet : Projectile::EnemyBullet;
  createProjectile(node, type, 0.0f, 0.5f, textures);
}

void Tank::createProjectile(SceneNode& node,
                            Projectile::Type type,
                            float xOffset,
                            float yOffset,
                            const TextureHolder& textures) const
{
  std::unique_ptr<Projectile> projectile(new Projectile(type, textures));

  sf::Vector2f offset(xOffset * mSprite.getGlobalBounds().width,
                      yOffset * mSprite.getGlobalBounds().height);
  sf::Vector2f velocity(0, projectile->getMaxSpeed());

  float sign = isAllied() ? -1.f : +1.f;
  projectile->setPosition(getWorldPosition() + offset * sign);
  projectile->setVelocity(velocity * sign);
  node.attachChild(std::move(projectile));
}

void Tank::updateTexts()
{
  mHealthDisplay->setString(toString(getHitpoints()) + " HP");
  mHealthDisplay->setPosition(0.f, 50.f);
  mHealthDisplay->setRotation(-getRotation());
}