#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include "SimulatedEntity.hpp"
#include <Utility/Utility.hpp>

enum State
{
	FOOD_IN_SIGHT, // nourriture en vue (il sera attiré par la nourriture)
	FEEDING,       // en train de manger (là en principe il arrête de se déplacer)
	WANDERING,     // déambule
	IDLE           // au repos
};

class Animal : public SimulatedEntity /// ABSTRACT
{
	public:
		/** constructor */
		Animal(Vec2d const& pos, double energy, sf::Texture* texture, double rayon);

		void update(sf::Time) override;
		void updateState();
		void move(sf::Time);
		Vec2d getSpeedVector() {return getHeading()*velocite;}
		virtual double getMaxSpeed() const = 0;
		//Angle getNewR

		/** pure virtual inherited isDead not yet redefined */
	private:
		State etat;
		double velocite;
		//double maxSpeed;
		static Intervals intervals;
		static Probs probs;
};

#endif // ANIMAL_HPP
