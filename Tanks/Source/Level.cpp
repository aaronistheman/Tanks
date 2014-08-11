#include <Tanks/Level.hpp>

#include <cassert>


Level::Level(GameType::ID gameType)
  // initialize mGameType first so that getFirstLevel() can be used
  : mGameType(gameType)
{
  mLevel = getFirstLevel();
}

Levels::ID Level::getLevel() const
{
  return mLevel;
}

void Level::incrementLevel()
{
  // Do not increment the level if it is last
  if (isLastLevel())
    return;

  // Assume enum Levels::ID is ordered in an increment-friendly way
  mLevel = Levels::ID(mLevel + 1);
}

void Level::resetLevel()
{
  mLevel = getFirstLevel();
}

GameType::ID Level::getGameType() const
{
  return mGameType;
}

void Level::setGameType(GameType::ID gameType)
{
  mGameType = gameType;
  resetLevel();
}

bool Level::isLastLevel() const
{
  // returns true if is last level in a particular game type
  switch (mGameType)
  {
    case GameType::Default:
      return (mLevel == Levels::MainLast);
    case GameType::Survival:
      return (mLevel == Levels::Survival); // Survival mode only has one level

    default:
      // mGameType must have went bad; terminate
      assert(false);
  }
}

Levels::ID Level::getFirstLevel() const
{
  switch (mGameType)
  {
    case GameType::Default:
      return Levels::MainOne;
    case GameType::Survival:
      return Levels::Survival;

    default:
      // mGameType must have went bad; terminate
      assert(false);
  }
}