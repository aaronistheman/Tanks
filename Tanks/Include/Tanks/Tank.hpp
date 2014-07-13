#ifndef TANKS_TANK_HPP
#define TANKS_TANK_HPP

#include <Tanks/Entity.hpp>
#include <Tanks/ResourceIdentifiers.hpp>

#include <SFML/Graphics/Sprite.hpp>

class Tank : public Entity
{
  public:
    enum Type
    {
      DefaultTank,
      TypeCount,
    };

  public:
    Tank(Type type, const TextureHolder& textures);

  private:
	  virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

  private:
    Type mType;
    sf::Sprite mSprite;
};

#endif // TANKS_TANK_HPP