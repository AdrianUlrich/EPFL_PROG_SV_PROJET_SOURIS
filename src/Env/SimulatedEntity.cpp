#include "SimulatedEntity.hpp"
#include <Random/Random.hpp>
#include <Utility/Utility.hpp>
#include <Application.hpp>
#include <SFML/Graphics.hpp>
#include <string>
using namespace std;

SimulatedEntity::SimulatedEntity(Vec2d const& pos, double energy, sf::Texture& texture)
:	texture(texture),
	pos(pos),
	angle(uniform(0.,TAU)),
	box(nullptr),
	energy(energy),
	age(sf::Time::Zero)
{}

void SimulatedEntity::drawOn(sf::RenderTarget& target)
{
//std::string msg("EntityNRJ:"+to_nice_string(energy));
auto text = buildText("yo",pos,getAppFont(),getAppConfig().default_debug_text_size,sf::Color::Blue);
text.setRotation(angle / DEG_TO_RAD + 90);
target.draw(text);
}

void SimulatedEntity::update(sf::Time dt)
{
  age += dt;
}
