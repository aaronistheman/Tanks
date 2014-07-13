#include <Tanks/Utility.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

void centerOrigin(sf::Sprite& sprite)
{
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(std::floor(bounds.width / 2.f), std::floor(bounds.height / 2.f));
}

void centerOrigin(sf::Text& text)
{
	sf::FloatRect bounds = text.getLocalBounds();
	text.setOrigin(std::floor(bounds.width / 2.f), std::floor(bounds.height / 2.f));
}

void setSize(sf::Sprite& sprite, const sf::Vector2f& desiredSize)
{
  sprite.setScale(desiredSize.x / sprite.getTexture()->getSize().x,
                  desiredSize.y / sprite.getTexture()->getSize().y);
}