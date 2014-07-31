#include <Tanks/World.hpp>
#include <Tanks/Foreach.hpp>
#include <Tanks/Category.hpp>

#include <SFML/Graphics/RenderWindow.hpp>

#include <algorithm>
#include <cmath>


World::World(sf::RenderWindow& window, FontHolder& fonts)
: mWindow(window)
, mWorldView(window.getDefaultView())
, mFonts(fonts)
, mTextures() 
, mSceneGraph()
, mSceneLayers()
, mWorldBounds(0.f, 0.f, mWorldView.getSize().x, mWorldView.getSize().y)
, mScrollSpeed(0.0f)
, mPlayerTank(nullptr)
{
	loadTextures();
	buildScene();

	// Prepare the view
	mWorldView.setCenter(mWorldView.getSize().x / 2.f, 
                       mWorldBounds.height - mWorldView.getSize().y / 2.f);
}

void World::update(sf::Time dt)
{
	// Scroll the world, reset player velocity and rotation offset
	mWorldView.move(0.f, mScrollSpeed * dt.asSeconds());	
	mPlayerTank->setVelocity(0.f, 0.f);
  mPlayerTank->setRotationOffset(0.f);

  destroyProjectilesOutsideView();

	// Forward commands to scene graph, adapt velocity (scrolling, diagonal correction)
	while (!mCommandQueue.isEmpty())
		mSceneGraph.onCommand(mCommandQueue.pop(), dt);
	adaptPlayerVelocity();

  // Collision detection and response (may destroy entities)
	handleCollisions();

  // Remove all destroyed entities, create new ones
	mSceneGraph.removeWrecks();
  spawnEnemies();

	// Regular update step, adapt position (correct if outside view)
	mSceneGraph.update(dt, mCommandQueue);
	adaptPlayerPosition();
}

void World::draw()
{
	mWindow.setView(mWorldView);
	mWindow.draw(mSceneGraph);
}

CommandQueue& World::getCommandQueue()
{
	return mCommandQueue;
}

bool World::hasAlivePlayer() const
{
	return !mPlayerTank->isMarkedForRemoval();
}

void World::loadTextures()
{
	mTextures.load(Textures::DefaultTank, "Media/Textures/DefaultTank.png");
  mTextures.load(Textures::EnemyTank, "Media/Textures/EnemyTank.png");
  mTextures.load(Textures::Metal, "Media/Textures/Metal.png");

  mTextures.load(Textures::Bullet, "Media/Textures/Bullet.png");
}

void World::adaptPlayerPosition()
{
	// Keep player's position inside the screen bounds, at least borderDistance units from the border
	sf::FloatRect viewBounds(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());
  const float borderDistance = 50.f;

	sf::Vector2f position = mPlayerTank->getPosition();
	position.x = std::max(position.x, viewBounds.left + borderDistance);
	position.x = std::min(position.x, viewBounds.left + viewBounds.width - borderDistance);
	position.y = std::max(position.y, viewBounds.top + borderDistance);
	position.y = std::min(position.y, viewBounds.top + viewBounds.height - borderDistance);
	mPlayerTank->setPosition(position);
}

void World::adaptPlayerVelocity()
{
	sf::Vector2f velocity = mPlayerTank->getVelocity();

	// If moving diagonally, reduce velocity (to have always same velocity)
	if (velocity.x != 0.f && velocity.y != 0.f)
		mPlayerTank->setVelocity(velocity / std::sqrt(2.f));

	// Add scrolling velocity
	mPlayerTank->accelerate(0.f, mScrollSpeed);
}

bool matchesCategories(SceneNode::Pair& colliders,
                       Category::Type type1,
                       Category::Type type2)
{
  unsigned int category1 = colliders.first->getCategory();
  unsigned int category2 = colliders.second->getCategory();

  if (type1 & category1 && type2 & category2)
  {
    return true;
  }
  else if (type1 & category2 && type2 & category1)
  {
    // Flip the elements of the pair to avoid having both
    // A-B and B-A collisions recorded
    std::swap(colliders.first, colliders.second);
    return true;
  }
  else
  {
    return false;
  }
}

void World::handleCollisions()
{
  std::set<SceneNode::Pair> collisionPairs;
  mSceneGraph.checkSceneCollision(mSceneGraph, collisionPairs);

  FOREACH(SceneNode::Pair pair, collisionPairs)
  {
    if (matchesCategories(pair, Category::PlayerTank, Category::EnemyTank))
    {
      auto& player = static_cast<Tank&>(*pair.first);
      auto& enemy = static_cast<Tank&>(*pair.second);

      // player.setPosition(player.getPosition().x - 10.f, player.getPosition().y - 10.f);
      // player.setVelocity(-player.getVelocity());
      player.damage(enemy.getHitpoints());
      enemy.destroy();
    }
    else if (matchesCategories(pair, Category::EnemyTank, 
                               Category::AlliedProjectile)
             || matchesCategories(pair, Category::PlayerTank,
                                  Category::EnemyProjectile))
    {
      auto& tank = static_cast<Tank&>(*pair.first);
      auto& projectile = static_cast<Projectile&>(*pair.second);

      tank.damage(projectile.getDamage());
      projectile.destroy();
    }
    else if (matchesCategories(pair, Category::AlliedProjectile,
                               Category::EnemyProjectile))
    {
      auto& projectile1 = static_cast<Projectile&>(*pair.first);
      auto& projectile2 = static_cast<Projectile&>(*pair.second);

      projectile1.destroy();
      projectile2.destroy();
    }
  }
}

void World::buildScene()
{
	// Initialize the different layers
	for (std::size_t i = 0; i < LayerCount; ++i)
	{
		Category::Type category = (i == Air) ? Category::SceneAirLayer : Category::None;

		SceneNode::Ptr layer(new SceneNode(category));
		mSceneLayers[i] = layer.get();

		mSceneGraph.attachChild(std::move(layer));
	}

	// Prepare the tiled background
	sf::Texture& texture = mTextures.get(Textures::Metal);
	sf::IntRect textureRect(mWorldBounds);
	texture.setRepeated(true);

	// Add the background sprite to the scene
	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
	backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
	mSceneLayers[Background]->attachChild(std::move(backgroundSprite));

	// Add player's tank
	std::unique_ptr<Tank> leader(new Tank(Tank::DefaultTank, mTextures, mFonts));
	mPlayerTank = leader.get();
	mPlayerTank->setPosition(sf::Vector2f(800.f, 60.f));
  mPlayerTank->setRotation(180.f);
	mSceneLayers[Air]->attachChild(std::move(leader));

	// Add enemy aircraft
	addEnemies();
}

void World::addEnemies()
{
  // Add enemies to the spawn point container
  addEnemy(Tank::EnemyTank, sf::Vector2f(300.f, 250.f), 90.f);
  addEnemy(Tank::EnemyTank, sf::Vector2f(950.f, 340.f), 270.f);
  addEnemy(Tank::EnemyTank, sf::Vector2f(400.f, 500.f), 45.f);
  addEnemy(Tank::EnemyTank, sf::Vector2f(800.f, 480.f), 270.f);

  // Sort all enemies according to their y value, such that lower enemies are checked first for spawning
	std::sort(mEnemySpawnPoints.begin(), mEnemySpawnPoints.end(), [] (SpawnPoint lhs, SpawnPoint rhs)
	{
		return lhs.y < rhs.y;
	});
}

void World::addEnemy(Tank::Type type, sf::Vector2f spawnPosition,
                     float rotation)
{
	SpawnPoint spawn(type, spawnPosition.x, spawnPosition.y, rotation);
	mEnemySpawnPoints.push_back(spawn);
}

void World::spawnEnemies()
{
  while (!mEnemySpawnPoints.empty())
  {
    SpawnPoint spawn = mEnemySpawnPoints.back();

    std::unique_ptr<Tank> enemy(new Tank(spawn.type, mTextures, mFonts));
    enemy->setPosition(spawn.x, spawn.y);
    enemy->setRotation(spawn.r);

    mSceneLayers[Air]->attachChild(std::move(enemy));

    mEnemySpawnPoints.pop_back();
  }
}

void World::destroyProjectilesOutsideView()
{
  Command command;
  command.category = Category::Projectile;
  command.action = derivedAction<Projectile>(
    [this] (Projectile& p, sf::Time)
  {
    if (!getViewBounds().intersects(p.getBoundingRect()))
      p.destroy();
  });

  mCommandQueue.push(command);
}

sf::FloatRect World::getViewBounds() const
{
  // sf::FloatRect rect(mWorldView.getCenter() - mWorldView.getSize() / 2.f + sf::Vector2f(100.f, 100.f), 
  //                    mWorldView.getSize() - sf::Vector2f(200.f, 200.f));
  // return rect;

	return sf::FloatRect(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());
}