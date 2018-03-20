#ifndef MOUSE_HPP
#define MOUSE_HPP

#include "Animal.hpp"


class Mouse : public Animal
{
	public:
		/** Default constructor */
		Mouse();

		/** masked draw function */
		void drawOn(sf::RenderTarget);
};

#endif // MOUSE_HPP
