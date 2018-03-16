#ifndef I_COLLIDER_HPP
#define I_COLLIDER_HPP

#include <Utility/Vec2d.hpp>


class Collider
{
public:
	Collider(Vec2d position, double rayon);
	
	Vec2d getCenter() const;
	double getRadius() const;

	bool isColliding(Collider const& other) const;
	bool isPointInside(Vec2d const&) const;

private:
	Vec2d position;
	double rayon;
};

bool operator |(Collider const& body1, Collider const& body2);
bool operator >(Collider const& body, Vec2d const& point);


#endif //I_COLLIDER_HPP
