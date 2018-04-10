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
}

void Mouse::drawOn(sf::RenderTarget& target)
{
	entitySprite.setPosition(pos);
	entitySprite.setRotation(angle/ DEG_TO_RAD);
	SimulatedEntity::drawOn(target);
}

bool Mouse::specificDead() const
{
	// Later mouse will be able to die from cancer :/
	return false;	
}

