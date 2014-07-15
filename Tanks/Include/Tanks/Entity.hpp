#ifndef TANKS_ENTITY_HPP
#define TANKS_ENTITY_HPP

#include <Tanks/SceneNode.hpp>


class Entity : public SceneNode
{
	public:
		void				setVelocity(sf::Vector2f velocity);
		void				setVelocity(float vx, float vy);
		void				accelerate(sf::Vector2f velocity);
		void				accelerate(float vx, float vy);
		sf::Vector2f		getVelocity() const;

    void        setRotationOffset(float angle);
    void        rotate(float offset);
    float       getRotationOffset() const;


	private:
		virtual void		updateCurrent(sf::Time dt);


	private:
		sf::Vector2f		mVelocity;
    float           mRotationOffset;
};

#endif // TANKS_ENTITY_HPP
