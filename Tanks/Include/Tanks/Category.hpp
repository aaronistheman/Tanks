#ifndef TANKS_CATEGORY_HPP
#define TANKS_CATEGORY_HPP


// Entity/scene node category, used to dispatch commands
namespace Category
{
	enum Type
	{
		None				= 0,
		SceneAirLayer				= 1 << 0,
		PlayerTank		= 1 << 1,
		AlliedTank		= 1 << 2,
		EnemyTank		= 1 << 3,
    Pickup      = 1 << 4,
    AlliedProjectile = 1 << 5,
    EnemyProjectile  = 1 << 6,

		Aircraft = PlayerTank | AlliedTank | EnemyTank,
		Projectile = AlliedProjectile | EnemyProjectile,
	};
}

#endif // TANKS_CATEGORY_HPP
