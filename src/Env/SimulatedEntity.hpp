#ifndef SIMULATEDENTITY_HPP
#define SIMULATEDENTITY_HPP

#include <SFML/Graphics.hpp>
#include <Utility/Utility.hpp>
#include "Box.hpp"
#include <Utility/Vec2d.hpp>

class SimulatedEntity
{
	public:
		/** constructor */
		SimulatedEntity(Vec2d const& pos, double energy, sf::Texture* texture);

		/** SFML draw function */
		void drawOn(sf::RenderTarget&);

		/** aging function*/
		void update(sf::Time dt);
	protected:
		Vec2d pos;
		Angle angle;

		Box* box; //!< Current box

		double energy; //!< Current life force or nutritivity
		sf::Time age; //!< age incremented by update()
		sf::Time longevity; //!< Time of certain DEATH
		
		/** SFML variables */
		sf::Texture* texture;
		sf::Sprite entitySprite;
	private:
		sf::Text text;
};

#endif // SIMULATEDENTITY_HPP
