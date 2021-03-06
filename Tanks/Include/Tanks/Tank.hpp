#ifndef TANKS_TANK_HPP
#define TANKS_TANK_HPP

#include <Tanks/Entity.hpp>
#include <Tanks/Command.hpp>
#include <Tanks/ResourceIdentifiers.hpp>
#include <Tanks/TextNode.hpp>
#include <Tanks/Projectile.hpp>
#include <Tanks/Direction.hpp>

#include <SFML/Graphics/Sprite.hpp>

#include <vector>


class Tank : public Entity
{
  public:
    enum Type
    {
      Hero,
      Dummy,
      Hunting1,
      Hunting2,
      Guarding1,
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
    Type                  getType() const;
    bool                  isAllied() const;
    bool                  isMovingTowardsPlayer() const;
    float                 getMaxMovementSpeed() const;
    float                 getMaxRotationSpeed() const;
    static int            getMaxHitpoints(Type type);

    float                 getTravelledDistance() const;
    void                  setTravelledDistance(float distance);
    float                 getAmountRotated() const;
    void                  setAmountRotated(float rotation);
    std::size_t           getDirectionIndex() const;
    void                  setDirectionIndex(std::size_t index);

    float                 getGuardingPathLength() const;
    void                  setGuardingPathLength(float length);
    float                 getGuardingAngle() const;
    void                  setGuardingAngle(float angle);

    void                  addCollisionWithTank(sf::FloatRect intersection);
    void                  addCollisionWithBlock(sf::FloatRect intersection);
    void                  fire();


  private:
	  virtual void    drawCurrent(sf::RenderTarget& target, 
                                sf::RenderStates states) const;
    virtual void    updateCurrent(sf::Time dt, CommandQueue& commands);
    void         updateMovementPattern(sf::Time dt);
    void         checkProjectileLaunch(sf::Time dt, CommandQueue& commands);
    void         handleIntersections();
    void         handleIntersectionsWithTank();
    void         handleIntersectionsWithBlock();
    void         adaptVelocityBasedOnCollisions();
    void         adaptRotationBasedOnCollisions();

    bool         isGuarding() const;
    void         adjustGuardingDirections();

    void         createBullets(SceneNode& node, const TextureHolder& textures) const;
    void         createProjectile(SceneNode& node,
                                  Projectile::Type type,
                                  sf::Vector2f offset,
                                  const TextureHolder& textures) const;

    void            updateTexts();

  private:
    struct CollisionData
    {
      CollisionData(sf::FloatRect intersection)
        : intersection(intersection)
      {
      }

      sf::FloatRect intersection;
    };

  private:
    Type            mType;
    sf::Sprite      mSprite;
    float           mRotationOffset; // basically a rate of rotation
    bool            mCanMoveLeft;
    bool            mCanMoveRight;
    bool            mCanMoveUp;
    bool            mCanMoveDown;
    bool            mCanRotateCounterclockwise;
    bool            mCanRotateClockwise;
    
    Command         mFireCommand;
    sf::Time        mFireCountdown;
    bool            mIsFiring;
    bool            mIsMarkedForRemoval;
    std::vector<CollisionData>    mCollisionsWithTank;
    std::vector<CollisionData>    mCollisionsWithBlock;

    int             mFireRateLevel;

    float           mTravelledDistance;
    float           mAmountRotated;
    std::size_t     mDirectionIndex;
    std::vector<Direction>    mDirections;

    // For tanks of guarding type
    float           mGuardingPathLength;
    float           mGuardingAngle;

    TextNode*       mHealthDisplay;
    SceneNode*      mBulletEmitter; // blank SceneNode used for positioning
                                    // bullets according to offsets
};

#endif // TANKS_TANK_HPP