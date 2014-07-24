#include <Tanks/DataTables.hpp>
#include <Tanks/Tank.hpp>

std::vector<TankData> initializeTankData()
{
  std::vector<TankData> data(Tank::TypeCount);

  data[Tank::DefaultTank].hitpoints = 100;
  data[Tank::DefaultTank].movementSpeed = 200.f;
  data[Tank::DefaultTank].rotationSpeed = 80.f;
  data[Tank::DefaultTank].texture = Textures::DefaultTank;

  return data;
}