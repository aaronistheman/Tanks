#ifndef TANKS_UTILITY_HPP
#define TANKS_UTILITY_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <sstream>


namespace sf
{
	class Sprite;
	class Text;
}

// Since std::to_string doesn't work on MinGW we have to implement
// our own to support all platforms.
template <typename T>
std::string toString(const T& value);

// Convert enumerators to strings
std::string toString(sf::Keyboard::Key key);

// Calls setOrigin() with the center of the object
void  centerOrigin(sf::Sprite& sprite);
void  centerOrigin(sf::Text& text);

// Calls setScale() to resize the object
void setSize(sf::Sprite& sprite, const sf::Vector2f& desiredSize);

// Degree/radian conversion
float			toDegree(float radian);
float			toRadian(float degree);

// Random number generation
int				randomInt(int exclusiveMax);

// Vector operations
float			length(sf::Vector2f vector);
sf::Vector2f	unitVector(sf::Vector2f vector);

// Because SFML's angles used in rotation are different from
// the nature of typical trigonometry angles, this function
// is necessary for using trig functions from <cmath>.
float     toTrigAngle(float degree);

#include <Tanks/Utility.inl>
#endif // TANKS_UTILITY_HPP