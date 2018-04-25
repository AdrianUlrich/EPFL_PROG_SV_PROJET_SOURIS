#include "Animal.hpp"
#include <Random/Random.hpp>

Intervals Animal::intervals = { -180, -100, -55, -25, -10, 0, 10, 25, 55, 100, 180};
Probs Animal::probs = {0.0000,0.0000,0.0005,0.0010,0.0050,0.9870,0.0050,0.0010,0.0005,0.0000,0.0000};

Animal::Animal(Vec2d const& pos, double energy, sf::Texture* texture, double rayon)
:	SimulatedEntity(pos,energy,texture,rayon),
	etat(IDLE),
	compteur(sf::Time::Zero)
{}

void Animal::update(sf::Time dt)
{
	SimulatedEntity::update(dt);
	compteur += dt;
	switch (etat)
	{
	case WANDERING:
		move(dt);
		break;

	default:
		break;
	}
	updateState()

}

void Animal::updateState()
{
	if (etat!=WANDERING)
	{
		etat=WANDERING;
		velocite=getMaxSpeed();
	}
	//if (energy<minimum_de_faim && isFoodNear())
	//	etat = FOOD_IN_SIGHT;
}

void Animal::move(sf::Time dt)
{
	if (compteur>getAppConfig().time_between_rotations)
	{
		compteur = sf::Time::Zero;
		angle += getNewRotation();
		if (angle*angle>TAU*TAU)
			angle = angle % TAU;
	}
	auto new_p(pos + getSpeedVector()*(dt.asSeconds()));
	if (new_p.y - getRadius() <= 	box->getTopLimit(true) // mur du haut de la boîte contenant p
		||new_p.y + getRadius() >= 	box->getBottomLimit(true)) // mur du bas de la boîte contenant p
	{
		angle=-angle;
		new_p = pos + getSpeedVector()*(dt.asSeconds());
	}
	if (new_p.x - getRadius() <= 	box->getLeftLimit(true) // mur de gauche de la boîte contenant p
		||new_p.x + getRadius() >= 	box->getRightLimit(true)) // mur de droite de la boîte contenant p
	{
		angle = PI-angle;
		new_p = pos + getSpeedVector()*(dt.asSeconds());
	}
	pos = new_p;
}
