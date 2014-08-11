#ifndef TANKS_LEVELIDENTIFIERS_HPP
#define TANKS_LEVELIDENTIFIERS_HPP


namespace Levels
{
  enum ID
  {
    // For organizing World data;
    // use "Main" to denote default game mode
    MainOne,
    MainTwo,
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
    Default,
    Survival,
    TypeCount
  };

} // namespace GameType

#endif // TANKS_LEVELIDENTIFIERS_HPP