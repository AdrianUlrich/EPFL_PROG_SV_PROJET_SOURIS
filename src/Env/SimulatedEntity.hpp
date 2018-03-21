#ifndef SIMULATEDENTITY_HPP
#define SIMULATEDENTITY_HPP

#include <SFML/Graphics.hpp>

class SimulatedEntity
{
	public:
		/** Default constructor */
		SimulatedEntity(Vec2d pos, double energy);

		/** SFML draw function */
		void drawOn(sf::RenderTarget&);

		/** aging function*/
		void update(sf::Time dt);
	protected:
		sf::Texture texture; //!< Texture SFML
		sf::Sprite entitySprite; //!< Sprite SFML

		Vec2d pos; 			//!< Membre "position"
		Angle angle; 		//!< Membre "angle"

		Box* box; 			//!< Pointeur "boite"

		double energy; 	//!< Membre "�nergie"
		sf::Time age; 	//!< Membre "age"
};

#endif // SIMULATEDENTITY_HPP
