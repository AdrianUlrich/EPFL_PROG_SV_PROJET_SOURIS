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
		
		/** eatable */
		bool eatable(SimulatedEntity const*);
		bool eatableBy(Cheese const*);
		bool eatableBy(Mouse const*);
		
		
	//private:
		//double mouseSize;
};

#endif // MOUSE_HPP
