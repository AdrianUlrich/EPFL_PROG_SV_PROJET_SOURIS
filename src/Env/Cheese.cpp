#include "Cheese.hpp"
#include <Application.hpp>
#include <algorithm>

Cheese::Cheese(Vec2d const& pos)
:	SimulatedEntity
	(
		pos,
		getAppConfig().cheese_initial_energy,
		&getAppTexture(getAppConfig().cheese_texture),
		getAppConfig().cheese_initial_energy
	)
	//,maxSide(std::max(texture->getSize().x, texture->getSize().y))
{
	entitySprite = buildSprite(pos,energy/*/std::max(entity_size,1.)*/,*texture);
	longevity = sf::seconds(1e+9);
}

void Cheese::drawOn(sf::RenderTarget& target)
{
	entitySprite.setRotation(angle / DEG_TO_RAD);
	SimulatedEntity::drawOn(target);
}

Quantity Cheese::provideEnergy(Quantity qte)
{
	if (energy<=0) return 0;
	double oldEnergy(energy);
	energy=std::max(0.,energy-qte);
	entitySprite.setScale(Vec2d(1,1)*(energy/oldEnergy));
	entity_size=energy;
	return oldEnergy-/*new*/energy;
}

bool Cheese::specificDead() const
{
	// Cheese may die from death
	return false;
}


bool Cheese::eatable(SimulatedEntity const* entity)
{
return entity->eatableBy(this);
}

bool Cheese::eatableBy(Cheese const*)
{return false;}

bool Cheese::eatableBy(Mouse const*)
{return true;}
