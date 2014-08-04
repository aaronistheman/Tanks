#include <Tanks/BlockNode.hpp>
#include <Tanks/DataTables.hpp>
#include <Tanks/Foreach.hpp>

#include <SFML/Graphics/RenderTarget.hpp>


namespace
{
  const std::vector<BlockData> Table = initializeBlockData();
}

BlockNode::BlockNode(Block::Type type)
  : SceneNode()
  , mBlocks()
  , mType(type)
  , mVertexArray(sf::Quads)
  , mNeedsVertexUpdate(true)
{
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
  // No reason to update indestructible blocks
  if (mType == Block::Destructible)
  {
    if (!mBlocks.empty())
    {
      mBlocks.remove_if( [] (Block b) { return b.hitpoints <= 0; } );
    }

    mNeedsVertexUpdate = true;
  }
}

void BlockNode::drawCurrent(sf::RenderTarget& target, 
                            sf::RenderStates states) const
{
  if (mNeedsVertexUpdate)
  {
    computeVertices();
    mNeedsVertexUpdate = false;
  }

  target.draw(mVertexArray, states);
}

void BlockNode::addVertex(float worldX, float worldY, 
                          const sf::Color& color) const
{
  sf::Vertex vertex;
  vertex.position = sf::Vector2f(worldX, worldY);
  vertex.color = color;

  mVertexArray.append(vertex);
}

void BlockNode::computeVertices() const
{
  FOREACH(const Block& block, mBlocks)
  {
    sf::Vector2f size = block.size;
    sf::Vector2f half = size / 2.f;

    sf::Vector2f pos = block.position;
    sf::Color c = block.color;

    float ratio = block.hitpoints / Table[mType].hitpoints;
    c.a = static_cast<sf::Uint8>(255 * std::max(ratio, 0.f));

    addVertex(pos.x - half.x, pos.y - half.y, c);
    addVertex(pos.x + half.x, pos.y - half.y, c);
    addVertex(pos.x + half.x, pos.y + half.y, c);
    addVertex(pos.x - half.x, pos.y + half.y, c);
  }
}