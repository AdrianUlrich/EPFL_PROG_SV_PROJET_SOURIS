#ifndef I_COLLIDER_HPP
#define I_COLLIDER_HPP

#include <Utility/Vec2d.hpp>


class Collider /// ABSTRACT
{
public:
	//Collider(Vec2d const& position, double rayon);

	/** pure virtual getters */
	virtual Vec2d getCenter() const = 0;
	virtual double getRadius() const = 0;

	/** utility collider methods */
	bool isColliding(Collider const& other) const;
	bool isPointInside(Vec2d const&) const;

private:
	//Vec2d position;
	//double rayon;
};

bool operator |(Collider const& body1, Collider const& body2);
bool operator >(Collider const& body, Vec2d const& point);


#endif //I_COLLIDER_HPP
