#ifndef SIMULATEDENTITY_HPP
#define SIMULATEDENTITY_HPP

#include <SFML/Graphics.hpp>

class SimulatedEntity
{
	public:
		/** Default constructor */
		SimulatedEntity(Vec2d pos, double energy);

		/** SFML draw function */
		void drawOn(sf::RenderTarget);

	protected:
		sf::Texture texture; //!< Texture SFML

		Vec2d pos; 			//!< Membre "position"
		Angle angle; 		//!< Membre "angle"

		Box* box; 			//!< Pointeur "boite"

		double energy; 	//!< Membre "énergie"
		sf::Time age; 	//!< Membre "age"
};

#endif // SIMULATEDENTITY_HPP
