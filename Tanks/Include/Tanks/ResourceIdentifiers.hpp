#ifndef TANKS_RESOURCEIDENTIFIERS_HPP
#define TANKS_RESOURCEIDENTIFIERS_HPP


// Forward declaration of SFML classes
namespace sf
{
	class Texture;
  class Font;
}

namespace Textures
{
	enum ID
	{
		HeroTank,
    DummyTank,
    HuntingTank1,
    HuntingTank2,
    GuardingTank1,
    Bullet,
    Metal,
    TitleScreen,
    ButtonNormal,
    ButtonSelected,
    ButtonPressed
	};
}

namespace Fonts
{
  enum ID
  {
    Main,
  };
}

// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
typedef ResourceHolder<sf::Font,    Fonts::ID>     FontHolder;

#endif // TANKS_RESOURCEIDENTIFIERS_HPP
