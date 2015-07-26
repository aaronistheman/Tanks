/*
  Authors of original version: Artur Moreira, Henrik Vogelius Hansson, and
    Jan Haller
*/

#ifndef TANKS_TEXTNODE_HPP
#define TANKS_TEXTNODE_HPP

#include <Tanks/ResourceHolder.hpp>
#include <Tanks/ResourceIdentifiers.hpp>
#include <Tanks/SceneNode.hpp>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>


class TextNode : public SceneNode
{
  public:
    explicit      TextNode(const FontHolder& fonts,
                           const std::string& text);
    void          setString(const std::string& text);

  private:
    virtual void  drawCurrent(sf::RenderTarget& target,
                              sf::RenderStates states) const;

  private:
    sf::Text      mText;
};

#endif // TANKS_TEXTNODE_HPP