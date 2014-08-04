#ifndef TANKS_BLOCK_HPP
#define TANKS_BLOCK_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>

struct Block
{
  enum Type
  {
    Indestructible,
    Destructible,
    BlockCount
  };

  sf::Vector2f    size;
  sf::Vector2f    position;
  sf::Color       color;
  int             hitpoints;
};

#endif TANKS_BLOCK_HPP