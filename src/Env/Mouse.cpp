#include "Mouse.hpp"
#include <Application.hpp>

Mouse::Mouse(Vec2d const& pos)
:	Animal
	(
		pos,
		getAppConfig().mouse_energy_initial,
		getAppTexture(getAppConfig().mouse_texture_white)
	),
	mouseSize(getAppConfig().mouse_size)
{
	entitySprite = 
	buildSprite
	(
		pos,
		mouseSize,
		texture
	);
}

void Mouse::drawOn(sf::RenderTarget& target)
{
	//SimulatedEntity::drawOn(target);
	entitySprite.setRotation(angle/ DEG_TO_RAD);
	target.draw(entitySprite);
}
