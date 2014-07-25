#include <Tanks/DataTables.hpp>
#include <Tanks/Tank.hpp>

std::vector<TankData> initializeTankData()
{
  std::vector<TankData> data(Tank::TypeCount);

  data[Tank::DefaultTank].hitpoints = 100;
  data[Tank::DefaultTank].movementSpeed = 200.f;
  data[Tank::DefaultTank].rotationSpeed = 80.f;
  data[Tank::DefaultTank].texture = Textures::DefaultTank;

  data[Tank::EnemyTank].hitpoints = 40;
  data[Tank::EnemyTank].movementSpeed = 80.f;
  data[Tank::EnemyTank].rotationSpeed = 60.f;
  data[Tank::EnemyTank].texture = Textures::DefaultTank;
  data[Tank::EnemyTank].directions.push_back(Direction( 45, 80, 0));
  data[Tank::EnemyTank].directions.push_back(Direction(-45, 160, 0));
  data[Tank::EnemyTank].directions.push_back(Direction( 45, 80, 0));

  return data;
}