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
	mur[0].first = Vec2d(position.x-(largeur/2)+epaisseur, position.y+(hauteur/2));
	mur[0].second =Vec2d(position.x-(largeur/2), position.y-(hauteur/2)+epaisseur);
	mur[1].first = Vec2d(position.x+(largeur/2), position.y+(hauteur/2));
	mur[1].second =Vec2d(position.x-(largeur/2)+epaisseur, position.y+(hauteur/2)+epaisseur);
	mur[2].first = Vec2d(position.x+(largeur/2), position.y+(hauteur/2)-epaisseur);
	mur[2].second =Vec2d(position.x+(largeur/2)-epaisseur, position.y-(hauteur/2));
	mur[3].first = Vec2d(position.x+(largeur/2)-epaisseur, position.y-(hauteur/2)+epaisseur);
	mur[3].second =Vec2d(position.x-(largeur/2), position.y-(hauteur/2));
	for (auto val : mur)
		rectangle.push_back(buildRectangle(val.second, val.first, texture));
}

double Box::getLeftLimit(bool intern)
{
	if (intern)
		return mur[0].second.x;
	else
		return mur[0].first.x;
}

double Box::getRightLimit(bool intern)
{
	if (intern)
		return mur[1].first.x;
	else
		return mur[1].second.x;
}

double Box::getTopLimit(bool intern)
{
	if (intern)
		return mur[2].second.y;
	else
		return mur[2].first.y;
}

double Box::getBottomLimit(bool intern)
{
	if (intern)
		return mur[3].first.y;
	else
		return mur[3].second.y;
}

bool Box::isPositionInside(const Vec2d& position)
{
	return
	(
				(position.x < getRightLimit(true))
		and	(position.x > getLeftLimit(true))
		and	(position.y > getTopLimit(true))
		and	(position.y < getBottomLimit(true))
	);
}

bool Box::isPositionOnWall(const Vec2d& position)
{
	return
	(
			!	(isPositionInside(position))
		and	(position.x < getRightLimit())
		and	(position.x > getLeftLimit())
		and	(position.y > getTopLimit())
		and (position.y < getBottomLimit())
	);
}

void Box::drawOn(sf::RenderTarget& target)
{
	for (auto val : rectangle)
	{
	target.draw(val);
	}
}

