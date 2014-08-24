#include <Tanks/Quadtree.hpp>

#include <SFML/Graphics/RectangleShape.hpp>


Quadtree::Quadtree(int level, sf::FloatRect bounds)
  : mMaxObjects(6)
  , mMaxLevels(3)
  , mLevel(level)
  , mObjects()
  , mBounds(bounds)
  , mTreeNodes()
{
}

void Quadtree::clear()
{
  mObjects.clear();

  for (int i = 0; i < mTreeNodes.size(); ++i)
  {
    if (mTreeNodes[i] != nullptr)
    {
      // Recursively clear all objects from all nodes
      mTreeNodes[i]->clear();
      mTreeNodes[i] = nullptr;
    }
  }
}

// Splits the node into 4 subnodes
void Quadtree::split()
{
  float subWidth = mBounds.width / 2.f;
  float subHeight = mBounds.height / 2.f;
  float x = mBounds.left;
  float y = mBounds.top;
  int newLevel = mLevel + 1;

  mTreeNodes[0] = new Quadtree(newLevel, 
    sf::FloatRect(x + subWidth, y, subWidth, subHeight));
  mTreeNodes[1] = new Quadtree(newLevel,
    sf::FloatRect(x, y, subWidth, subHeight));
  mTreeNodes[2] = new Quadtree(newLevel,
    sf::FloatRect(x, y + subHeight, subWidth, subHeight));
  mTreeNodes[3] = new Quadtree(newLevel,
    sf::FloatRect(x + subWidth, y + subHeight, subWidth, subHeight));
}

// Determine which node the object belongs to.
// -1 means object cannot completely fit within a child node
// and is part of the parent node.
int Quadtree::getIndex(const SceneNode& sceneNode) const
{
  int index = -1;
  double verticalMidpoint = mBounds.left + (mBounds.width / 2);
  double horizontalMidpoint = mBounds.top + (mBounds.height / 2);

  sf::FloatRect rect = sceneNode.getBoundingRect();

  // Object can completely fit within the top quadrants
  bool topQuadrant = (rect.top + rect.height) < horizontalMidpoint;
  // Object can completely fit within the bottom quadrants
  bool bottomQuadrant = rect.top > horizontalMidpoint;

  // Object can completely fit within the left quadrants
  if ((rect.left + rect.width) < verticalMidpoint)
  {
    if (topQuadrant)
      index = 1;
    else if (bottomQuadrant)
      index = 2;
  }
  // Object can completely fit within the right quadrants
  else if (rect.left > verticalMidpoint)
  {
    if (topQuadrant)
      index = 0;
    else if (bottomQuadrant)
      index = 3;
  }
  
  return index;
}

void Quadtree::insert(SceneNode& sceneNode)
{
  // If this tree already has nodes: insert it into its
  // correct node
  if (mTreeNodes[0] != nullptr)
  {
    int index = getIndex(sceneNode);

    if (index != -1)
    {
      mTreeNodes[index]->insert(sceneNode);
      return;
    }
  }

  // Place sceneNode in parent node
  mObjects.push_back(&sceneNode);

  // Split and redetermine which node to place objects in if necessary
  if (mObjects.size() > mMaxObjects && mLevel < mMaxLevels)
  {
    if (mTreeNodes[0] == nullptr)
      split();

    for (auto itr = mObjects.begin(); itr != mObjects.end(); )
    {
      int index = getIndex(**itr);
      if (index != -1)
      {
        mTreeNodes[index]->insert(**itr);
        itr = mObjects.erase(itr);
      }
      else
        // Object does not entirely fit in any one child node;
        // keep it in parent node
        ++itr;
    }
  }
}

// Return all scene nodes that could collide with the given scene node
std::vector<SceneNode*> Quadtree::retrieve(const SceneNode& sceneNode) const
{
  std::vector<SceneNode*> returnObjects;

  // Add the scene nodes in the object's child quadtree
  int index = getIndex(sceneNode);
  if (index != -1 && mTreeNodes[0] != nullptr)
    returnObjects = mTreeNodes[index]->retrieve(sceneNode);

  // Add the scene nodes in the parent node as well
  for (auto itr = mObjects.begin(); itr != mObjects.end(); ++itr)
    returnObjects.push_back(*itr);

  return returnObjects;
}

void Quadtree::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  drawBounds(target);

  // If there are tree nodes to draw, draw them
  if (mTreeNodes[0] != nullptr)
    for (int i = 0; i < mTreeNodes.size(); ++i)
      mTreeNodes[i]->draw(target, states);
}

void Quadtree::drawBounds(sf::RenderTarget& target) const
{
  sf::RectangleShape bounds;
  bounds.setFillColor(sf::Color::Transparent);
  bounds.setOutlineColor(sf::Color::Green);
  bounds.setOutlineThickness(1.f);
  bounds.setPosition(mBounds.left, mBounds.top);
  bounds.setSize(sf::Vector2f(mBounds.width, mBounds.height));
  target.draw(bounds);
}

sf::FloatRect Quadtree::getBounds() const
{
  return mBounds;
}

void Quadtree::setBounds(const sf::FloatRect& rect)
{
  mBounds = rect;
}