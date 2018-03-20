#include "Mouse.hpp"
#include <Application.hpp>

Mouse::Mouse()
: energy(getAppConfig().mouse_initial_energy)
	texture(getAppConfig().mouse_texture_white)
{}

void Mouse::drawOn(sf::RenderTarget target)
{
	sf::Sprite const entitySprite = buildSprite
	(
		pos,
		getAppConfig().mouse_size,
		texture
	);
	entitySprite.setRotation(angle/ DEG_TO_RAD);
	target.draw(entitySprite);
}
