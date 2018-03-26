#include "Cheese.hpp"
#include <Application.hpp>
#include <algorithm>

Cheese::Cheese(Vec2d const& pos)
:	SimulatedEntity
	(
		pos,
		getAppConfig().cheese_initial_energy,
		getAppTexture(getAppConfig().cheese_texture)
	),
	maxSide(std::max(texture.getSize().x, texture.getSize().y))
{
	SimulatedEntity::entitySprite =
	(
		buildSprite
		(
			pos,
			energy,
			texture
		)
	);
}

void Cheese::drawOn(sf::RenderTarget& target)
{
	//SimulatedEntity::drawOn(target);
	entitySprite.setScale(Vec2d(energy,energy)/maxSide);
	entitySprite.setRotation(angle/ DEG_TO_RAD);
	target.draw(entitySprite);
}
