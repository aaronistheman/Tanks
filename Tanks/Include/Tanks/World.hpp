#ifndef TANKS_WORLD_HPP
#define TANKS_WORLD_HPP

#include <Tanks/ResourceHolder.hpp>
#include <Tanks/ResourceIdentifiers.hpp>
#include <Tanks/SceneNode.hpp>
#include <Tanks/SpriteNode.hpp>
#include <Tanks/CommandQueue.hpp>
#include <Tanks/Command.hpp>
#include <Tanks/SpawnPoint.hpp>
#include <Tanks/Level.hpp>
#include <Tanks/DataTables.hpp>

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <array>
#include <queue>


// Forward declaration
namespace sf
{
	class RenderWindow;
}

class World : private sf::NonCopyable
{
  public:
		explicit							World(sf::RenderWindow& window, FontHolder& fonts,
                                GameType::GameType gameType);
		void								update(sf::Time dt);
		void								draw();
		
		CommandQueue&						getCommandQueue();

		bool 								hasAlivePlayer() const;
    bool                hasAliveEnemy() const;


	private:
		void								loadTextures();
		void								adaptTankPositions();
		void								adaptPlayerVelocity();
    void                handleCollisions();
		
    Level::Level        getFirstLevel();
    void								buildScene();
    void                addEnemies();
    void                addEnemy(Tank::Type type, 
                                 sf::Vector2f spawnPosition,
                                 float rotation, 
                                 float numberOfKillsToAppear);
    void                spawnEnemies();
    void                addBlocks();
    void                addBlock(Block::Type type,
                                 sf::Vector2f spawnPosition,
                                 sf::Vector2f size);
    void                spawnBlocks();
    void                destroyProjectilesOutsideView();
    void                updateEnemyCounters();
    void                updateHuntingEnemies();
    sf::FloatRect       getViewBounds() const;


	private:
		enum Layer
		{
      // Order these layers from least to most visible
			Background,
			MainGround,
      UpperGround,
			LayerCount
		};


	private:
		sf::RenderWindow&					mWindow;
		sf::View							mWorldView;
    WorldView::Type       mViewType;
		TextureHolder						mTextures;
    FontHolder&             mFonts;
    GameType::GameType      mGameType;
    Level::Level            mLevel;

		SceneNode							mSceneGraph;
		std::array<SceneNode*, LayerCount>	mSceneLayers;
		CommandQueue						mCommandQueue;

		sf::FloatRect						mWorldBounds;
		float								mScrollSpeed;
		Tank*							mPlayerTank;

    std::vector<EnemySpawnPoint>     mEnemySpawnPoints;
    std::vector<BlockSpawnPoint>     mBlockSpawnPoints;
    std::vector<Tank*>        mHuntingEnemies;
    int                       mNumberOfDestroyedEnemies;
    int                       mNumberOfAliveEnemies;
};

#endif // TANKS_WORLD_HPP
