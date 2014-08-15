#include <Tanks/Block.hpp>
#include <Tanks/DataTables.hpp>
#include <Tanks/Utility.hpp>
#include <Tanks/Foreach.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

#include <cassert>


namespace
{
  const std::vector<BlockData> Table = initializeBlockData();
}

Block::Block(Block::Type type,
             sf::Vector2f size)
 : mType(type)
 , mShape()
 , mHitpoints(Table[mType].hitpoints)
{
  mShape.setSize(size);
  mShape.setFillColor(Table[mType].color);

  centerOrigin(mShape);
}

unsigned int Block::getCategory() const
{
  if (mType == Indestructible)
    return Category::IndestructibleBlock;
  else
    return Category::DestructibleBlock;
}

sf::FloatRect Block::getBoundingRect() const
{
  return getWorldTransform().transformRect(mShape.getGlobalBounds());
}

Block::Type Block::getType() const
{
  return mType;
}

sf::Vector2f Block::getSize() const
{
  return mShape.getSize();
}

void Block::repair(int points)
{
  assert(points > 0);

  mHitpoints += points;
}

void Block::damage(int points)
{
  assert(points > 0);
  
  if (mType == Block::Destructible)
    mHitpoints -= points;
}

void Block::destroy()
{
  mHitpoints = 0;
}

int Block::getHitpoints() const
{
  return mHitpoints;
}

bool Block::isDestroyed() const
{
  return mHitpoints <= 0;
}

int Block::getMaxHitpoints(Type type)
{
  return Table[type].hitpoints;
}

void Block::drawCurrent(sf::RenderTarget& target, 
                        sf::RenderStates states) const
{
  target.draw(mShape, states);
}