#ifndef MOUSE_HPP
#define MOUSE_HPP

#include "Animal.hpp"


class Mouse : public Animal
{
	public:
		/** Default constructor */
		Mouse();

		void drawOn(sf::RenderTarget);
	protected:

	private:
};

#endif // MOUSE_HPP
