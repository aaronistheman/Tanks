#ifndef TANKS_CATEGORY_HPP
#define TANKS_CATEGORY_HPP


// Entity/scene node category, used to dispatch commands
namespace Category
{
	enum Type
	{
		None				= 0,
		Scene				= 1 << 0,
		PlayerTank		= 1 << 1,
		AlliedTank		= 1 << 2,
		EnemyTank		= 1 << 3,
	};
}

#endif // TANKS_CATEGORY_HPP
