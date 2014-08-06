#include <Tanks/Block.hpp>
#include <Tanks/DataTables.hpp>
#include <Tanks/Utility.hpp>
#include <Tanks/Foreach.hpp>

#include <SFML/Graphics/RenderTarget.hpp>


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
  // Give some room to slightly interact with the block without
  // collision detection
  sf::FloatRect rect = 
    getWorldTransform().transformRect(mShape.getGlobalBounds());
  /*const float extraRoom = 10.f;
  if (rect.width > extraRoom * 3.f)
  {
    rect.width -= (extraRoom * 2.f);
    rect.left += extraRoom;
  }
  if (rect.height > extraRoom * 3.f)
  {
    rect.height -= (extraRoom * 2.f);
    rect.top += extraRoom;
  }*/

  return rect;
}

void Block::drawCurrent(sf::RenderTarget& target, 
                        sf::RenderStates states) const
{
  target.draw(mShape, states);
}