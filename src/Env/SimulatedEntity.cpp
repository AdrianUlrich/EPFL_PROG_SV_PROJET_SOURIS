#include "SimulatedEntity.hpp"
#include "Mouse.hpp"
#include "Cheese.hpp"
#include <Random/Random.hpp>
#include <Utility/Utility.hpp>
#include <Application.hpp>
#include <SFML/Graphics.hpp>
#include <string>
using namespace std;

SimulatedEntity::SimulatedEntity(Vec2d const& pos, double energy, sf::Texture* texture, double rayon)
:	pos(pos),
	entity_size(rayon),
	angle(uniform(0.,TAU)),
	box(nullptr),
	energy(energy),
	age(sf::Time::Zero),
	texture(texture),
	text(buildText
	(
		"EntityNRJ:"+to_nice_string(energy),
		pos,
		getAppFont(),
		getAppConfig().default_debug_text_size,
		getAppConfig().debug_text_color
	))
{}

void SimulatedEntity::drawOn(sf::RenderTarget& target)
{
	if (isDebugOn())
	{
		auto circle(buildCircle(getCenter(), getRadius(), sf::Color(20,150,20,30)));
		target.draw(circle);
	}
	target.draw(entitySprite);
	if (isDebugOn())
	{
		text.setString("EntityNRJ:"+to_nice_string(energy));
		//text.setRotation(angle / DEG_TO_RAD + 90);
		target.draw(text);
	}
}

Vec2d SimulatedEntity::getHeading() const
{
	return Vec2d::fromAngle(angle);
}

void SimulatedEntity::update(sf::Time dt)
{
	age += dt;
}

bool SimulatedEntity::isDead() const
{
	return
	(
		age > longevity or
		energy <= 0 or
		specificDead()
	);
}

bool SimulatedEntity::canBeConfinedIn(Box* box)
{
	return box.isPositionInside(pos);
}

void SimulatedEntity::confine()
{
	if (box==nullptr) return;

	auto topWall(box->getTopLimit(true));
	  if (getPosition().y - getRadius() < topWall)
		  position.y = topWall + radius * 1.25);

	auto bottomWall(box->getBottomLimit(true));
	  if (getPosition().y + getRadius() > bottomWall)
		  position.y = bottomWall - radius * 1.25);

	auto rightWall(box->getRightLimit(true));
	  if (getPosition().x + getRadius() > rightWall)
		  position.x = rightWall - radius * 1.25);

	auto leftWall(box->getLeftLimit(true));
	  if (getPosition().x - getRadius() < leftWall)
		  position.x = leftWall + radius * 1.25);
}


