#ifndef MOUSE_HPP
#define MOUSE_HPP

#include "Animal.hpp"

class Mouse : public Animal
{
	public:
		/** constructor */
		Mouse(Vec2d const&);

		/**	masked draw function*/
		void drawOn(sf::RenderTarget&) override;
		
		/** masking isDead pure virtual method */
		virtual bool specificDead() const override;
		
	//private:
		//double mouseSize;
};

#endif // MOUSE_HPP
