#include "Mouse.hpp"
#include <Application.hpp>

Mouse::Mouse()
: energy(getAppConfig().mouse_energy_initial),
	texture(getAppConfig().mouse_texture_white),
	mouseSize(getAppConfig().mouse_size),
	entitySprite(buildSprite
	(
		pos,
		mouseSize,
		texture
	)
{}

void Mouse::drawOn(sf::RenderTarget& target)
{
	entitySprite.setRotation(angle/ DEG_TO_RAD);
	target.draw(entitySprite);
}
