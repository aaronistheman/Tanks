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
, mCanMoveLeft(true)
, mCanMoveRight(true)
, mCanMoveUp(true)
, mCanMoveDown(true)
, mCanRotateCounterclockwise(true)
, mCanRotateClockwise(true)
, mFireCommand()
, mFireCountdown(sf::Time::Zero)
, mIsFiring(false)
, mIsMarkedForRemoval(false)
, mCollisionsWithTank()
, mCollisionsWithBlock()
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

Tank::Type Tank::getType() const
{
  return mType;
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

int Tank::getMaxHitpoints() const
{
  return Table[mType].hitpoints;
}

int Tank::getMaxHitpoints(Type type)
{
  return Table[type].hitpoints;
}

void Tank::addCollisionWithTank(sf::FloatRect intersection)
{
  mCollisionsWithTank.push_back(CollisionData(intersection));
}

void Tank::addCollisionWithBlock(sf::FloatRect intersection)
{
  mCollisionsWithBlock.push_back(CollisionData(intersection));
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
  
  // Handle intersections between tanks and blocks
  handleIntersections();

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

    // Moved enough but haven't rotated enough: no more movement;
    // Implicitly handles a direction for zero distance
    if (mTravelledDistance >= directions[mDirectionIndex].distance)
    {
      setVelocity(0.f, 0.f);
    }
    // Have not moved enough:
    else
    {
      // Compute velocity from direction; indirectly handles the speed
      // reduction necessary in diagonal movement
      float radians = toRadian(directions[mDirectionIndex].angle + 90.f);
      float vx = getMaxMovementSpeed() * std::cos(radians);
      float vy = getMaxMovementSpeed() * std::sin(radians);
      setVelocity(vx, vy);
      mTravelledDistance += getMaxMovementSpeed() * dt.asSeconds();
    }

    // Rotated enough but haven't moved enough: no more rotation;
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

void Tank::handleIntersections()
{
  // Remove all movement restrictions from previous frame
  mCanMoveLeft = true;
  mCanMoveRight = true;
  mCanMoveUp = true;
  mCanMoveDown = true;
  mCanRotateCounterclockwise = true;
  mCanRotateClockwise = true;

  // Update movement restrictions (if necessary)
  handleIntersectionsWithTank();
  handleIntersectionsWithBlock();

  // Adapt movement based on movement restrictions
  adaptVelocityBasedOnCollisions();
  adaptRotationBasedOnCollisions();
}

void Tank::handleIntersectionsWithTank()
{
  // React to collision with other tank;
  // use the intersection to move the tank so as to remove that
  // intersection
   
  while (!mCollisionsWithTank.empty())
  {
    sf::FloatRect boundingRect = getBoundingRect();
    sf::FloatRect intersection = mCollisionsWithTank.back().intersection;

    // Check leftward and rightward movement
    if ((boundingRect.top + boundingRect.height) > intersection.top
      && boundingRect.top < (intersection.top + intersection.height)
      && intersection.height > intersection.width)
    {
      if ((boundingRect.left == intersection.left) || !mCanMoveLeft)
        mCanMoveLeft = false;
      if (((boundingRect.left + boundingRect.width) ==
        (intersection.left + intersection.width)) || !mCanMoveRight)
        mCanMoveRight = false;
    }
    
    // Check upward and downward movement
    if ((boundingRect.left + boundingRect.width) > intersection.left
      && boundingRect.left < (intersection.left + intersection.width)
      && intersection.width > intersection.height)
    {
      if ((boundingRect.top == intersection.top) || !mCanMoveUp)
        mCanMoveUp = false;
      if (((boundingRect.top + boundingRect.height) ==
        (intersection.top + intersection.height)) || !mCanMoveDown)
        mCanMoveDown = false;
    }

    // Check rotation
    float rotation = getRotation();
    if ((180.f > rotation && rotation > 90.f) ||
        (360.f > rotation && rotation > 270.f))
    {
      if (!mCanMoveLeft || !mCanMoveRight)
        mCanRotateCounterclockwise = false;
      if (!mCanMoveUp || !mCanMoveDown)
        mCanRotateClockwise = false;
    }
    else if ((90.f > rotation && rotation > 0.f) ||
             (270.f > rotation && rotation > 180.f))
    {
      if (!mCanMoveLeft || !mCanMoveRight)
        mCanRotateClockwise = false;
      if (!mCanMoveUp || !mCanMoveDown)
        mCanRotateCounterclockwise = false;
    }

    mCollisionsWithTank.pop_back();
  }
}

void Tank::handleIntersectionsWithBlock()
{
  // React to collision with block;
  // use the intersection to move the tank so as to remove that
  // intersection
  
  while (!mCollisionsWithBlock.empty())
  {
    sf::FloatRect boundingRect = getBoundingRect();
    sf::FloatRect intersection = mCollisionsWithBlock.back().intersection;

    // Check leftward and rightward movement
    if ((boundingRect.top + boundingRect.height) > intersection.top
      && boundingRect.top < (intersection.top + intersection.height)
      && intersection.height > intersection.width)
    {
      if ((boundingRect.left == intersection.left) || !mCanMoveLeft)
        mCanMoveLeft = false;
      if (((boundingRect.left + boundingRect.width) ==
        (intersection.left + intersection.width)) || !mCanMoveRight)
        mCanMoveRight = false;
    }
    
    // Check upward and downward movement
    if ((boundingRect.left + boundingRect.width) > intersection.left
      && boundingRect.left < (intersection.left + intersection.width)
      && intersection.width > intersection.height)
    {
      if ((boundingRect.top == intersection.top) || !mCanMoveUp)
        mCanMoveUp = false;
      if (((boundingRect.top + boundingRect.height) ==
        (intersection.top + intersection.height)) || !mCanMoveDown)
        mCanMoveDown = false;
    }

    // Check rotation
    float rotation = getRotation();
    if ((180.f > rotation && rotation > 90.f) ||
        (360.f > rotation && rotation > 270.f))
    {
      if (!mCanMoveLeft || !mCanMoveRight)
        mCanRotateCounterclockwise = false;
      if (!mCanMoveUp || !mCanMoveDown)
        mCanRotateClockwise = false;
    }
    else if ((90.f > rotation && rotation > 0.f) ||
             (270.f > rotation && rotation > 180.f))
    {
      if (!mCanMoveLeft || !mCanMoveRight)
        mCanRotateClockwise = false;
      if (!mCanMoveUp || !mCanMoveDown)
        mCanRotateCounterclockwise = false;
    }

    mCollisionsWithBlock.pop_back();
  }
}

void Tank::adaptVelocityBasedOnCollisions()
{
  // Edit velocity based on where tank can and cannot move (if necessary)
  sf::Vector2f velocity = getVelocity();
  if (!mCanMoveLeft && velocity.x < 0.f)
    velocity.x = 0.f;
  else if (!mCanMoveRight && velocity.x > 0.f)
    velocity.x = 0.f;
  if (!mCanMoveUp && velocity.y < 0.f)
    velocity.y = 0.f;
  else if (!mCanMoveDown && velocity.y > 0.f)
    velocity.y = 0.f;
  setVelocity(velocity);
}

void Tank::adaptRotationBasedOnCollisions()
{
  // Edit rotation based on which way the tank can and cannot rotate (if
  // necessary)
  if ((!mCanRotateCounterclockwise && mRotationOffset < 0.f) ||
      (!mCanRotateClockwise && mRotationOffset > 0.f))
    mRotationOffset = 0.f;
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