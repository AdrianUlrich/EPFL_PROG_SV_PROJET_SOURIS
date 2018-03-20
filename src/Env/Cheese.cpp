#include "Cheese.hpp"
#include <Application.hpp>

Cheese::Cheese()
: energy(getAppConfig().cheese_initial_energy)
	texture(getAppConfig().cheese_texture)
{}

void Cheese::drawOn(sf::RenderTarget target)
{
	sf::Sprite const entitySprite = buildSprite
	(
		pos,
		energy,
		texture
	);
	entitySprite.setRotation(angle/ DEG_TO_RAD);
	target.draw(entitySprite);
}
