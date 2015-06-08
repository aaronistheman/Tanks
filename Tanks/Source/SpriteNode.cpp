#include <Tanks/SpriteNode.hpp>
#include <Tanks/Utility.hpp>

#include <SFML/Graphics/RenderTarget.hpp>


SpriteNode::SpriteNode(const sf::Texture& texture)
: mSprite(texture)
{
}	

SpriteNode::SpriteNode(const sf::Texture& texture, const sf::IntRect& textureRect)
: mSprite(texture, textureRect)
{
}

/*
SpriteNode::SpriteNode(const sf::Texture& texture, const sf::Vector2f& sizeOfSprite)
: mSprite(texture)
{
  setSize(mSprite, sizeOfSprite);
}
*/

void SpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}