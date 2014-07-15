#include <Tanks/Entity.hpp>

void Entity::setVelocity(sf::Vector2f velocity)
{
	mVelocity = velocity;
}

void Entity::setVelocity(float vx, float vy)
{
	mVelocity.x = vx;
	mVelocity.y = vy;
}

sf::Vector2f Entity::getVelocity() const
{
	return mVelocity;
}

void Entity::accelerate(sf::Vector2f velocity)
{
	mVelocity += velocity;
}

void Entity::accelerate(float vx, float vy)
{
	mVelocity.x += vx;
	mVelocity.y += vy;
}

void Entity::setRotationOffset(float angle)
{
  mRotationOffset = angle;
}

void Entity::rotate(float offset)
{
  mRotationOffset += offset;
}

float Entity::getRotationOffset() const
{
  return mRotationOffset;
}

void Entity::updateCurrent(sf::Time dt)
{	
	move(mVelocity * dt.asSeconds());
  sf::Transformable::rotate(mRotationOffset * dt.asSeconds());
}