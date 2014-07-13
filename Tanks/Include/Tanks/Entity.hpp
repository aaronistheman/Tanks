#ifndef TANKS_ENTITY_HPP
#define TANKS_ENTITY_HPP

#include <Tanks/SceneNode.hpp>


class Entity : public SceneNode
{
	public:
		void				setVelocity(sf::Vector2f velocity);
		void				setVelocity(float vx, float vy);
		sf::Vector2f		getVelocity() const;


	private:
		virtual void		updateCurrent(sf::Time dt);


	private:
		sf::Vector2f		mVelocity;
};

#endif // TANKS_ENTITY_HPP
