#ifndef TANKS_BLOCKNODE_HPP
#define TANKS_BLOCKNODE_HPP

#include <Tanks/SceneNode.hpp>
#include <Tanks/Block.hpp>
#include <Tanks/ResourceIdentifiers.hpp>

#include <SFML/Graphics/VertexArray.hpp>

#include <forward_list>

// The blocks contained in this node act as walls
class BlockNode : public SceneNode
{
  public:
                            BlockNode(Block::Type type);

    void                    addBlock(sf::Vector2f size, sf::Vector2f position);
    Block::Type             getBlockType() const;
    virtual unsigned int    getCategory() const;


	private:
		virtual void			updateCurrent(sf::Time dt, CommandQueue& commands);
		virtual void			drawCurrent(sf::RenderTarget& target, 
                                  sf::RenderStates states) const;
		
		void					addVertex(float worldX, float worldY, 
                            const sf::Color& color) const;
		void					computeVertices() const;


  private:
    std::forward_list<Block>       mBlocks;
    Block::Type                    mType;

    mutable sf::VertexArray     mVertexArray;
    mutable bool                mNeedsVertexUpdate;
};

#endif