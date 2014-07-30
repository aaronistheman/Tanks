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


	private:
		void								loadTextures();
		void								adaptPlayerPosition();
		void								adaptPlayerVelocity();
    void                handleCollisions();
		
    void								buildScene();
    void                addEnemies();
    void                addEnemy(Tank::Type type, float relX, float relY);
    void                spawnEnemies();
    void                destroyProjectilesOutsideView();
    sf::FloatRect       getViewBounds() const;
    sf::FloatRect       getBattlefieldBounds() const;


	private:
		enum Layer
		{
			Background,
			Air,
			LayerCount
		};

    struct SpawnPoint
    {
      SpawnPoint(Tank::Type type, float x, float y)
        : type(type)
        , x(x)
        , y(y)
      {
      }

      Tank::Type type;
      float x;
      float y;
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
		sf::Vector2f						mSpawnPosition;
		float								mScrollSpeed;
		Tank*							mPlayerTank;

    std::vector<SpawnPoint>     mEnemySpawnPoints;
};

#endif // TANKS_WORLD_HPP
