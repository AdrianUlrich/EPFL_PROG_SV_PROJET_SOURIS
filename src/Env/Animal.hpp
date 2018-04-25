#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include "SimulatedEntity.hpp"
#include <Utility/Utility.hpp>
#include <Random/Random.hpp>


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
		Angle getNewRotation() const {return DEG_TO_RAD * piecewise_linear(intervals,probs);}

		/** pure virtual inherited isDead not yet redefined */
	private:
		State etat;
		//double maxSpeed;

		double velocite;
		static Intervals intervals;
		static Probs probs;
		sf::Time compteur;
};

#endif // ANIMAL_HPP
