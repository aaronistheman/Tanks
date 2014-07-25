#ifndef TANKS_ENTITY_HPP
#define TANKS_ENTITY_HPP

#include <Tanks/SceneNode.hpp>


class Entity : public SceneNode
{
	public:
    explicit    Entity(int hitpoints);

		void				setVelocity(sf::Vector2f velocity);
		void				setVelocity(float vx, float vy);
		void				accelerate(sf::Vector2f velocity);
		void				accelerate(float vx, float vy);
		sf::Vector2f		getVelocity() const;
    /*
    void        setRotationOffset(float angle);
    void        rotate(float offset);
    float       getRotationOffset() const;
    */
    void        repair(int points);
    void        damage(int points);
    void        destroy();
    int         getHitpoints() const;
    bool        isDestroyed() const;


	protected:
		virtual void		updateCurrent(sf::Time dt, CommandQueue& commands);


	private:
		sf::Vector2f		mVelocity;
    // float           mRotationOffset;
    int             mHitpoints;
};

#endif // TANKS_ENTITY_HPP
