#include "Mouse.hpp"
#include <Application.hpp>

Mouse::Mouse(Vec2d const& pos)
:	Animal
	(
		pos,
		getAppConfig().mouse_energy_initial,
		&getAppTexture(getAppConfig().mouse_texture_white),
		getAppConfig().mouse_size
	)
	//,mouseSize(getAppConfig().mouse_size)
{
	entitySprite = buildSprite(pos,entity_size,*texture);
	longevity = getAppConfig().mouse_longevity;
	//maxSpeed = getAppConfig().mouse_max_speed;
}

void Mouse::drawOn(sf::RenderTarget& target)
{
	entitySprite.setPosition(pos);
	entitySprite.setRotation(angle/ DEG_TO_RAD);
	SimulatedEntity::drawOn(target);
	if (isDebugOn())
	{
		Animal::drawOn(target);
	}
}

bool Mouse::isDead() const
{
	return
	(
		SimulatedEntity::isDead()
	or	false //! Mouse can die of other conditions like CANCER
	);
}

bool Mouse::eatable(SimulatedEntity const* entity)  const
{return entity->eatableBy(this);}

bool Mouse::eatableBy(Cheese const*) const
{return false;}

bool Mouse::eatableBy(Mouse const*) const
{return false;}

double Mouse::getMaxSpeed() const
{return getAppConfig().mouse_max_speed;}

