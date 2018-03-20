#include "SimulatedEntity.hpp"
#include <Random/Random.hpp>
#include <Utility/Utility.hpp>
#include <Application.hpp>

SimulatedEntity::SimulatedEntity(Vec2d pos, double energy)
: box(nullptr),
	angle(uniform(0,TAU)),
	age(sf::Time.Zero)
{}

void SimulatedEntity::drawOn(sf::RenderTarget target)
{
	auto text = buildText
	(
		to_nice_string(energy),
		pos,
		getAppFont(),
		getAppConfig().default_debug_text_size,
		sf::Color::Blue
	);
text.setRotation(angle / DEG_TO_RAD + 90);
target.draw(text);
}
