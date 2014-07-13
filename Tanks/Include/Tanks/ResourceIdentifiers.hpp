#ifndef TANKS_RESOURCEIDENTIFIERS_HPP
#define TANKS_RESOURCEIDENTIFIERS_HPP


// Forward declaration of SFML classes
namespace sf
{
	class Texture;
}

namespace Textures
{
	enum ID
	{
		Metal,
    DefaultTank,
    TypeCount,
	};
}

// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;

#endif // TANKS_RESOURCEIDENTIFIERS_HPP
