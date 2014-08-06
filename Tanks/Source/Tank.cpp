#include <Tanks/Tank.hpp>
#include <Tanks/DataTables.hpp>
#include <Tanks/ResourceHolder.hpp>
#include <Tanks/Utility.hpp>
#include <Tanks/CommandQueue.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <cmath>
#include <math.h>

#include <iostream>


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
, mIsCollidingWithTank(false)
, mIsCollidingWithBlock(false)
, mIntersectionWithTank(sf::FloatRect())
, mIntersectionWithBlock(sf::FloatRect())
, mFireRateLevel(1)
, mTravelledDistance(0.f)
, mAmountRotation(0.f)
, mDirectionIndex(0)
, mHealthDisplay(nullptr)
, mBulletEmitter(nullptr)
{
	centerOrigin(mSprite);

  mFireCommand.category = Category::SceneGroundLayer;
  mFireCommand.action   = [this, &textures] (SceneNode& node, sf::Time)
  {
    createBullets(node, textures);
  };

  std::unique_ptr<TextNode> healthDisplay(new TextNode(fonts, ""));
  mHealthDisplay = healthDisplay.get();
  attachChild(std::move(healthDisplay));

  updateTexts();

  std::unique_ptr<SceneNode> bulletEmitter(new SceneNode());
  mBulletEmitter = bulletEmitter.get();
  attachChild(std::move(bulletEmitter));
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

    case EnemyTank1:
      return Category::EnemyTank1;

    case EnemyTank2:
      return Category::EnemyTank2;

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

bool Tank::isCollidingWithTank() const
{
  return mIsCollidingWithTank;
}

bool Tank::isCollidingWithBlock() const
{
  return mIsCollidingWithBlock;
}

bool Tank::isAllied() const
{
  return mType == Type::DefaultTank;
}

bool Tank::isMovingTowardsPlayer() const
{
  return mType == Type::EnemyTank2;
}

float Tank::getMaxMovementSpeed() const
{
  return Table[mType].movementSpeed;
}

float Tank::getMaxRotationSpeed() const
{
  return Table[mType].rotationSpeed;
}

void Tank::setIsCollidingWithTank(bool flag, sf::FloatRect intersection)
{
  mIsCollidingWithTank = flag;
  mIntersectionWithTank = intersection;
}

void Tank::setIsCollidingWithBlock(bool flag, sf::FloatRect intersection)
{
  mIsCollidingWithBlock = flag;
  mIntersectionWithBlock = intersection;
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

  // Update enemy movement pattern
	updateMovementPattern(dt);
  
  // Handle collisions with tanks and blocks
  handleCollisionWithTank();
  if (mType == DefaultTank)
    std::cout << mIsCollidingWithBlock << '\n';
  handleCollisionWithBlock();

  // Apply velocity and rotation
	Entity::updateCurrent(dt, commands);
  sf::Transformable::rotate(mRotationOffset * dt.asSeconds());

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

void Tank::handleCollisionWithTank()
{
  // React to collision with other tank;
  // use the intersection to move the tank so as to remove that
  // intersection
  if (mIsCollidingWithTank)
  {
    sf::Vector2f position = getPosition();
    
    // Edit velocity
    sf::Vector2f velocity;
    velocity.x = getMaxMovementSpeed() * 
                 (position.x > mIntersectionWithTank.left) ? 1.f : -1.f;
    velocity.y = getMaxMovementSpeed() *
                 (position.y > mIntersectionWithTank.top) ? 1.f : -1.f;
    setVelocity(velocity);
    
    // Edit position
    sf::Vector2f positionOffset;
    positionOffset.x = mIntersectionWithTank.width * 
                 (position.x > mIntersectionWithTank.left) ? 1.f : -1.f;
    positionOffset.y = mIntersectionWithTank.height *
                 (position.y > mIntersectionWithTank.top) ? 1.f : -1.f;
    setPosition(position + positionOffset);
    
    setIsCollidingWithTank(false);
  }
}

void Tank::handleCollisionWithBlock()
{
  // React to collision with block;
  // use the intersection to cancel the tank's movement in whichever
  // direction would put it through the block;
  // prevent rotation
  if (mIsCollidingWithBlock)
  {
    // sf::Vector2f position = getPosition();
    // sf::Vector2f velocity = getVelocity();
    // sf::FloatRect boundingRect = getBoundingRect();
    
    /*if (boundingRect.left == mIntersectionWithBlock.left && velocity.x < 0.f)
      // Cancel leftward movement
      velocity.x = 0.f;
    else if ((boundingRect.left + boundingRect.width) == 
             (mIntersectionWithBlock.left + mIntersectionWithBlock.width) && velocity.x > 0.f)
      // Cancel rightward movement
      velocity.x = 0.f;

    if (boundingRect.top == mIntersectionWithBlock.top && velocity.y < 0.f)
      // Cancel upward movement
      velocity.y = 0.f;
    else if ((boundingRect.top + boundingRect.height) ==
             (mIntersectionWithBlock.top + mIntersectionWithBlock.height) && velocity.y > 0.f)
      // Cancel downward movement
      velocity.y = 0.f;*/

    // Cancel leftward movement
    // position.x = std::max(position.x, mIntersectionWithBlock.left + boundingRect.width);
    // Cancel rightwrd movement
    // position.x = std::min(position.x, mIntersectionWithBlock.left);
    // Cancel upward movement
    // position.y = std::max(position.y, mIntersectionWithBlock

    // setPosition(position);
    // setVelocity(velocity);
    
    sf::Vector2f position = getPosition();
    
    // Edit velocity
    sf::Vector2f velocity;
    velocity.x = getMaxMovementSpeed() * 
                 (position.x > mIntersectionWithBlock.left) ? 1.f : -1.f;
    velocity.y = getMaxMovementSpeed() *
                 (position.y > mIntersectionWithBlock.top) ? 1.f : -1.f;
    setVelocity(velocity);
    
    // Edit position
    sf::Vector2f positionOffset;
    positionOffset.x = mIntersectionWithBlock.width * 
                 (position.x > mIntersectionWithBlock.left) ? 1.f : -1.f;
    positionOffset.y = mIntersectionWithBlock.height *
                 (position.y > mIntersectionWithBlock.top) ? 1.f : -1.f;
    setPosition(position + positionOffset);
    
    setIsCollidingWithBlock(false);
  }
}

void Tank::createBullets(SceneNode& node, 
                         const TextureHolder& textures) const
{
  Projectile::Type type = isAllied() 
    ? Projectile::AlliedBullet : Projectile::EnemyBullet;
  createProjectile(node, type, Table[mType].bulletOffset, textures);
}

void Tank::createProjectile(SceneNode& node,
                            Projectile::Type type,
                            sf::Vector2f offset,
                            const TextureHolder& textures) const
{
  std::unique_ptr<Projectile> projectile(new Projectile(type, textures));

  // Adjust projectlie's direction/velocity according to tank's rotation;
  // create projectileAngle because trig functions need angle in radians
  float projectileAngle = toRadian(toTrigAngle(getRotation()));
  sf::Vector2f velocity(
    projectile->getMaxSpeed() * std::cos(projectileAngle), 
    projectile->getMaxSpeed() * std::sin(projectileAngle) * -1);
  
  // Adjust projectile's rotation according to tank's rotation
  projectile->setRotation(getRotation());

  // Finally set projectile's position and velocity;
  // negate SFML's upside down y-axis
  mBulletEmitter->setPosition(offset.x, -offset.y);
  projectile->setPosition(mBulletEmitter->getWorldPosition());
  projectile->setVelocity(velocity);
  node.attachChild(std::move(projectile));
}

void Tank::updateTexts()
{
  mHealthDisplay->setString(toString(getHitpoints()) + " HP");
  mHealthDisplay->setPosition(0.f, 50.f);
  mHealthDisplay->setRotation(-getRotation());
}