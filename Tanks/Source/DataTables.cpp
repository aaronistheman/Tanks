#include <Tanks/DataTables.hpp>
#include <Tanks/Tank.hpp>
#include <Tanks/Projectile.hpp>
#include <Tanks/Block.hpp>

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
    return Tank::DefaultTank;
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
    return Projectile::AlliedBullet;
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
    return Block::Indestructible;
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

  else
  {
    // Terminate because someting went wrong with the file and that
    // data could be crucial to the program
    assert(false);
    return Textures::DefaultTank;
  }
}

std::vector<TankData> initializeTankData()
{
  std::vector<TankData> data(Tank::TypeCount);

  std::string filePath = "DataTables/TankData.txt";
  std::ifstream ist(filePath.c_str());
  
  // Figure out which tank is next for initializing data;
  // initialize each data element of that tank
  while (!ist.eof())
  {
    // This is used to input the labels preceding each data element (see
    // the text files in the DataTables folder);
    // we don't want to input the labels into any significant variable;
    // they are there to make reading the file easier for humans
    std::string label = "";

    std::string tankTypeString = "";
    int hitpoints = 0;
    float movementSpeed = 0.f;
    float rotationSpeed = 0.f;
    std::string textureName = "";
    float fireInterval = 0.f;
    float bulletOffsetX = 0.f;
    float bulletOffsetY = 0.f;

    ist >> label; // Ignore the label in front of each data element
    ist >> tankTypeString;
    Tank::Type tankType = convertStringToTankType(tankTypeString);
    
    ist >> label;
    ist >> hitpoints;
    data[tankType].hitpoints = hitpoints;
    
    ist >> label;
    ist >> movementSpeed;
    data[tankType].movementSpeed = movementSpeed;
    
    ist >> label;
    ist >> rotationSpeed;
    data[tankType].rotationSpeed = rotationSpeed;
    
    ist >> label;
    ist >> textureName;
    data[tankType].texture = convertStringToTextureID(textureName);
    
    ist >> label;
    ist >> fireInterval;
    data[tankType].fireInterval = sf::seconds(fireInterval);
    
    ist >> label;
    ist >> bulletOffsetX;
    ist >> label;
    ist >> bulletOffsetY;
    data[tankType].bulletOffset =
      sf::Vector2f(bulletOffsetX, bulletOffsetY);
  } 

  // stop file reading
  ist.close();

  // AI directions; these are not in the files
  // data[Tank::EnemyTank1].directions.push_back(Direction( 90, 50, 30));
  // data[Tank::EnemyTank1].directions.push_back(Direction( 0, 50, -60));
  // data[Tank::EnemyTank1].directions.push_back(Direction( 270, 50, 60));
  // data[Tank::EnemyTank1].directions.push_back(Direction( 180, 50, -30));

  return data;
}

std::vector<ProjectileData> initializeProjectileData()
{
	std::vector<ProjectileData> data(Projectile::TypeCount);
  
  std::string filePath = "DataTables/ProjectileData.txt";
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
    Projectile::Type projectileType = 
      convertStringToProjectileType(projectileTypeString);
    
    ist >> label;
    ist >> damage;
    data[projectileType].damage = damage;
    
    ist >> label;
    ist >> speed;
    data[projectileType].speed = speed;
    
    ist >> label;
    ist >> textureName;
    data[projectileType].texture = convertStringToTextureID(textureName);
  }

  // stop file reading
  ist.close();

	return data;
}

std::vector<BlockData> initializeBlockData()
{
  std::vector<BlockData> data(Block::TypeCount);
  
  std::string filePath = "DataTables/BlockData.txt";
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
    Block::Type blockType = 
      convertStringToBlockType(blockTypeString);
    
    ist >> label;
    ist >> redComponent;
    ist >> greenComponent;
    ist >> blueComponent;
    ist >> alphaComponent;
    data[blockType].color = sf::Color(redComponent, greenComponent,
                                      blueComponent, alphaComponent);

    ist >> label;
    ist >> hitpoints;
    data[blockType].hitpoints = hitpoints;
  }

  // stop file reading
  ist.close();

	return data;
}