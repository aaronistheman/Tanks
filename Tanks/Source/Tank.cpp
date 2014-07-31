#include <Tanks/Tank.hpp>
#include <Tanks/DataTables.hpp>
#include <Tanks/ResourceHolder.hpp>
#include <Tanks/Utility.hpp>
#include <Tanks/CommandQueue.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <cmath>
#include <math.h>


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
, mIsMarkedForRemoval(false)
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

bool Tank::isMarkedForRemoval() const
{
	return mIsMarkedForRemoval;
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
  // Entity has been destroyed: mark for removal
  if (isDestroyed())
  {
    mIsMarkedForRemoval = true;
    return;
  }

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
		if (mTravelledDistance >= directions[mDirectionIndex].distance &&
        mAmountRotation    >= std::abs(directions[mDirectionIndex].rotation))
    {
      mDirectionIndex = (mDirectionIndex + 1) % directions.size();
      mTravelledDistance = 0.f;
      mAmountRotation    = 0.f;
    }

    // Moved enough but haven't rotated enough: no more movement
    // Implicitly handles a direction for zero distance
    if (mTravelledDistance >= directions[mDirectionIndex].distance)
    {
      setVelocity(0.f, 0.f);
    }
    // Have not moved enough:
    else
    {
      // Compute velocity from direction
      float radians = toRadian(directions[mDirectionIndex].angle + 90.f);
      float vx = getMaxMovementSpeed() * std::cos(radians);
      float vy = getMaxMovementSpeed() * std::sin(radians);
      setVelocity(vx, vy);
      mTravelledDistance += getMaxMovementSpeed() * dt.asSeconds();
    }

    // Rotated enough but haven't moved enough: no more rotation
    // Implicitly handles a direction for zero rotation
    if (mAmountRotation >= std::abs(directions[mDirectionIndex].rotation))
    {
      setRotationOffset(0.f);
    }
    // Have not rotated enough:
    else
    {
      setRotationOffset(directions[mDirectionIndex].rotation);
      mAmountRotation += getMaxRotationSpeed() * dt.asSeconds();
    }
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
  
  // yOffsetAngle:
  float projectileAngle = toRadian(toTrigAngle(getRotation()));

  // Adjust projectile's offset according to tank's rotation
  // Each offset (x and y) has to be converted to an offset of the form
  // (x, y) based on the tank's rotation.
  // Use tank's angle to calculate angle-corrected yOffset:
  float x2 = std::cos(projectileAngle) * yOffset;
  float y2 = std::sin(projectileAngle) * yOffset;
  // Use xOffsetAngle to calculate angle-corrected xOffset:
  float xOffsetAngle = projectileAngle - toRadian(90);
  float x1 = std::cos(xOffsetAngle) * xOffset;
  float y1 = std::sin(xOffsetAngle) * xOffset;
  sf::Vector2f offset((x1 + x2) * getBoundingRect().width * -1,
                      (y1 + y2) * getBoundingRect().height);

  // Adjust projectlie's direction according to tank's rotation
  sf::Vector2f velocity(projectile->getMaxSpeed() * std::cos(projectileAngle), 
                        projectile->getMaxSpeed() * std::sin(projectileAngle) * -1);
  
  // Adjust projectile's rotation according to tank's rotation
  projectile->setRotation(getRotation());

  // Finally set projectile's position and velocity
  projectile->setPosition(getWorldPosition() + offset * -1.f);
  projectile->setVelocity(velocity);
  node.attachChild(std::move(projectile));
}

void Tank::updateTexts()
{
  mHealthDisplay->setString(toString(getHitpoints()) + " HP");
  mHealthDisplay->setPosition(0.f, 50.f);
  mHealthDisplay->setRotation(-getRotation());
}