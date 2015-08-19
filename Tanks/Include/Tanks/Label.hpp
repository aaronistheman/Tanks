/*
  Authors of original version: Artur Moreira, Henrik Vogelius Hansson, and
    Jan Haller
*/

#ifndef TANKS_LABEL_HPP
#define TANKS_LABEL_HPP

#include <Tanks/Component.hpp>
#include <Tanks/ResourceIdentifiers.hpp>
#include <Tanks/ResourceHolder.hpp>

#include <SFML/Graphics/Text.hpp>


namespace GUI
{

class Label : public Component
{
    public:
        typedef std::shared_ptr<Label> Ptr;
            

	public:
							Label(const std::string& text, const FontHolder& fonts);

        virtual bool		isSelectable() const;
		void				setText(const std::string& text);

        virtual void		handleEvent(const sf::Event& event);


    private:
        void				draw(sf::RenderTarget& target, sf::RenderStates states) const;


    private:
        sf::Text			mText;
};

} // namespace GUI


#endif // TANKS_LABEL_HPP