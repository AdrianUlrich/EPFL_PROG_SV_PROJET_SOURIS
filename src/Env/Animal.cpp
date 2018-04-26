#include "Animal.hpp"

#include <Utility/Arc.hpp>
#include <Utility/Vec2d.hpp>
#include <Utility/Utility.hpp>
#include <Random/Random.hpp>
#include <Application.hpp>
#include <Config.hpp>
#include <cmath>


Intervals Animal::intervals = { -180, -100, -55, -25, -10, 0, 10, 25, 55, 100, 180};
Probs Animal::probs = {0.0000,0.0000,0.0005,0.0010,0.0050,0.9870,0.0050,0.0010,0.0005,0.0000,0.0000};

Animal::Animal(Vec2d const& pos, double energy, sf::Texture* texture, double rayon)
:	SimulatedEntity(pos,energy,texture,rayon),
	etat(IDLE),
	AngleVision(getAppConfig().mouse_view_range),
	DistanceVision(getAppConfig().mouse_view_distance),
	velocite(0.),
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
	updateState();

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
		while (angle>TAU)
			angle -= TAU;
		while (angle<-TAU)
			angle += TAU;
	}
	auto new_p(pos + Vec2d(1,1));//getSpeedVector()*(dt.asSeconds()));
	if (box!=nullptr) {
		if (new_p.y - getRadius() <= 	box->getTopLimit(true) // mur du haut de la boîte contenant p
			||new_p.y + getRadius() >= 	box->getBottomLimit(true)) // mur du bas de la boîte contenant p
		{
			angle = -angle;
			new_p = pos + getSpeedVector()*(dt.asSeconds());
		}
		if (new_p.x - getRadius() <= 	box->getLeftLimit(true) // mur de gauche de la boîte contenant p
			||new_p.x + getRadius() >= 	box->getRightLimit(true)) // mur de droite de la boîte contenant p
		{
			angle = PI-angle;
			new_p = pos + getSpeedVector()*(dt.asSeconds());
		}
	}
	pos += new_p;
}

void Animal::drawOn(sf::RenderTarget& targetWindow)
{
	sf::Color color = sf::Color::Black;
	color.a = 16; // light, transparent grey
	Arc arcgraphics(45, 135, DistanceVision, color, DistanceVision);
	arcgraphics.setOrigin(DistanceVision, DistanceVision);
	arcgraphics.setPosition(pos);
	arcgraphics.rotate(angle/DEG_TO_RAD-90);
	targetWindow.draw(arcgraphics);
}  

bool Animal::isTargetInsight(const Vec2d& position)
{
	return 
	(
		(position.lengthSquared() <= DistanceVision*DistanceVision) and 
		(position.x*pos.x + position.y*pos.y >= cos((AngleVision+0.001)/2))
		or (isEqual(position.length(), 0))
	);
}


