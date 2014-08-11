#ifndef TANKS_LEVEL_HPP
#define TANKS_LEVEL_HPP

namespace Level
{
  enum ID
  {
    // For organizing World data;
    // use "Main" to denote default game mode
    None,
    MainOne,
    MainTwo,
    MainLast,
    Survival,
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

Level::ID       getNextLevel(Level::ID currentLevel, GameType::ID gameType);
bool            isLastLevel(Level::ID level, GameType::ID gameType);
GameType::ID    getGameType(Level::ID level);

#endif // TANKS_LEVEL_HPP