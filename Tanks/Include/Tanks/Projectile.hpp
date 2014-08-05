#ifndef TANKS_PROJECTILE_HPP
#define TANKS_PROJECTILE_HPP

#include <Tanks/Entity.hpp>
#include <Tanks/ResourceIdentifiers.hpp>

#include <SFML/Graphics/Sprite.hpp>


class Projectile : public Entity
{
  public:
    enum Type
    {
      AlliedBullet,
      EnemyBullet,
      Missile,
      TypeCount
    };

  public:
    Projectile(Type type, const TextureHolder& textures);

    virtual unsigned int getCategory() const;
    virtual sf::FloatRect getBoundingRect() const;
    float getMaxSpeed() const;
    int  getDamage() const;


  private:
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

  private:
    Type mType;
    sf::Sprite mSprite;
};

#endif // TANKS_PROJECTILE_HPP