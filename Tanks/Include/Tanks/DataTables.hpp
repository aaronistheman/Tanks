/*
  Authors of original version: Artur Moreira, Henrik Vogelius Hansson, and
    Jan Haller
*/

#ifndef TANKS_DATATABLES_HPP
#define TANKS_DATATABLES_HPP

#include <Tanks/ResourceIdentifiers.hpp>
#include <Tanks/SpawnPoint.hpp>
#include <Tanks/World.hpp>
#include <Tanks/Direction.hpp>

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Color.hpp>

#include <vector>


// Describes the bullet launches of tanks
struct BulletLaunchData
{
  sf::Vector2f bulletOffset;
};

struct TankData
{
  int             hitpoints;
  float           movementSpeed;
  float           rotationSpeed;
  Textures::ID    texture;
	sf::Time						fireInterval;
  std::vector<BulletLaunchData>   bullets;
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

struct LevelData
{
  Textures::ID                    backgroundTexture;
  World::ViewType                 viewType;
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