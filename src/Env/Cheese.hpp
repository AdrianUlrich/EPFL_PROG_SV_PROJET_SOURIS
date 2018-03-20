#ifndef CHEESE_HPP
#define CHEESE_HPP

#include "SimulatedEntity.hpp"


class Cheese : public SimulatedEntity
{
	public:
		/** Default constructor */
		Cheese();

		/** masked draw function */
		void drawOn(sf::RenderTarget&);
};

#endif // CHEESE_HPP
