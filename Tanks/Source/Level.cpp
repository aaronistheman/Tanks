#include <Tanks/Level.hpp>

#include <cassert>


Level::ID getNextLevel(Level::ID currentLevel, GameType::ID gameType)
{
  // Do not change the level if it is last
  if (isLastLevel(currentLevel, gameType))
    return currentLevel;

  // Make sure the current level is of the correct game type
  assert(getGameType(currentLevel) == gameType);

  // Return the next enum
  return Level::ID(currentLevel + 1);
}

bool isLastLevel(Level::ID level, GameType::ID gameType)
{
  switch (gameType)
  {
    case GameType::Default:
      return (level == Level::MainLast);
    case GameType::Survival:
      return (level == Level::Survival);
    default:
      // Game type not found; terminate the program
      assert(false);
  }
}

GameType::ID getGameType(Level::ID level)
{
  if (Level::MainOne <= level && level <= Level::MainLast)
    return GameType::Default;
  else if (Level::Survival)
    return GameType::Survival;

  // Game type not found; terminate the program
  assert(false);
}