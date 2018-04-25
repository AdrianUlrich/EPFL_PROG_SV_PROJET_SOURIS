#include "Animal.hpp"
#include <Utility/Arc.hpp>
#include <Utility/Vec2d.hpp>
#include <Utility/Utility.hpp>
#include <Random/Random.hpp>
#include <Application.hpp>
#include <Config.hpp>


Intervals Animal::intervals = { -180, -100, -55, -25, -10, 0, 10, 25, 55, 100, 180};
Probs Animal::probs = {0.0000,0.0000,0.0005,0.0010,0.0050,0.9870,0.0050,0.0010,0.0005,0.0000,0.0000};

Animal::Animal(Vec2d const& pos, double energy, sf::Texture* texture, double rayon)
:	SimulatedEntity(pos,energy,texture,rayon),
	etat(IDLE),
	AngleVision(getAppConfig().mouse_view_range),
	DistanceVision(getAppConfig().mouse_view_distance)
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
	auto new_p(pos + getSpeedVector()*(dt.asSeconds()));
	if
	(
		new_p.y - getRadius() <= 	box->getTopLimit(true) // mur du haut de la boîte contenant p
	||new_p.y + getRadius() >= 	box->getBottomLimit(true) // mur du bas de la boîte contenant p
	||new_p.x - getRadius() <= 	box->getLeftLimit(true) // mur de gauche de la boîte contenant p
	||new_p.x + getRadius() >= 	box->getRightLimit(true) // mur de droite de la boîte contenant p
	)
	{
		angle = -getHeading().angle();
		new_p = pos + getSpeedVector()*(dt.asSeconds());
	}
	pos = new_p;
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

bool isTargetInsight(const Vec2d& position)
{
	if ((position.lengthSquared()) <= (DistanceVision*DistanceVision) and 
		((position.x*x + position.y*y) >= cos((AngleVision+0.001)/2))
		{return true};
	if (isEqual(position.lenth, 0) {return true};
	
}


