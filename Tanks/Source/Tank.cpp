#include <Tanks/Tank.hpp>
#include <Tanks/ResourceHolder.hpp>
#include <Tanks/Utility.hpp>
#include <Tanks/Category.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>


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
: mType(type)
, mSprite(textures.get(toTextureID(type)))
{
	centerOrigin(mSprite);
  setSize(mSprite, sf::Vector2f(80.0f, 37.0f));
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
			return Category::PlayerAircraft;

		default:
			return Category::EnemyAircraft;
	}
}
