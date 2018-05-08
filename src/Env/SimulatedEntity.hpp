#ifndef SIMULATEDENTITY_HPP
#define SIMULATEDENTITY_HPP

#include <SFML/Graphics.hpp>
#include <Utility/Utility.hpp>
#include "Box.hpp"
#include "Collider.hpp"
#include <Utility/Vec2d.hpp>

class Mouse;
class Cheese;

class SimulatedEntity : public Collider /// ABSTRACT
{
	public:
		/** constructor */
		SimulatedEntity(Vec2d const& pos, double energy, sf::Texture* texture, double rayon);

		/** SFML draw function */
		virtual void drawOn(sf::RenderTarget&);

		/** aging function*/
		virtual void update(sf::Time);

		/** pure virtual method => abstract class */
		virtual bool isDead() const = 0;

		/** overriding virtual collider getters */
		Vec2d getCenter() const override {return pos;}
		double getRadius() const override {return entity_size/2;}

		/** confinement methode */
		bool canBeConfinedIn(Box*);

		/** eatable */
		virtual bool eatable(SimulatedEntity const*) const = 0;
		virtual bool eatableBy(Mouse const*) const = 0;
		virtual bool eatableBy(Cheese const*) const = 0;

		void confineInBox(Box* b);

		virtual Vec2d getHeading() const;

		/** polymorphic destructor */
		virtual ~SimulatedEntity() = default;

		void resetBox() {box->reset();}
		void confine(Box*);

	protected:
		Vec2d pos;
		double entity_size;
		Angle angle;

		Box* box; //!< Current box

		double energy; //!< Current life force or nutritivity
		sf::Time age; //!< age incremented by update()
		sf::Time longevity; //!< Time of certain DEATH

		/** SFML variables */
		sf::Texture* texture;
		sf::Sprite entitySprite;

	private:
		sf::Text text;

};

#endif // SIMULATEDENTITY_HPP
