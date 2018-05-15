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
		bool eatable(SimulatedEntity const* ntt) const override {return ntt->eatableBy(this);}
		bool eatableBy(Cheese const*) const override {return false;}
		bool eatableBy(Mouse const*) const override {return false;}

		/** masking getter pure virtual methods */
		virtual double getMaxSpeed() const override;
		virtual double getLossFactor() const override;
		virtual double getMass() const override;
		virtual Quantity getBite() const override;

	//private:
		//double mouseSize;
};

#endif // MOUSE_HPP
