#ifndef TANKS_DATATABLES_HPP
#define TANKS_DATATABLES_HPP

#include <Tanks/ResourceIdentifiers.hpp>

#include <SFML/System/Time.hpp>

#include <vector>


struct Direction
{
  Direction(float movementAngle, float distance, float rotation)
    : angle(movementAngle)
    , distance(distance)
    , rotation(rotation)
  {
  }

  float angle; // gives the direction to move
  float distance;
  float rotation;
};

struct TankData
{
  int             hitpoints;
  float           movementSpeed;
  float           rotationSpeed;
  Textures::ID    texture;
	sf::Time						fireInterval;
  std::vector<Direction>  directions;
};

struct ProjectileData
{
  int             damage;
  float           speed;
  Textures::ID    texture;
};


std::vector<TankData> initializeTankData();
std::vector<ProjectileData> initializeProjectileData();

#endif // TANKS_DATATABLES_HPP