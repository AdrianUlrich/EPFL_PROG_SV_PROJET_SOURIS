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

		/** champs de vision */ 
		double getViewRange() const {return AngleVision;} 
		double getViewDistance() const {return DistanceVision;} 
     
		/** pure virtual inherited specificDead not yet redefined */
		
		void drawOn(sf::RenderTarget&) override;
		
	private:
		State etat;
		double velocite;
		//double maxSpeed;
		static Intervals intervals;
		static Probs probs;

		double AngleVision; 
		double DistanceVision; 
};

#endif // ANIMAL_HPP
