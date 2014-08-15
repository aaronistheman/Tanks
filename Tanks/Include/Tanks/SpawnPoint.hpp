#ifndef TANKS_SPAWNPOINT_HPP
#define TANKS_SPAWNPOINT_HPP

#include <Tanks/Tank.hpp>
#include <Tanks/Block.hpp>


struct EnemySpawnPoint
{
  EnemySpawnPoint(Tank::Type type, 
                  float x, float y, 
                  float rotation,
                  int numberOfKills, 
                  int hitpoints,
                  float guardingPathLength = 0.f,
                  float guardingAngle = 0.f,
                  float travelledDistance = 0.f, 
                  float amountRotation = 0.f,
                  std::size_t directionIndex = 0)
    : type(type)
    , x(x)
    , y(y)
    , r(rotation)
    , n(numberOfKills)
    , h(hitpoints)
    , gpl(guardingPathLength)
    , ga(guardingAngle)
    , td(travelledDistance)
    , ar(amountRotation)
    , di(directionIndex)
  {
  }

  Tank::Type type;
  float x;
  float y;
  float r;
  int n;
  int h;
  float gpl;
  float ga;
  float td;
  float ar;
  std::size_t di;
};

struct BlockSpawnPoint
{
  BlockSpawnPoint(Block::Type type, float posX, float posY,
                  float sizeX, float sizeY, int hitpoints)
    : type(type)
    , posX(posX)
    , posY(posY)
    , sizeX(sizeX)
    , sizeY(sizeY)
    , h(hitpoints)
  {
  }

  Block::Type type;
  float posX;
  float posY;
  float sizeX;
  float sizeY;
  int h;
};

#endif // TANKS_SPAWNPOINT_HPP