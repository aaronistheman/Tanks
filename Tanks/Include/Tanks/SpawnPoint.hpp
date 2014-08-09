#ifndef TANKS_SPAWNPOINT_HPP
#define TANKS_SPAWNPOINT_HPP

#include <Tanks/Tank.hpp>
#include <Tanks/Block.hpp>


struct EnemySpawnPoint
{
  EnemySpawnPoint(Tank::Type type, float x, float y, float rotation,
                  float numberOfKills)
    : type(type)
    , x(x)
    , y(y)
    , r(rotation)
    , n(numberOfKills)
  {
  }

  Tank::Type type;
  float x;
  float y;
  float r;
  float n;
};

struct BlockSpawnPoint
{
  BlockSpawnPoint(Block::Type type, float posX, float posY,
                  float sizeX, float sizeY)
    : type(type)
    , posX(posX)
    , posY(posY)
    , sizeX(sizeX)
    , sizeY(sizeY)
  {
  }

  Block::Type type;
  float posX;
  float posY;
  float sizeX;
  float sizeY;
};

#endif // TANKS_SPAWNPOINT_HPP