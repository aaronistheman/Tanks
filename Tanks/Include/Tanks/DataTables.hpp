#ifndef TANKS_DATATABLES_HPP
#define TANKS_DATATABLES_HPP

#include <Tanks/ResourceIdentifiers.hpp>
#include <Tanks/SpawnPoint.hpp>

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Color.hpp>

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
  sf::Vector2f            bulletOffset;
  std::vector<Direction>  directions;
};

struct ProjectileData
{
  int             damage;
  float           speed;
  Textures::ID    texture;
};

struct BlockData
{
  sf::Color     color;
  int           hitpoints;
};

namespace WorldView
{
  enum Type
  {
    Static,
    Following,
    Scrolling
  };
}

struct LevelData
{
  Textures::ID                    backgroundTexture;
  WorldView::Type                 worldView;
  sf::FloatRect                   worldBounds;
  sf::Vector2f                    playerSpawnPosition;
  std::vector<EnemySpawnPoint>    enemySpawnPoints;
  std::vector<BlockSpawnPoint>    blockSpawnPoints;
};


std::vector<TankData>         initializeTankData();
std::vector<ProjectileData>   initializeProjectileData();
std::vector<BlockData>        initializeBlockData();
std::vector<LevelData>        initializeLevelData();

#endif // TANKS_DATATABLES_HPP