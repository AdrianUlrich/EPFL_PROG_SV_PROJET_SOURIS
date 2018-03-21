#include "Box.hpp"
#include <Application.hpp>
#include <Utility/Utility.hpp>

Box::Box (Vec2d position, double largeur, double hauteur, double epaisseur)
:	position (position),
	largeur (largeur),
	hauteur (hauteur),
	epaisseur (epaisseur),
	mur(4),
  texture(&getAppTexture(getAppConfig().simulation_lab_fence))
{
	mur[0].first = Vec2d(position.x,										position.y+epaisseur);
	mur[0].second =Vec2d(position.x+epaisseur,					position.y+hauteur);
	mur[1].first = Vec2d(position.x+epaisseur,					position.y+hauteur-epaisseur);
	mur[1].second =Vec2d(position.x+largeur,						position.y+hauteur);
	mur[2].first = Vec2d(position.x+largeur-epaiseur,		position.y);
	mur[2].second =Vec2d(position.x+largeur,						position.y+hauteur-epaisseur);
	mur[3].first = Vec2d(position.x, 										position.y);
	mur[3].second =Vec2d(position.x+largeur-epaisseur,	position.y+epaisseur);
	for (auto val : mur)
		rectangle.push_back(buildRectangle(val.second, val.first, texture);
}

double Box::getLeftLimit(bool intern)
{
	if (intern)
		return mur[0].first.x;
	else
		return mur[0].second.x;
}

double Box::getRightLimit(bool intern)
{
	if (intern)
		return mur[1].second.x;
	else
		return mur[1].first.x;
}

double Box::getTopLimit(bool intern)
{
	if (intern)
		return mur[2].first.y;
	else
		return mur[2].second.y;
}

double Box::getBottomLimit(bool intern)
{
	if (intern)
		return mur[3].second.y;
	else
		return mur[3].first.y;
}

bool isPositionInside(const Vec2d& position)
{
	return
	(
				(position.x < getRightLimit(true))
		and	(position.x > getLeftLimit(true))
		and	(position.y > getTopLimit(true))
		and	(position.y < getBottomLimit(true))
	);
}

bool isPositionOnWall(const Vec2d& position)
{
	return
	(
			!	(isPointInside(position))
		and	(position.x < getRightLimit())
		and	(position.x > getLeftLimit())
		and	(position.y > getTopLimit())
		and (position.y < getBottomLimit())
	);
}

void Box::drawOn(sf::RenderTarget& target)
{
	target.draw(rectangle);
}
