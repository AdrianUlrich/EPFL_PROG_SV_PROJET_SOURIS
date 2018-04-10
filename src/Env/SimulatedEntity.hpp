#ifndef SIMULATEDENTITY_HPP
#define SIMULATEDENTITY_HPP

#include <SFML/Graphics.hpp>
#include <Utility/Utility.hpp>
#include "Box.hpp"
#include "Collider.hpp"
#include <Utility/Vec2d.hpp>

class SimulatedEntity : public Collider /// ABSTRACT
{
	public:
		/** constructor */
		SimulatedEntity(Vec2d const& pos, double energy, sf::Texture* texture, double rayon);

		/** SFML draw function */
		virtual void drawOn(sf::RenderTarget&);

		/** aging function*/
		void update(sf::Time dt);
		
		bool isDead() const;
		/** pure virtual method => abstract class */
		virtual bool specificDead() const = 0;
		
		/** overriding virtual collider getters */
		Vec2d getCenter() const override {return pos;}
		double getRadius() const override {return entity_size/2;}
		
		/** polymorphic destructor */
		virtual ~SimulatedEntity() = default;
		
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
