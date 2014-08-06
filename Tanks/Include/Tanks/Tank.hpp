#ifndef TANKS_TANK_HPP
#define TANKS_TANK_HPP

#include <Tanks/Entity.hpp>
#include <Tanks/Command.hpp>
#include <Tanks/ResourceIdentifiers.hpp>
#include <Tanks/TextNode.hpp>
#include <Tanks/Projectile.hpp>

#include <SFML/Graphics/Sprite.hpp>


class Tank : public Entity
{
  public:
    enum Type
    {
      DefaultTank,
      EnemyTank1,
      EnemyTank2,
      TypeCount
    };

  public:
    Tank(Type type, const TextureHolder& textures, const FontHolder& fonts);
    
    void                  setRotationOffset(float angle);
    void                  rotate(float offset);
    float                 getRotationOffset() const;

    virtual unsigned int	  getCategory() const;
		virtual sf::FloatRect	  getBoundingRect() const;
    virtual bool          isMarkedForRemoval() const;
    bool                  isCollidingWithTank() const;
    bool                  isCollidingWithBlock() const;
    bool                  isAllied() const;
    bool                  isMovingTowardsPlayer() const;
    float                 getMaxMovementSpeed() const;
    float                 getMaxRotationSpeed() const;

    void                  setIsCollidingWithTank(bool flag);
    void                  setIsCollidingWithBlock(bool flag);
    void                  setIntersection(sf::FloatRect rect);
    void                  fire();


  private:
	  virtual void    drawCurrent(sf::RenderTarget& target, 
                                sf::RenderStates states) const;
    virtual void    updateCurrent(sf::Time dt, CommandQueue& commands);
    void         updateMovementPattern(sf::Time dt);
    void         checkProjectileLaunch(sf::Time dt, CommandQueue& commands);

    void         createBullets(SceneNode& node, const TextureHolder& textures) const;
    void         createProjectile(SceneNode& node,
                                  Projectile::Type type,
                                  sf::Vector2f offset,
                                  const TextureHolder& textures) const;

    void            updateTexts();

  private:
    Type            mType;
    sf::Sprite      mSprite;
    float           mRotationOffset; // basically a rate of rotation
    
    Command         mFireCommand;
    sf::Time        mFireCountdown;
    bool            mIsFiring;
    bool            mIsMarkedForRemoval;
    bool            mIsCollidingWithTank;
    bool            mIsCollidingWithBlock;
    sf::FloatRect   mIntersection;

    int             mFireRateLevel;

    float           mTravelledDistance;
    float           mAmountRotation;
    std::size_t     mDirectionIndex;

    TextNode*       mHealthDisplay;
    SceneNode*      mBulletEmitter; // blank SceneNode used for positioning
                                    // bullets according to offsets
};

#endif // TANKS_TANK_HPP