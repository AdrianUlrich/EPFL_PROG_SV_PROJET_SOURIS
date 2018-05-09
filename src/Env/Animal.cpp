#include "Animal.hpp"

#include <Utility/Arc.hpp>
#include <Utility/Vec2d.hpp>
#include <Utility/Utility.hpp>
#include <Random/Random.hpp>
#include <Application.hpp>
#include <Config.hpp>
#include <cmath>
#include <algorithm>


Intervals Animal::intervals = { -180, -100, -55, -25, -10, 0, 10, 25, 55, 100, 180};
Probs Animal::probs = {0.0000,0.0000,0.0005,0.0010,0.0050,0.9870,0.0050,0.0010,0.0005,0.0000,0.0000};

Animal::Animal(Vec2d const& pos, double energy, sf::Texture* texture, double rayon)
:	SimulatedEntity(pos,energy,texture,rayon),
	etat(IDLE),
	AngleVision(getAppConfig().mouse_view_range),
	DistanceVision(getAppConfig().mouse_view_distance),
	velocite(0.),
	compteur(sf::Time::Zero),
	cible_actuelle(nullptr)
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
		
	case FOOD_IN_SIGHT:
		move(getFoodLust(),dt);
		break;
		
	case FEEDING:
		//eat(cible_actuelle);
		break;

	default:
		break;
	}
	updateState();
	energy -= getAppConfig().animal_base_energy_consumption + getLossFactor()*velocite;
}

void Animal::updateState()	
{
	SimulatedEntity* food_near(nullptr);
	if (isSatiated())
	{
		etat = WANDERING;
		velocite = getMaxSpeed();
	}
	else if (etat == FOOD_IN_SIGHT and isColliding(*cible_actuelle))
	{
		etat = FEEDING;
	}
	else if	((food_near=getAppEnv().findTargetInSightOf(this))!=nullptr)
	{
		etat = FOOD_IN_SIGHT;
		cible_actuelle = food_near;
	}
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
    auto new_p(pos + getSpeedVector()*(dt.asSeconds()));
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
	pos = new_p;
}

void Animal::move(Vec2d const& force,sf::Time t)
{
	double dt(t.asSeconds());
	auto accel(force/getMass());
	auto new_vel(getSpeedVector()+accel*dt);
	auto new_dir(new_vel.normalised());
	angle = new_dir.angle();
	velocite = std::max(new_vel.length(),getMaxSpeed());
	pos+=getHeading()*velocite*dt;
}

bool Animal::isSatiated() const
{
	return (
	(etat!=FEEDING and
	energy<getAppConfig().animal_satiety_min) or
	(etat==FEEDING and
	energy<getAppConfig().animal_satiety_max));
}

Vec2d Animal::getFoodLust() const
{
	auto distV(getCenter()-cible_actuelle->getCenter());
	auto dist(distV.length());
	auto speed(std::min(getMaxSpeed(),dist*0.3));
	auto Vtarget(distV/dist * speed);
	return Vtarget-getSpeedVector();
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
	if (cible_actuelle!=nullptr)
		text.setString(text.getString()+"\nTARGETLOCK");
}  

bool Animal::isTargetInSight(const Vec2d& position)
{
	auto dist(position-pos);
	auto normdist(dist.normalised());
	return 
	(
		box->isPositionInside(position) and
		dist.lengthSquared() <= DistanceVision*DistanceVision and 
		(
			normdist.dot(getHeading()) >= cos((AngleVision+0.001)/2) or
			isEqual(dist.length(), 0.0)
		)
	);
}


