#ifndef TANKS_DATATABLES_HPP
#define TANKS_DATATABLES_HPP

#include <Tanks/ResourceIdentifiers.hpp>

#include <vector>


struct Direction
{
  Direction(float angle, float distance, float rotation)
    : angle(angle)
    , distance(distance)
    , rotation(rotation)
  {
  }

  float angle;
  float distance;
  float rotation;
};

struct TankData
{
  int             hitpoints;
  float           movementSpeed;
  float           rotationSpeed;
  Textures::ID    texture;
  std::vector<Direction>  directions;
};


std::vector<TankData> initializeTankData();

#endif // TANKS_DATATABLES_HPP