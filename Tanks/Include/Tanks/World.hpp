#ifndef TANKS_WORLD_HPP
#define TANKS_WORLD_HPP

#include <Tanks/ResourceHolder.hpp>
#include <Tanks/ResourceIdentifiers.hpp>
#include <Tanks/SceneNode.hpp>
#include <Tanks/SpriteNode.hpp>
#include <Tanks/Tank.hpp>
#include <Tanks/CommandQueue.hpp>
#include <Tanks/Command.hpp>

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
		explicit							World(sf::RenderWindow& window, FontHolder& fonts);
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
		
    void								buildScene();
    void                addEnemies();
    void                addEnemy(Tank::Type type, 
                                 sf::Vector2f spawnPosition,
                                 float rotation, 
                                 float numberOfKillsToAppear);
    void                spawnEnemies();
    void                spawnBlocks();
    void                destroyProjectilesOutsideView();
    void                updateDestroyedEnemiesCounter();
    void                updateActiveEnemiesVector();
    void                updateHuntingEnemies();
    sf::FloatRect       getViewBounds() const;


	private:
		enum Layer
		{
			Background,
			Ground,
			LayerCount
		};

    struct SpawnPoint
    {
      SpawnPoint(Tank::Type type, float x, float y, float rotation,
                 float numberOfKills)
        : type(type)
        , x(x)
        , y(y)
        , r(rotation)
        , n(numberOfKills)
      {
      }

      Tank::Type type;
      float x;
      float y;
      float r;
      float n;
    };


	private:
		sf::RenderWindow&					mWindow;
		sf::View							mWorldView;
		TextureHolder						mTextures;
    FontHolder&             mFonts;

		SceneNode							mSceneGraph;
		std::array<SceneNode*, LayerCount>	mSceneLayers;
		CommandQueue						mCommandQueue;

		sf::FloatRect						mWorldBounds;
		float								mScrollSpeed;
		Tank*							mPlayerTank;

    std::vector<SpawnPoint>     mEnemySpawnPoints;
		std::vector<Tank*>				mActiveEnemies;
    std::vector<Tank*>        mHuntingEnemies;
    int                       mNumberOfDestroyedEnemies;
};

#endif // TANKS_WORLD_HPP
