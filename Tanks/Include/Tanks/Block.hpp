#ifndef TANKS_BLOCK_HPP
#define TANKS_BLOCK_HPP

#include <Tanks/SceneNode.hpp>

#include <SFML/Graphics/RectangleShape.hpp>


// The blocks contained in this node act as walls
class Block : public SceneNode
{
  public:
    enum Type
    {
      Indestructible,
      Destructible,
      TypeCount
    };

  public:
                            Block(Block::Type type,
                                  sf::Vector2f size);

    virtual unsigned int    getCategory() const;
    virtual sf::FloatRect   getBoundingRect() const;
    
    void        repair(int points);
    void        damage(int points);
    void        destroy();
    int         getHitpoints() const;
    bool        isDestroyed() const;


	private:
		virtual void			drawCurrent(sf::RenderTarget& target, 
                                  sf::RenderStates states) const;


  private:
    Block::Type           mType;
    sf::RectangleShape    mShape;
    int                   mHitpoints;
};

#endif // TANKS_BLOCK_HPP