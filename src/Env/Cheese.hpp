#ifndef CHEESE_HPP
#define CHEESE_HPP

#include "SimulatedEntity.hpp"


class Cheese : public SimulatedEntity
{
	public:
		/** constructor */
		Cheese(Vec2d const&);

		/** masking draw function */
		void drawOn(sf::RenderTarget&);
	private:
    double maxSide;
};

#endif // CHEESE_HPP
