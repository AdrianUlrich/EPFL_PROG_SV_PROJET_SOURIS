#include "Animal.hpp"
#include "Organ.hpp"

#include <Utility/Arc.hpp>
#include <Utility/Vec2d.hpp>
#include <Utility/Utility.hpp>
#include <Random/Random.hpp>
#include <Application.hpp>
#include <Config.hpp>
#include <cmath>
#include <algorithm>
//#include <vector>
//#include <iostream>


Intervals Animal::intervals = { -180, -100, -55, -25, -10, 0, 10, 25, 55, 100, 180};
Probs Animal::probs = {0.0000,0.0000,0.0005,0.0010,0.0050,0.9870,0.0050,0.0010,0.0005,0.0000,0.0000};

Animal::Animal(Vec2d const& pos, double energy, sf::Texture* texture, double rayon)
:	SimulatedEntity(pos,energy,texture,rayon)
,	etat(IDLE)
,	AngleVision(getAppConfig().mouse_view_range)
,	DistanceVision(getAppConfig().mouse_view_distance)
,	velocite(0.)
,	compteur(sf::Time::Zero)
,	cible_actuelle(nullptr)
,	foie(new Organ(true))
{}

void Animal::updateCurrentSubstance(SubstanceId const& id)
{foie->setSubstance(id);}

void Animal::printSubstanceAt(SubstanceId id, Vec2d const& pos) const
{foie->printSubstanceAt(id,pos);}

Animal::~Animal()
{
	if (box!=nullptr) box->reset();
	delete foie;
}

bool Animal::canBeConfinedIn(Box* b) const
{return SimulatedEntity::canBeConfinedIn(b)&&b->isEmpty();}
void Animal::setRotation(Angle a)
{angle=a;}
void Animal::setOrgan(Organ*o)
{if(o!=nullptr){delete foie;foie=o;}}

void Animal::update(sf::Time dt)
{
	SimulatedEntity::update(dt);
	compteur += dt;
	updateState();
	switch (etat)
	{
	case WANDERING:
		move(dt);
		break;

	case FOOD_IN_SIGHT:
		move(getFoodPull(),dt);
		break;

	case FEEDING:
		feed();
		break;

	default:
		break;
	}
	energy -= getAppConfig().animal_base_energy_consumption + getLossFactor()*velocite;
}

void Animal::updateState()
{
	if (etat==IDLE or (isSatiated() and etat!=WANDERING))
	{
		etat = WANDERING;
		velocite = getMaxSpeed();
		cible_actuelle = nullptr;
	}
	else
	{
		if (etat == FOOD_IN_SIGHT /*and cible_actuelle!=nullptr*/ and isPointInside(cible_actuelle->getCenter())) // when etat==FOOD_IN_SIGHT , cible_actuelle must be defined
		{
			etat = FEEDING;
			angle=(cible_actuelle->getCenter()-getCenter()).angle();
			velocite=0.;
		}
		else if (etat!=FEEDING)
		{
			/// finding all targets in sight
			auto food_near(getAppEnv().findTargetsInSightOf(this)); // Type is vector<sim*>*
			if ((food_near->size())>1)
			{
				//std::cerr<<food_near->size()<<std::flush;
				/// finding the nearest target
				double mindist2(-1.);
				for (auto val : *food_near) // Type is sim*
				{
					if (val!=this and eatable(val))
					{
						double thisdist2((pos-(val->getCenter())).lengthSquared());
						if (thisdist2 < mindist2 or mindist2<0)
						{
							mindist2=thisdist2;
							cible_actuelle = val;
							etat=FOOD_IN_SIGHT;
						}
					}
				}
			}
			delete food_near;
		}
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
		{angle = -angle;}
		if (new_p.x - getRadius() <= 	box->getLeftLimit(true) // mur de gauche de la boîte contenant p
			||new_p.x + getRadius() >= 	box->getRightLimit(true)) // mur de droite de la boîte contenant p
		{angle = PI-angle;}
	}
pos += getSpeedVector()*(dt.asSeconds());
}

void Animal::move(Vec2d const& force,sf::Time t)
{
	double dt(t.asSeconds());
	Vec2d accel(force/getMass());
	Vec2d new_vel(getSpeedVector()+accel*dt);
	Vec2d new_dir(new_vel.normalised());
	angle = new_dir.angle();
	velocite = std::min(new_vel.length(),getMaxSpeed());
	auto new_p(pos+getHeading()*velocite*dt);
	if (box!=nullptr) {
		if (new_p.y - getRadius() <= 	box->getTopLimit(true) // mur du haut de la boîte contenant p
			||new_p.y + getRadius() >= 	box->getBottomLimit(true)) // mur du bas de la boîte contenant p
		{
			angle = -angle;
		}
		if (new_p.x - getRadius() <= 	box->getLeftLimit(true) // mur de gauche de la boîte contenant p
			||new_p.x + getRadius() >= 	box->getRightLimit(true)) // mur de droite de la boîte contenant p
		{
			angle = PI-angle;
		}
	}
	pos += getSpeedVector()*dt;
}

bool Animal::isSatiated() const
{
	return (
	(etat!=FEEDING and
	energy>getAppConfig().animal_satiety_min) or
	(etat==FEEDING and
	energy>getAppConfig().animal_satiety_max));
}

Vec2d Animal::getFoodPull() const
{
	Vec2d distV(cible_actuelle->getCenter()-getCenter());
	double dist(distV.length());
	double speed(std::min(getMaxSpeed(),dist*0.3));
	Vec2d Vtarget(distV/dist * speed);
	return (Vtarget-getSpeedVector());
}

void Animal::feed()
{
	energy+=cible_actuelle->provideEnergy(getBite());
}

void Animal::isDead(SimulatedEntity* NTT)
{
	if (cible_actuelle==NTT)
	{
		cible_actuelle=nullptr;
		etat=IDLE;
	}
	//std::cout<<"#PrayFor"<<static_cast<void*>(NTT)<<" who died due to police brutality :'("<<std::endl;
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

void Animal::setTarget(SimulatedEntity* a)
{cible_actuelle=a;}

double Animal::getViewRange() const
{return AngleVision;}

double Animal::getViewDistance() const
{return DistanceVision;}

Angle Animal::getNewRotation() const
{return DEG_TO_RAD * piecewise_linear(intervals,probs);}

Vec2d Animal::getSpeedVector() const
{return getHeading()*velocite;}

void Animal::fillBox()
{box->addOccupant();}

void Animal::drawCurrentOrgan(sf::RenderTarget& target)
{foie->Organ::drawOn(target);}

void Animal::updateOrgan()
{foie->update();}

void Animal::setCancerAt(Vec2d const& pos)
{foie->setCancerAt(pos);}
