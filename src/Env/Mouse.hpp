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
		virtual bool isDead() const override;

		/** eatable */
		bool eatable(SimulatedEntity const*) const override;
		bool eatableBy(Cheese const*) const override;
		bool eatableBy(Mouse const*) const override;

		/** masking getMaxSpeed pure virtual method */
		virtual double getMaxSpeed() const override;
		virtual double getLossFactor() const override;

	//private:
		//double mouseSize;
};

#endif // MOUSE_HPP
