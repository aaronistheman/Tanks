#ifndef TANKS_PLAYER_HPP
#define TANKS_PLAYER_HPP

#include <Tanks/Command.hpp>
#include <Tanks/Level.hpp>

#include <SFML/Window/Event.hpp>

#include <map>


class CommandQueue;

class Player
{
	public:
		enum Action
		{
			MoveLeft,
			MoveRight,
			MoveUp,
			MoveDown,
      RotateLeft,
      RotateRight,
      Fire,
			ActionCount
		};

    enum LevelStatus
    {
      LevelRunning,
      LevelSuccess,
      LevelFailure
    };


	public:
								Player();

		void					handleEvent(const sf::Event& event, CommandQueue& commands);
		void					handleRealtimeInput(CommandQueue& commands);

		void					assignKey(Action action, sf::Keyboard::Key key);
		sf::Keyboard::Key		getAssignedKey(Action action) const;

    void 					setLevelStatus(LevelStatus status);
		LevelStatus 			getLevelStatus() const;
    void          setLevel(Level::ID level);
    Level::ID     getLevel() const;
    void          setGameType(GameType::ID gameType);
    GameType::ID    getGameType();


	private:
		void					initializeActions();
		static bool				isRealtimeAction(Action action);


	private:
		std::map<sf::Keyboard::Key, Action>		mKeyBinding;
		std::map<Action, Command>				mActionBinding;
		LevelStatus 							mCurrentLevelStatus;
    Level::ID                   mLevel;
    GameType::ID                mGameType;
};

#endif // TANKS_PLAYER_HPP
