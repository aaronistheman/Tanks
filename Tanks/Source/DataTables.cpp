#include <Tanks/DataTables.hpp>
#include <Tanks/Tank.hpp>
#include <Tanks/Projectile.hpp>
#include <Tanks/Block.hpp>
#include <Tanks/LevelIdentifiers.hpp>

#include <cassert>
#include <fstream>
#include <string>


Tank::Type convertStringToTankType(std::string& s)
{
  if (s == "Hero")
    return Tank::Hero;
  else if (s == "Dummy")
    return Tank::Dummy;
  else if (s == "Hunting1")
    return Tank::Hunting1;
  else if (s == "Hunting2")
    return Tank::Hunting2;

  else
  {
    // Terminate because something went wrong with the file and that
    // data could be crucial to the program
    assert(false);
  }
}

Projectile::Type convertStringToProjectileType(std::string& s)
{
  if (s == "AlliedBullet")
    return Projectile::AlliedBullet;
  else if (s == "EnemyBullet")
    return Projectile::EnemyBullet;

  else
  {
    // Terminate because something went wrong with the file and that
    // data could be crucial to the program
    assert(false);
  }
}

Block::Type convertStringToBlockType(std::string& s)
{
  if (s == "Indestructible")
    return Block::Indestructible;
  else if (s == "Destructible")
    return Block::Destructible;

  else
  {
    // Terminate because something went wrong with the file and that
    // data could be crucial to the program
    assert(false);
  }
}

Levels::ID convertStringToLevelID(std::string& s)
{
  if (s == "MainOne")
    return Levels::MainOne;
  else if (s == "MainTwo")
    return Levels::MainTwo;
  else if (s == "MainLast")
    return Levels::MainLast;
  else if (s == "Survival")
    return Levels::Survival;

  else
  {
    // Terminate because something went wrong with the file and that
    // data could be crucial to the program
    assert(false);
  }
}

World::ViewType convertStringToViewType(std::string& s)
{
  if (s == "Static")
    return World::Static;
  else if (s == "Following")
    return World::Following;
  else if (s == "Scrolling")
    return World::Scrolling;

  else
  {
    // Terminate because something went wrong with the file and that
    // data could be crucial to the program
    assert(false);
  }
}

Textures::ID convertStringToTextureID(std::string& s)
{
  if (s == "HeroTank")
    return Textures::HeroTank;
  else if (s == "DummyTank")
    return Textures::DummyTank;
  else if (s == "HuntingTank1")
    return Textures::HuntingTank1;
  else if (s == "HuntingTank2")
    return Textures::HuntingTank2;
  else if (s == "Bullet")
    return Textures::Bullet;
  else if (s == "Metal")
    return Textures::Metal;

  else
  {
    // Terminate because someting went wrong with the file and that
    // data could be crucial to the program
    assert(false);
  }
}

std::vector<TankData> initializeTankData()
{
  std::vector<TankData> data(Tank::TypeCount);

  std::string filePath = "DataTables/EntityData/TankData.txt";
  std::ifstream ist(filePath.c_str());

  std::string dataLabel = ""; // tells which tank's data is being read
  
  while (ist.good())
  {
    // Confirm that we're about to begin reading tank data
    while (dataLabel != "TankType")
      ist >> dataLabel;

    // Reset the reading variables
    std::string tankTypeString = "";
    int hitpoints = 0;
    float movementSpeed = 0.f;
    float rotationSpeed = 0.f;
    std::string textureID = "";
    float fireInterval = 0.f;
    float bulletOffsetX = 0.f;
    float bulletOffsetY = 0.f;
    float directionAngle = 0.f;
    float directionDistance = 0.f;
    float directionRotation = 0.f;

    // Get the actual type of tank
    ist >> tankTypeString;
    Tank::Type tankType = convertStringToTankType(tankTypeString);
    
    // Read all of the data for a specific tank type until told that the
    // data for a different tank type is next
    while (ist.good() && ist >> dataLabel && dataLabel != "TankType")
    {
      // Use dataLabel to determine which data is being read
      if (dataLabel == "Hitpoints")
      {
        ist >> hitpoints;
        data[tankType].hitpoints = hitpoints;
      }
      else if (dataLabel == "MovementSpeed")
      {
        ist >> movementSpeed;
        data[tankType].movementSpeed = movementSpeed;
      }
      else if (dataLabel == "RotationSpeed")
      {
        ist >> rotationSpeed;
        data[tankType].rotationSpeed = rotationSpeed;
      }
      else if (dataLabel == "TextureID")
      {
        ist >> textureID;
        data[tankType].texture = convertStringToTextureID(textureID);
      }
      else if (dataLabel == "FireInterval")
      {
        ist >> fireInterval;
        data[tankType].fireInterval = sf::seconds(fireInterval);
      }
      else if (dataLabel == "BulletOffset")
      {
        ist >> bulletOffsetX >> bulletOffsetY;
        data[tankType].bulletOffset = 
          sf::Vector2f(bulletOffsetX, bulletOffsetY);
      }
      else if (dataLabel == "Direction")
      {
        // AI direction (not every tank has this)
        ist >> directionAngle >> directionDistance >> directionRotation;
        data[tankType].directions.push_back(
          Direction(directionAngle, directionDistance, directionRotation));
      }
      else if (dataLabel == "/*")
      {
        // ignore file comment
        while (ist.good() && dataLabel != "*/")
          ist >> dataLabel;
      }
      else
      {
        // bad data label; call assert() to prevent hidden bad data reading
        assert(false);
      }
    }
  }

  // stop file reading
  ist.close();

  return data;
}

std::vector<ProjectileData> initializeProjectileData()
{
  std::vector<ProjectileData> data(Projectile::TypeCount);

  std::string filePath = "DataTables/EntityData/ProjectileData.txt";
  std::ifstream ist(filePath.c_str());

  std::string dataLabel = ""; // tells which projectile's data is being read
  
  while (ist.good())
  {
    // Confirm that we're about to begin reading projectile data
    while (dataLabel != "ProjectileType")
      ist >> dataLabel;

    // Reset the reading variables
    std::string projectileTypeString = "";
    int damage = 0;
    float speed = 0.f;
    std::string textureID = "";

    // Get the actual type of projectile
    ist >> projectileTypeString;
    Projectile::Type projectileType = 
      convertStringToProjectileType(projectileTypeString);
    
    // Read all of the data for a specific projectile type until told that the
    // data for a different projectile type is next
    while (ist.good() && ist >> dataLabel && dataLabel != "ProjectileType")
    {
      // Use dataLabel to determine which data is being read
      if (dataLabel == "Damage")
      {
        ist >> damage;
        data[projectileType].damage = damage;
      }
      else if (dataLabel == "Speed")
      {
        ist >> speed;
        data[projectileType].speed = speed;
      }
      else if (dataLabel == "TextureID")
      {
        ist >> textureID;
        data[projectileType].texture = convertStringToTextureID(textureID);
      }
      else if (dataLabel == "/*")
      {
        // ignore file comment
        while (ist.good() && dataLabel != "*/")
          ist >> dataLabel;
      }
      else
      {
        // bad data label; call assert() to prevent hidden bad data reading
        assert(false);
      }
    }
  }

  // stop file reading
  ist.close();

  return data;
}

std::vector<BlockData> initializeBlockData()
{
  std::vector<BlockData> data(Block::TypeCount);

  std::string filePath = "DataTables/EntityData/BlockData.txt";
  std::ifstream ist(filePath.c_str());

  std::string dataLabel = ""; // tells which block's data is being read
  
  while (ist.good())
  {
    // Confirm that we're about to begin reading block data
    while (dataLabel != "BlockType")
      ist >> dataLabel;

    // Reset the reading variables
    std::string blockTypeString = "";
    int redComponent = 0.f;
    int greenComponent = 0.f;
    int blueComponent = 0.f;
    int alphaComponent = 0.f;
    int hitpoints = 0;

    // Get the actual type of block
    ist >> blockTypeString;
    Block::Type blockType = 
      convertStringToBlockType(blockTypeString);
    
    // Read all of the data for a specific block type until told that the
    // data for a different block type is next
    while (ist.good() && ist >> dataLabel && dataLabel != "BlockType")
    {
      // Use dataLabel to determine which data is being read
      if (dataLabel == "Color")
      {
        ist >> redComponent >> greenComponent >> 
          blueComponent >> alphaComponent;
        data[blockType].color = sf::Color(redComponent, greenComponent,
                                          blueComponent, alphaComponent);
      }
      else if (dataLabel == "Hitpoints")
      {
        ist >> hitpoints;
        data[blockType].hitpoints = hitpoints;
      }
      else if (dataLabel == "/*")
      {
        // ignore file comment
        while (ist.good() && dataLabel != "*/")
          ist >> dataLabel;
      }
      else
      {
        // bad data label; call assert() to prevent hidden bad data reading
        assert(false);
      }
    }
  }

  // stop file reading
  ist.close();

	return data;
}

std::vector<LevelData> initializeLevelData()
{
  std::vector<LevelData> data(Levels::TypeCount);

  std::string filePath = "DataTables/LevelData/LevelData.txt";
  std::ifstream ist(filePath.c_str());

  std::string levelLabel = "";

  while (ist.good())
  {
    // Confirm that we're about to begin reading level data
    while (levelLabel != "LevelID")
      ist >> levelLabel;

    // Reset the reading variables
    std::string   levelString = "";
    std::string   textureID = "";
    std::string   viewTypeString = "";
    float         worldBoundsLeft = 0.f;
    float         worldBoundsTop = 0.f;
    float         worldBoundsWidth = 0.f;
    float         worldBoundsHeight = 0.f;
    float         playerSpawnX = 0.f;
    float         playerSpawnY = 0.f;
    std::string   enemyTypeString = "";
    float         enemyPosX = 0.f;
    float         enemyPosY = 0.f;
    float         rotation = 0.f;
    float         requiredKills = 0.f;
    std::string   blockTypeString = "";
    float         blockPosX = 0.f;
    float         blockPosY = 0.f;
    float         blockSizeX = 0.f;
    float         blockSizeY = 0.f;

    // Get the actual type of level
    ist >> levelString;
    Levels::ID levelID = convertStringToLevelID(levelString);
    
    // Read all of the data for a specific level until told that the
    // data for a different level is next
    while (ist.good() && ist >> levelLabel && levelLabel != "LevelID")
    {
      // Use dataLabel to determine which data is being read
      if (levelLabel == "TextureID")
      {
        ist >> textureID;
        data[levelID].backgroundTexture = convertStringToTextureID(textureID);
      }
      else if (levelLabel == "ViewType")
      {
        ist >> viewTypeString;
        data[levelID].viewType = convertStringToViewType(viewTypeString);
      }
      else if (levelLabel == "WorldBounds")
      {
        ist >> worldBoundsLeft >> worldBoundsTop >> 
          worldBoundsWidth >> worldBoundsHeight;
        data[levelID].worldBounds = sf::FloatRect(worldBoundsLeft, 
          worldBoundsTop, worldBoundsWidth, worldBoundsHeight);
      }
      else if (levelLabel == "PlayerSpawn")
      {
        ist >> playerSpawnX >> playerSpawnY;
        data[levelID].playerSpawnPosition = 
          sf::Vector2f(playerSpawnX, playerSpawnY);
      }
      else if (levelLabel == "Enemy")
      {
        ist >> enemyTypeString >> enemyPosX >> enemyPosY >> 
          rotation >> requiredKills;

        Tank::Type enemyType = convertStringToTankType(enemyTypeString);

        data[levelID].enemySpawnPoints.push_back(
          EnemySpawnPoint(enemyType, 
            enemyPosX, enemyPosY, rotation, requiredKills,
            Tank::getMaxHitpoints(enemyType)));
      }
      else if (levelLabel == "Block")
      {
        ist >> blockTypeString >> blockPosX >> blockPosY >>
          blockSizeX >> blockSizeY;

        Block::Type blockType = convertStringToBlockType(blockTypeString);

        data[levelID].blockSpawnPoints.push_back(
          BlockSpawnPoint(convertStringToBlockType(blockTypeString),
            blockPosX, blockPosY, blockSizeX, blockSizeY,
            Block::getMaxHitpoints(blockType)));
      }
      else if (levelLabel == "/*")
      {
        // ignore file comment
        while (ist.good() && levelLabel != "*/")
          ist >> levelLabel;
      }
      else
      {
        // bad data label; call assert() to prevent hidden bad data reading
        assert(false);
      }
    }
  }

  // stop file reading
  ist.close();

  return data;
}