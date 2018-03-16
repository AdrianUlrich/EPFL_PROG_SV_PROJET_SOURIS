#include "Collider.hpp"

Collider::Collider(Vec2d position, double rayon)
: position(position), rayon(rayon)
{}

bool Collider::isColliding(Collider const& other) const
{	
	return(((other.position-position).lengthSquared()) <=((other.rayon+rayon)*(other.rayon+rayon)));
}
bool operator |(Collider const& body1, Collider const& body2)
{
	return body1.isColliding(body2);
}

bool Collider::isPointInside(Vec2d const& other) const
{
return(((other-position).lengthSquared()) <=(rayon*rayon));
}
bool operator >(Collider const& body, Vec2d const& point)
{
	return body.isPointInside(point);
}

Vec2d Collider::getCenter() const
{return position;}

double Collider::getRadius() const
{return rayon;}
