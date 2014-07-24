#include <Tanks/Tank.hpp>
#include <Tanks/DataTables.hpp>
#include <Tanks/ResourceHolder.hpp>
#include <Tanks/Utility.hpp>
#include <Tanks/Category.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>


namespace
{
  const std::vector<TankData> Table = initializeTankData();
}

Textures::ID toTextureID(Tank::Type type)
{
	switch (type)
	{
		case Tank::DefaultTank:
			return Textures::DefaultTank;
	}
	return Textures::DefaultTank;
}

Tank::Tank(Type type, const TextureHolder& textures)
: Entity(Table[type].hitpoints)
, mType(type)
, mSprite(textures.get(toTextureID(type)))
{
	centerOrigin(mSprite);
}

void Tank::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}

unsigned int Tank::getCategory() const
{
	switch (mType)
	{
		case DefaultTank:
			return Category::PlayerTank;

		default:
			return Category::EnemyTank;
	}
}

sf::FloatRect Tank::getBoundingRect() const
{
	return getWorldTransform().transformRect(mSprite.getGlobalBounds());
}
