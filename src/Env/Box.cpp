#include "Box.hpp"
#include <Application.hpp>
#include <Utility/Utility.hpp>
#include <array>

Box::Box (Vec2d position, double largeur, double hauteur, double epaisseur)
:	pos (position),
	l(largeur),
	h(hauteur),
	e(epaisseur),
	texture(&getAppTexture(getAppConfig().simulation_lab_fence)),
	empty(true)
{
	/*! initialisation murs */
	double x(pos.x-l/2),y(pos.y-h/2);
	murs[0].first =Vec2d(x,y)+Vec2d(e,h);
	murs[0].second=Vec2d(x,y)+Vec2d(0,e);
	murs[1].first =Vec2d(x,y)+Vec2d(l,h);
	murs[1].second=Vec2d(x,y)+Vec2d(e,h-e);
	murs[2].first =Vec2d(x,y)+Vec2d(l,h-e);
	murs[2].second=Vec2d(x,y)+Vec2d(l-e,0);
	murs[3].first =Vec2d(x,y)+Vec2d(l-e,e);
	murs[3].second=Vec2d(x,y)+Vec2d(0,0);
	/*! initialisation rectangles */
	for (int i(0); i<4; ++i)
		builtRecs[i] = buildRectangle(murs[i].second,murs[i].first,texture);
}

double Box::getLeftLimit(bool intern)
{
	return ((intern) ? murs[0].first.x : murs[0].second.x);
}

double Box::getRightLimit(bool intern)
{
	return ((intern) ? murs[2].second.x : murs[2].first.x);
}

double Box::getTopLimit(bool intern)
{
	return ((intern) ? murs[3].first.y : murs[3].second.y);
}

double Box::getBottomLimit(bool intern)
{
	return ((intern) ? murs[1].second.y : murs[1].first.y);
}

bool Box::isPositionInside(const Vec2d& pos)
{
	return
	(
		(pos.x < getRightLimit(true))
		and	(pos.x > getLeftLimit(true))
		and	(pos.y > getTopLimit(true))
		and	(pos.y < getBottomLimit(true))
	);
}

bool Box::isPositionOnWall(const Vec2d& pos)
{
	return
	(
		not	(isPositionInside(pos))
		and	(pos.x < getRightLimit())
		and	(pos.x > getLeftLimit())
		and	(pos.y > getTopLimit())
		and (pos.y < getBottomLimit())
	);
}

void Box::drawOn(sf::RenderTarget& target)
{
	for (auto wal : builtRecs)
	{
		target.draw(wal);
	}
}
