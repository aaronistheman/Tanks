#ifndef TANKS_LEVELIDENTIFIERS_HPP
#define TANKS_LEVELIDENTIFIERS_HPP


namespace Levels
{
  enum ID
  {
    None,
    MainOne,
    MainTwo,
    MainThree,
    MainLast,
    Survival = 100, // prevent accidental incrementation to a different
                    // game mode
    TypeCount
  };
  
} // namespace Level

namespace GameType
{
  enum ID
  {
    None,
    Default,
    Survival,
    TypeCount
  };

} // namespace GameType

#endif // TANKS_LEVELIDENTIFIERS_HPP