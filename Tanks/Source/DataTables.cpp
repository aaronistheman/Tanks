#include <Tanks/DataTables.hpp>
#include <Tanks/Tank.hpp>
#include <Tanks/Projectile.hpp>

std::vector<TankData> initializeTankData()
{
  std::vector<TankData> data(Tank::TypeCount);

  data[Tank::DefaultTank].hitpoints = 100;
  data[Tank::DefaultTank].movementSpeed = 200.f;
  data[Tank::DefaultTank].rotationSpeed = 80.f;
  data[Tank::DefaultTank].texture = Textures::DefaultTank;
  data[Tank::DefaultTank].fireInterval = sf::seconds(1);

  data[Tank::EnemyTank].hitpoints = 40;
  data[Tank::EnemyTank].movementSpeed = 80.f;
  data[Tank::EnemyTank].rotationSpeed = 60.f;
  data[Tank::EnemyTank].texture = Textures::EnemyTank;
  data[Tank::EnemyTank].fireInterval = sf::seconds(2);
  data[Tank::EnemyTank].directions.push_back(Direction( 90, 50, 30));
  data[Tank::EnemyTank].directions.push_back(Direction( 0, 50, -60));
  data[Tank::EnemyTank].directions.push_back(Direction( 270, 50, 60));
  data[Tank::EnemyTank].directions.push_back(Direction( 180, 50, -30));

  return data;
}

std::vector<ProjectileData> initializeProjectileData()
{
	std::vector<ProjectileData> data(Projectile::TypeCount);

	data[Projectile::AlliedBullet].damage = 10;
	data[Projectile::AlliedBullet].speed = 300.f;
	data[Projectile::AlliedBullet].texture = Textures::Bullet;

	data[Projectile::EnemyBullet].damage = 10;
	data[Projectile::EnemyBullet].speed = 300.f;
	data[Projectile::EnemyBullet].texture = Textures::Bullet;

	// data[Projectile::Missile].damage = 200;
	// data[Projectile::Missile].speed = 150.f;
	// data[Projectile::Missile].texture = Textures::Missile;

	return data;
}