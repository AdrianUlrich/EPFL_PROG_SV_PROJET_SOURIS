#include "Cheese.hpp"
#include <Application.hpp>
#include <algorithm>

Cheese::Cheese(Vec2d const& pos)
:	SimulatedEntity
	(
		pos,
		getAppConfig().cheese_initial_energy,
		&getAppTexture(getAppConfig().cheese_texture)
	),
	maxSide(std::max(texture->getSize().x, texture->getSize().y))
{
	entitySprite = buildSprite(pos,energy/maxSide,*texture);
	longevity = sf::seconds(1e+9);
}

void Cheese::drawOn(sf::RenderTarget& target)
{
	if (isDebugOn())
		SimulatedEntity::drawOn(target);
	entitySprite.setScale(Vec2d(energy,energy)/maxSide);
	entitySprite.setRotation(angle/ DEG_TO_RAD);
	target.draw(entitySprite);
}

Quantity Cheese::provideEnergy(Quantity qte)
{
	double oldEnergy(energy);
	energy=std::max(0.,energy-qte);
	return oldEnergy-/*new*/energy;
}

bool Cheese::specificDead() const
{
	// Cheese may die from death
	return false;
}
