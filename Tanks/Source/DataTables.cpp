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
  if (s == "DefaultTank")
    return Tank::DefaultTank;
  else if (s == "EnemyTank1")
    return Tank::EnemyTank1;
  else if (s == "EnemyTank2")
    return Tank::EnemyTank2;

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

Level::ID convertStringToLevel(std::string& s)
{
  if (s == "MainOne")
    return Level::MainOne;
  else if (s == "MainTwo")
    return Level::MainTwo;
  else if (s == "Survival")
    return Level::Survival;

  else
  {
    // Terminate because something went wrong with the file and that
    // data could be crucial to the program
    assert(false);
  }
}

WorldView::Type convertStringToWorldViewType(std::string& s)
{
  if (s == "Static")
    return WorldView::Static;
  else if (s == "Following")
    return WorldView::Following;
  else if (s == "Scrolling")
    return WorldView::Scrolling;

  else
  {
    // Terminate because something went wrong with the file and that
    // data could be crucial to the program
    assert(false);
  }
}

Textures::ID convertStringToTextureID(std::string& s)
{
  if (s == "DefaultTank")
    return Textures::DefaultTank;
  else if (s == "EnemyTank1")
    return Textures::EnemyTank1;
  else if (s == "EnemyTank2")
    return Textures::EnemyTank2;
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
    std::string textureName = "";
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
        ist >> textureName;
        data[tankType].texture = convertStringToTextureID(textureName);
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
  
  // Figure out which projectile is next for initializing data;
  // initialize each data element of that projectile
  while (!ist.eof())
  {
    // This is used to input the labels preceding each data element (see
    // the text files in the DataTables folder);
    // we don't want to input the labels into any significant variable;
    // they are there to make reading the file easier for humans
    std::string label = "";

    std::string projectileTypeString = "";
    int damage = 0;
    float speed = 0.f;
    std::string textureName = "";

    ist >> label; // Ignore the label in front of each data element
    ist >> projectileTypeString;
    ist >> label;
    ist >> damage;
    ist >> label;
    ist >> speed;
    ist >> label;
    ist >> textureName;

    Projectile::Type projectileType = 
      convertStringToProjectileType(projectileTypeString);
    data[projectileType].damage = damage;
    data[projectileType].speed = speed;
    data[projectileType].texture = convertStringToTextureID(textureName);
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
  
  // Figure out which block type is next for initializing data;
  // initialize each data element of that block
  while (!ist.eof())
  {
    // This is used to input the labels preceding each data element (see
    // the text files in the DataTables folder);
    // we don't want to input the labels into any significant variable;
    // they are there to make reading the file easier for humans
    std::string label = "";

    std::string blockTypeString = "";
    int redComponent = 0.f;
    int greenComponent = 0.f;
    int blueComponent = 0.f;
    int alphaComponent = 0.f;
    int hitpoints = 0;

    ist >> label; // Ignore the label in front of each data element
    ist >> blockTypeString;
    ist >> label;
    ist >> redComponent;
    ist >> greenComponent;
    ist >> blueComponent;
    ist >> alphaComponent;
    ist >> label;
    ist >> hitpoints;

    Block::Type blockType = convertStringToBlockType(blockTypeString);
    data[blockType].color = sf::Color(redComponent, greenComponent,
                                      blueComponent, alphaComponent);
    data[blockType].hitpoints = hitpoints;
  }

  // stop file reading
  ist.close();

	return data;
}

std::vector<LevelData> initializeLevelData()
{
  std::vector<LevelData> data(Level::TypeCount);

  std::string filePath = "DataTables/LevelData/LevelData.txt";
  std::ifstream ist(filePath.c_str());

  while (!ist.eof())
  {
    // This is used to input the labels preceding each data element (see
    // the text files in the DataTables folder);
    // we don't want to input the labels into any significant variable;
    // they are there to make reading the file easier for humans
    std::string label = "";

    std::string levelString = "";
    std::string textureName = "";
    std::string worldView = "";

    ist >> label; // Ignore the label in front of each data element
    ist >> levelString;
    ist >> label;
    ist >> textureName;
    ist >> label;
    ist >> worldView;

    Level::ID level = convertStringToLevel(levelString);
    data[level].backgroundTexture = convertStringToTextureID(textureName);
    data[level].worldView = convertStringToWorldViewType(worldView);
  }

  // stop file reading
  ist.close();

  return data;
}