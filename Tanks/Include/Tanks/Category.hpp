#ifndef TANKS_CATEGORY_HPP
#define TANKS_CATEGORY_HPP


// Entity/scene node category, used to dispatch commands
namespace Category
{
	enum Type
	{
		None				= 0,
		SceneGroundLayer	 = 1 << 0,
		PlayerTank		= 1 << 1,
		SimpleEnemyTank		= 1 << 2,
    ToxicTank      = 1 << 3,
    HuntingTank    = 1 << 4,
    AlliedProjectile = 1 << 5,
    EnemyProjectile  = 1 << 6,
    IndestructibleBlock = 1 << 7,
    DestructibleBlock   = 1 << 8,

    EnemyTank = SimpleEnemyTank | ToxicTank | HuntingTank,

    Tank = PlayerTank | EnemyTank,
		Projectile = AlliedProjectile | EnemyProjectile,
    Block = IndestructibleBlock | DestructibleBlock,
	};
}

#endif // TANKS_CATEGORY_HPP
