#include "Animal.hpp"
#include <Random/Random.hpp>

Animal::Animal(Vec2d const& pos, double energy, sf::Texture* texture, double rayon)
:	SimulatedEntity(pos,energy,texture,rayon),
	etat(IDLE),
	intervals{ -180, -100, -55, -25, -10, 0, 10, 25, 55, 100, 180},
	probs{0.0000,0.0000,0.0005,0.0010,0.0050,0.9870,0.0050,0.0010,0.0005,0.0000,0.0000}
{}

void Animal::update(sf::Time dt)
{
	SimulatedEntity::update(dt);
	//if (energy<wdouch && isFoodNear())
	//	etat = FOOD_IN_SIGHT;
	if (etat == WANDERING)
		move(dt); //
}

void Animal::updateState()
{
	if (etat!=WANDERING)
		etat=WANDERING;
}

void Animal::move(sf::Time dt)
{
	auto new_p(pos + getSpeedVector()*dt);
	if
	(
		new_p.y - getRadius() <= 	box->getTopLimit(true) // mur du haut de la boîte contenant p
	||new_p.y + getRadius() >= 	box->getBottomLimit(true) // mur du bas de la boîte contenant p
	||new_p.x - getRadius() <= 	box->getLeftLimit(true) // mur de gauche de la boîte contenant p
	||new_p.x + getRadius() >= 	box->getRightLimit(true) // mur de droite de la boîte contenant p
	)
	{
		angle = -getHeading().angle();
		new_p = pos + getSpeedVector()*dt;
	}
	pos = new_p;
}
