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
  return getWorldTransform().transformRect(mShape.getGlobalBounds());
}

void Block::drawCurrent(sf::RenderTarget& target, 
                        sf::RenderStates states) const
{
  target.draw(mShape, states);
}