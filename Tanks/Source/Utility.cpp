#include <Tanks/Utility.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Shape.hpp>

#include <cmath>
#include <random>
#include <ctime>
#include <cassert>


namespace
{
	std::default_random_engine createRandomEngine()
	{
		auto seed = static_cast<unsigned long>(std::time(nullptr));
		return std::default_random_engine(seed);
	}

	auto RandomEngine = createRandomEngine();
}

std::string toString(sf::Keyboard::Key key)
{
	#define BOOK_KEYTOSTRING_CASE(KEY) case sf::Keyboard::KEY: return #KEY;

	switch (key)
	{
		BOOK_KEYTOSTRING_CASE(Unknown)
		BOOK_KEYTOSTRING_CASE(A)
		BOOK_KEYTOSTRING_CASE(B)
		BOOK_KEYTOSTRING_CASE(C)
		BOOK_KEYTOSTRING_CASE(D)
		BOOK_KEYTOSTRING_CASE(E)
		BOOK_KEYTOSTRING_CASE(F)
		BOOK_KEYTOSTRING_CASE(G)
		BOOK_KEYTOSTRING_CASE(H)
		BOOK_KEYTOSTRING_CASE(I)
		BOOK_KEYTOSTRING_CASE(J)
		BOOK_KEYTOSTRING_CASE(K)
		BOOK_KEYTOSTRING_CASE(L)
		BOOK_KEYTOSTRING_CASE(M)
		BOOK_KEYTOSTRING_CASE(N)
		BOOK_KEYTOSTRING_CASE(O)
		BOOK_KEYTOSTRING_CASE(P)
		BOOK_KEYTOSTRING_CASE(Q)
		BOOK_KEYTOSTRING_CASE(R)
		BOOK_KEYTOSTRING_CASE(S)
		BOOK_KEYTOSTRING_CASE(T)
		BOOK_KEYTOSTRING_CASE(U)
		BOOK_KEYTOSTRING_CASE(V)
		BOOK_KEYTOSTRING_CASE(W)
		BOOK_KEYTOSTRING_CASE(X)
		BOOK_KEYTOSTRING_CASE(Y)
		BOOK_KEYTOSTRING_CASE(Z)
		BOOK_KEYTOSTRING_CASE(Num0)
		BOOK_KEYTOSTRING_CASE(Num1)
		BOOK_KEYTOSTRING_CASE(Num2)
		BOOK_KEYTOSTRING_CASE(Num3)
		BOOK_KEYTOSTRING_CASE(Num4)
		BOOK_KEYTOSTRING_CASE(Num5)
		BOOK_KEYTOSTRING_CASE(Num6)
		BOOK_KEYTOSTRING_CASE(Num7)
		BOOK_KEYTOSTRING_CASE(Num8)
		BOOK_KEYTOSTRING_CASE(Num9)
		BOOK_KEYTOSTRING_CASE(Escape)
		BOOK_KEYTOSTRING_CASE(LControl)
		BOOK_KEYTOSTRING_CASE(LShift)
		BOOK_KEYTOSTRING_CASE(LAlt)
		BOOK_KEYTOSTRING_CASE(LSystem)
		BOOK_KEYTOSTRING_CASE(RControl)
		BOOK_KEYTOSTRING_CASE(RShift)
		BOOK_KEYTOSTRING_CASE(RAlt)
		BOOK_KEYTOSTRING_CASE(RSystem)
		BOOK_KEYTOSTRING_CASE(Menu)
		BOOK_KEYTOSTRING_CASE(LBracket)
		BOOK_KEYTOSTRING_CASE(RBracket)
		BOOK_KEYTOSTRING_CASE(SemiColon)
		BOOK_KEYTOSTRING_CASE(Comma)
		BOOK_KEYTOSTRING_CASE(Period)
		BOOK_KEYTOSTRING_CASE(Quote)
		BOOK_KEYTOSTRING_CASE(Slash)
		BOOK_KEYTOSTRING_CASE(BackSlash)
		BOOK_KEYTOSTRING_CASE(Tilde)
		BOOK_KEYTOSTRING_CASE(Equal)
		BOOK_KEYTOSTRING_CASE(Dash)
		BOOK_KEYTOSTRING_CASE(Space)
		BOOK_KEYTOSTRING_CASE(Return)
		BOOK_KEYTOSTRING_CASE(BackSpace)
		BOOK_KEYTOSTRING_CASE(Tab)
		BOOK_KEYTOSTRING_CASE(PageUp)
		BOOK_KEYTOSTRING_CASE(PageDown)
		BOOK_KEYTOSTRING_CASE(End)
		BOOK_KEYTOSTRING_CASE(Home)
		BOOK_KEYTOSTRING_CASE(Insert)
		BOOK_KEYTOSTRING_CASE(Delete)
		BOOK_KEYTOSTRING_CASE(Add)
		BOOK_KEYTOSTRING_CASE(Subtract)
		BOOK_KEYTOSTRING_CASE(Multiply)
		BOOK_KEYTOSTRING_CASE(Divide)
		BOOK_KEYTOSTRING_CASE(Left)
		BOOK_KEYTOSTRING_CASE(Right)
		BOOK_KEYTOSTRING_CASE(Up)
		BOOK_KEYTOSTRING_CASE(Down)
		BOOK_KEYTOSTRING_CASE(Numpad0)
		BOOK_KEYTOSTRING_CASE(Numpad1)
		BOOK_KEYTOSTRING_CASE(Numpad2)
		BOOK_KEYTOSTRING_CASE(Numpad3)
		BOOK_KEYTOSTRING_CASE(Numpad4)
		BOOK_KEYTOSTRING_CASE(Numpad5)
		BOOK_KEYTOSTRING_CASE(Numpad6)
		BOOK_KEYTOSTRING_CASE(Numpad7)
		BOOK_KEYTOSTRING_CASE(Numpad8)
		BOOK_KEYTOSTRING_CASE(Numpad9)
		BOOK_KEYTOSTRING_CASE(F1)
		BOOK_KEYTOSTRING_CASE(F2)
		BOOK_KEYTOSTRING_CASE(F3)
		BOOK_KEYTOSTRING_CASE(F4)
		BOOK_KEYTOSTRING_CASE(F5)
		BOOK_KEYTOSTRING_CASE(F6)
		BOOK_KEYTOSTRING_CASE(F7)
		BOOK_KEYTOSTRING_CASE(F8)
		BOOK_KEYTOSTRING_CASE(F9)
		BOOK_KEYTOSTRING_CASE(F10)
		BOOK_KEYTOSTRING_CASE(F11)
		BOOK_KEYTOSTRING_CASE(F12)
		BOOK_KEYTOSTRING_CASE(F13)
		BOOK_KEYTOSTRING_CASE(F14)
		BOOK_KEYTOSTRING_CASE(F15)
		BOOK_KEYTOSTRING_CASE(Pause)
	}

	return "";
}

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

void centerOrigin(sf::Shape& shape)
{
  sf::FloatRect bounds = shape.getLocalBounds();
  shape.setOrigin(std::floor(bounds.width / 2.f), std::floor(bounds.height / 2.f));
}

void setSize(sf::Sprite& sprite, const sf::Vector2f& desiredSize)
{
  sprite.setScale(desiredSize.x / sprite.getTexture()->getSize().x,
                  desiredSize.y / sprite.getTexture()->getSize().y);
}

float toDegree(float radian)
{
	return 180.f / 3.141592653589793238462643383f * radian;
}

float toRadian(float degree)
{
	return 3.141592653589793238462643383f / 180.f * degree;
}

int randomInt(int exclusiveMax)
{
	std::uniform_int_distribution<> distr(0, exclusiveMax - 1);
	return distr(RandomEngine);
}

float length(sf::Vector2f vector)
{
	return std::sqrt(vector.x * vector.x + vector.y * vector.y);
}

sf::Vector2f unitVector(sf::Vector2f vector)
{
	assert(vector != sf::Vector2f(0.f, 0.f));
	return vector / length(vector);
}

float toTrigAngle(float angleInDegreesSFML)
{
  if (angleInDegreesSFML <= 90)
    return (90 - angleInDegreesSFML);
  else /* (angleInDegreesSFML > 90) */
    return (450 - angleInDegreesSFML);
}

float fixAngleToRangeDegrees(float angleInDegrees)
{
  while (angleInDegrees < 0.f)
    angleInDegrees += 360.f;
  while (angleInDegrees >= 360.f)
    angleInDegrees -= 360.f;

  return angleInDegrees;
}

float fixAngleToRangeRadians(float angleInRadians)
{
  while (angleInRadians < 0.f)
    angleInRadians += 2.f * 3.141592653589793238462643383f;
  while (angleInRadians >= 2.f * 3.141592653589793238462643383f)
    angleInRadians -= 2.f * 3.141592653589793238462643383f;

  return angleInRadians;
}

float arctan(float height, float width)
{
  // Because the default range of std::atan only contains geometric
  // quadrants 1 and 4, we check if, based on the height and
  // width, the angle should actually be in quadrants 2 or 3 (or
  // still 1 or 4).
  // This method achieves the full range of [0, 2 * pi].

  // Deal with either a height or width of 0;
  // implicitly avoids risk of division by zero
  if (height == 0 && width > 0)
    return 0.f;
  else if (height > 0 && width == 0)
    return 3.141592653589793238462643383f / 2.f;
  else if (height == 0 && width < 0)
    return 3.141592653589793238462643383f;
  else if (height < 0 && width == 0)
    return 3.141592653589793238462643383f * 3.f / 2.f;
  else if (height == 0 && width == 0)
    return 0.f;

  // Get the angle in radians within default range [-pi, pi]
  float angle = std::atan(height / width);
  angle = fixAngleToRangeRadians(angle);

  // Quadrant 1:
  if (height > 0 && width > 0)
    return angle;
  
  // Quadrant 2 (treated as Quadrant 4 by std::atan):
  else if (height > 0 && width < 0)
    return angle - 3.141592653589793238462643383f;

  // Quadrant 3 (treated as Quadrant 1 by std::atan):
  else if (height < 0 && width < 0)
    return angle + 3.141592653589793238462643383f;

  // Quadrant 4:
  else /* (height < 0 && width > 0) */
    return angle;
}