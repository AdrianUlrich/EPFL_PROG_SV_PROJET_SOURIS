#ifndef CHEESE_HPP
#define CHEESE_HPP

#include "SimulatedEntity.hpp"


class Cheese : public SimulatedEntity
{
	public:
		/** Default constructor */
		Cheese();

		/** masking draw function */
		void drawOn(sf::RenderTarget&);
	private:
    double maxSide;
};

#endif // CHEESE_HPP
