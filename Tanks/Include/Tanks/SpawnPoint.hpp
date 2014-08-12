#ifndef TANKS_SPAWNPOINT_HPP
#define TANKS_SPAWNPOINT_HPP

#include <Tanks/Tank.hpp>
#include <Tanks/Block.hpp>


struct EnemySpawnPoint
{
  EnemySpawnPoint(Tank::Type type, float x, float y, float rotation,
                  int numberOfKills, int hitpoints)
    : type(type)
    , x(x)
    , y(y)
    , r(rotation)
    , n(numberOfKills)
    , h(hitpoints)
  {
  }

  Tank::Type type;
  float x;
  float y;
  float r;
  int n;
  int h;
};

struct BlockSpawnPoint
{
  BlockSpawnPoint(Block::Type type, float posX, float posY,
                  float sizeX, float sizeY, int hitpoints = 0)
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