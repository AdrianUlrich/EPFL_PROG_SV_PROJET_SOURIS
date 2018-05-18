#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include "SimulatedEntity.hpp"
//#include "Organ.hpp"
class Organ;
#include <Utility/Utility.hpp>
#include <Random/Random.hpp>

class Organ;

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

		~Animal();
	
		void drawOn(sf::RenderTarget&) override;

		void update(sf::Time) override;
		void updateState();
		
		virtual bool canBeConfinedIn(Box*) const override;
		void fillBox() {box->addOccupant();}

		/** movement-related methods (called by Animal::update) */
		void move(sf::Time);
		void move(Vec2d const&,sf::Time);
		Vec2d getSpeedVector() const {return getHeading()*velocite;}
		virtual double getMaxSpeed() const = 0;
		virtual double getLossFactor() const = 0;
		virtual double getMass() const = 0;
		Angle getNewRotation() const {return DEG_TO_RAD * piecewise_linear(intervals,probs);}

		/** nutrition-related methods (called by Animal::update) */
		bool isSatiated() const;
		Vec2d getFoodPull() const;
		virtual Quantity getBite() const = 0; //! each different animal has different biteSize
		void feed();

		/** champs de vision */
		virtual double getViewRange() const {return AngleVision;}
		virtual double getViewDistance() const {return DistanceVision;}


		/** detection d'une cible */
		bool isTargetInSight(const Vec2d& position);
		void setTarget(SimulatedEntity* a) {cible_actuelle=a;}

  
		/** SFML draw (Organ* Animal::foie) on window */
		void drawCurrentOrgan(sf::RenderTarget&);
		void updateOrgan();

		/** pure virtual inherited isDead() not yet redefined */
		/** method to ACK that another entity died */
		virtual void isDead(SimulatedEntity*) override;
		
		
	protected:
		virtual void setRotation(Angle a);
		virtual void setOrgan(Organ*o);

	private:
		State etat;
		//double maxSpeed;

		static Intervals intervals;
		static Probs probs;

		double AngleVision;
		double DistanceVision;
		double velocite;
		sf::Time compteur;
  
		SimulatedEntity* cible_actuelle;
  
		Organ* foie;
};

#endif // ANIMAL_HPP
