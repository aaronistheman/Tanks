#ifndef TANKS_DATATABLES_HPP
#define TANKS_DATATABLES_HPP

#include <Tanks/ResourceIdentifiers.hpp>

#include <vector>


struct TankData
{
  int             hitpoints;
  float           movementSpeed;
  float           rotationSpeed;
  Textures::ID    texture;
};


std::vector<TankData> initializeTankData();

#endif // TANKS_DATATABLES_HPP