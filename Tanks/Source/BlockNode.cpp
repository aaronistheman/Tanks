#include <Tanks/BlockNode.hpp>
#include <Tanks/DataTables.hpp>

#include <functional>


namespace
{
  const std::vector<BlockData> Table = initializeBlockData();
}

void BlockNode::addBlock(sf::Vector2f size, sf::Vector2f position)
{
  Block block;
  block.size = size;
  block.position = position;
  block.color = Table[mType].color;
  block.hitpoints = Table[mType].hitpoints;

  mBlocks.push_front(block);
}

Block::Type BlockNode::getBlockType() const
{
  return mType;
}

unsigned int BlockNode::getCategory() const
{
  return Category::BlockSystem;
}

void BlockNode::updateCurrent(sf::Time dt, CommandQueue&)
{
  if (!mBlocks.empty())
  {
    mBlocks.remove_if( [] (Block b) { return b.hitpoints <= 0; } );
  }

  mNeedsVertexUpdate = true;
}