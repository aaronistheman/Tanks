#include <Tanks/Projectile.hpp>
#include <Tanks/Utility.hpp>
#include <Tanks/DataTables.hpp>
#include <Tanks/ResourceHolder.hpp>


namespace
{
	const std::vector<ProjectileData> Table = initializeProjectileData();
}

Projectile::Projectile(Type type, const TextureHolder& textures)
  : Entity(1)
  , mType(type)
  , mSprite(textures.get(Table[type].texture))
{
  centerOrigin(mSprite);
}