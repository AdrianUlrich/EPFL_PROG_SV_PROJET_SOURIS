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
     		
		void drawOn(sf::RenderTarget&) override;
		
		void update(sf::Time) override;
		void updateState();
		void move(sf::Time);
		Vec2d getSpeedVector() {return getHeading()*velocite;}
		virtual double getMaxSpeed() const = 0;
		virtual double getLossFactor() const = 0;
		Angle getNewRotation() const {return DEG_TO_RAD * piecewise_linear(intervals,probs);}


		/** champs de vision */ 
		virtual double getViewRange() const {return AngleVision;} 
		virtual double getViewDistance() const {return DistanceVision;} 

		
		/** detection d'une cible */
		bool isTargetInSight(const Vec2d& position);
		
		~Animal() {if (box!=nullptr) box->reset();}

		/** pure virtual inherited isDead not yet redefined */
		
	protected:
	
		void setRotation(Angle a) {angle=a;}

	private:
		State etat;
		//double maxSpeed;

		static Intervals intervals;
		static Probs probs;

		double AngleVision; 
		double DistanceVision; 
		double velocite;
		sf::Time compteur;
};

#endif // ANIMAL_HPP
