#include "Cheese.hpp"
#include <Application.hpp>

Cheese::Cheese()
: texture(getAppConfig().cheese_texture),
	energy(getAppConfig().cheese_initial_energy)
	entitySprite(buildSprite
	(
		pos,
		energy,
		texture
	)
{}

void Cheese::drawOn(sf::RenderTarget& target)
{
	entitySprite.setSize(energy);
	entitySprite.setRotation(angle/ DEG_TO_RAD);
	target.draw(entitySprite);
}
