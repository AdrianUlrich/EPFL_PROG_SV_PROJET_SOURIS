#ifndef CHEESE_HPP
#define CHEESE_HPP

#include "SimulatedEntity.hpp"


class Cheese : public SimulatedEntity
{
	public:
		/** constructor */
		Cheese(Vec2d const&);

		/** masking draw function */
		void drawOn(sf::RenderTarget&) override;

		/** get eaten you camembert */
		Quantity provideEnergy(Quantity);

		/** masking isDead pure virtual method */
		bool isDead() const override;

		/** eatable */
		bool eatable(SimulatedEntity const* ntt) const override {return ntt->eatableBy(this);}
		bool eatableBy(Cheese const*) const override {return false;}
		bool eatableBy(Mouse const*) const override {return true;}

	//private:
		//double maxSide;
};

#endif // CHEESE_HPP
