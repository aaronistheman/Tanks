#ifndef TANKS_TANK_HPP
#define TANKS_TANK_HPP

#include <Tanks/Entity.hpp>
#include <Tanks/Command.hpp>
#include <Tanks/ResourceIdentifiers.hpp>
#include <Tanks/TextNode.hpp>

#include <SFML/Graphics/Sprite.hpp>


class Tank : public Entity
{
  public:
    enum Type
    {
      DefaultTank,
      EnemyTank,
      TypeCount
    };

  public:
    Tank(Type type, const TextureHolder& textures, const FontHolder& fonts);
    
    virtual unsigned int	getCategory() const;
		virtual sf::FloatRect	getBoundingRect() const;
    float                 getMaxMovementSpeed() const;
    float                 getMaxRotationSpeed() const;

  private:
	  virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void updateCurrent(sf::Time dt, CommandQueue& commands);
    void         updateMovementPattern(sf::Time dt);

    void         updateTexts();

  private:
    Type            mType;
    sf::Sprite      mSprite;

    float           mTravelledDistance;
    float           mAmountRotation;
    std::size_t     mDirectionIndex;
    TextNode*       mHealthDisplay;
};

#endif // TANKS_TANK_HPP