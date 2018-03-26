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
		SimulatedEntity(Vec2d const& pos, double energy, sf::Texture& texture);

		/** SFML draw function */
		void drawOn(sf::RenderTarget&);

		/** aging function*/
		void update(sf::Time dt);
	protected:
		sf::Texture& texture; //!< Texture SFML
		sf::Sprite entitySprite; //!< Sprite SFML

		Vec2d pos; 			//!< Membre "position"
		Angle angle; 		//!< Membre "angle"

		Box* box; 			//!< Pointeur "boite"

		double energy; 	//!< Membre "énergie"
		sf::Time age; 	//!< Membre "age"
};

#endif // SIMULATEDENTITY_HPP
