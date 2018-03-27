/*
 * prjsv 2018
 * 2016
 * Marco Antognini
 * fev 2018
 * Antoine Madrona
 */

#include <Application.hpp>
#include <Env/Collider.hpp>


#include <catch.hpp>

#include <iostream>


class DummyCollider: public Collider
{
	
  public:
	DummyCollider(const Vec2d& pos, double rad)
		:  center(pos), radius(rad)
	{}
	
	Vec2d getCenter()  const override
	{
		return center;
	}
	
	double getRadius() const
	{
		return radius;
	}
	
  private:
	Vec2d center;
	double radius;
};

SCENARIO("Collision", "[Collider]")
{
    GIVEN("Two identical Colliders")
    {
        DummyCollider o1({ 1, 1 }, 2);
        DummyCollider o2({ 1, 1 }, 2);

        THEN("they collide")
        {
            CHECK(o1.isColliding(o2));
            CHECK(o2.isColliding(o1));
            CHECK((o1 | o2));
            CHECK((o2 | o1));
        }

        THEN("they have the same bounding circle")
        {
            CHECK(o1.getCenter() == o2.getCenter());
			CHECK(o1.getRadius() == o2.getRadius());
        }
    }

    GIVEN("A collider inside the other, with different centers and radius")
    {
        DummyCollider o1({ 0, 0 }, 4);
        DummyCollider o2({ 1, 1 }, 3);

        THEN("the two colliders collide")
        {
            CHECK(o1.isColliding(o2));
            CHECK(o2.isColliding(o1));
            CHECK((o1 | o2));
            CHECK((o2 | o1));
        }
		
        THEN("their bounding circles are not the same")
        {
            CHECK_FALSE(o1.getRadius() == o2.getRadius());
			CHECK_FALSE(o1.getCenter() == o2.getCenter());
        }
    }

    GIVEN("Colliders that overlap but are not inside of each other")
    {
        DummyCollider o1 ({ 0, 0 }, 4);
        DummyCollider o2 ({ 1, 1 }, 3);
		DummyCollider o3 ({ 5, 5 }, 4);

        THEN("they collide")
        {
            CHECK(o1.isColliding(o3));
			CHECK(o3.isColliding(o1));
            CHECK(o2.isColliding(o3));
			CHECK(o3.isColliding(o2));
            CHECK((o1 | o3));
            CHECK((o3 | o1));
			CHECK((o2 | o3));
			CHECK((o3 | o2));
        }
	}
	

	GIVEN("Colliders that don't overlap ")
		{
        DummyCollider o1({ 0, 0 }, 4);
        DummyCollider o2({ 1, 1 }, 3);
		DummyCollider o3({ 5, 5 }, 4);
		DummyCollider o4({-9,-9 }, 4);

        THEN("they don't collide")
        {
            CHECK_FALSE(o1.isColliding(o4));
			CHECK_FALSE(o4.isColliding(o1));
            CHECK_FALSE(o2.isColliding(o4));
			CHECK_FALSE(o4.isColliding(o2));
			CHECK_FALSE(o3.isColliding(o4));
			CHECK_FALSE(o4.isColliding(o3));
            CHECK_FALSE((o1 | o4));
            CHECK_FALSE((o4 | o1));
			CHECK_FALSE((o2 | o4));
			CHECK_FALSE((o4 | o2));
			CHECK_FALSE((o3 | o4));
			CHECK_FALSE((o4 | o3));
        }
		}
	
    GIVEN("A Collider and two points, one inside and one outside")
    {
        DummyCollider o ({ 0, 0 }, 5);
        auto p1 = Vec2d(0, 0);
        auto p2 = Vec2d(6, 0);

        THEN("only one point is inside")
        {
			CHECK(o.isPointInside(p1));
            CHECK(o > p1);
			CHECK_FALSE(o.isPointInside(p2));
            CHECK_FALSE(o > p2);
        }
    }

	
}
