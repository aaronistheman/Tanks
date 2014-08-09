#ifndef TANKS_LEVEL_HPP
#define TANKS_LEVEL_HPP

namespace Level
{
  enum Level
  {
    // For organizing World data;
    // use "Main" to denote default game mode
    MainOne,
    MainTwo,
    Survival,
    TypeCount
  };
  
} // namespace Level

namespace GameType
{
  enum GameType
  {
    Default,
    Survival,
    TypeCount
  };

} // namespace GameType

#endif // TANKS_LEVEL_HPP