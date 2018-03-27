/*
* prjsv 2018
* 2016
* Marco Antognini
* fev 2018
* Antoine Madrona
*/

#include <Application.hpp>
#include <Env/Box.hpp>
#include <Env/Cheese.hpp>
#include <Env/Mouse.hpp>
#include <Config.hpp>
#include <catch.hpp>
#include <Utility/Constants.hpp>

#include <iostream>

class DummyMouse : public Mouse
{
public:
    DummyMouse(Vec2d const& position,
                Vec2d const& heading)
    : Mouse(position)
    {
        setHeading(heading);
    }

    // Break encapsulation for this test
    void setHeading(Vec2d const& heading) {
        setRotation(heading.angle());
    }

    double getViewRange() const override {
        return TAU/3;
    }
};

// Utility function
// angle in radian, considered radius is abs(radius)
Vec2d Polar2Cartesian(double angle, double radius)
{
    return std::abs(radius) * Vec2d(std::cos(angle), std::sin(angle));
}


SCENARIO("Testing the isTargetInSight method", "[Mouse]")
{

	const Vec2d initialOrientation(1, 0);
	const Vec2d diagonalHeading (1/1.4142,-1/1.4142);
	const Vec2d initialPosition(450,150);

  Box box1({150,150});
  Box box2(initialPosition);

  DummyMouse mickey({195,105}, initialOrientation);
  DummyMouse winnie(initialPosition, initialOrientation);

  mickey.confine(&box1);
  winnie.confine(&box2);

	Vec2d target(1000,1000);

	double const viewDistance(getAppConfig().mouse_view_distance); // distance de vue
	double const viewRange(TAU/3); // angle de vision ATTENTION DIFFERENT DE JSON

  GIVEN("A mouse in an empty box")
  {
    THEN("Other entities are not seen")
    {
      CHECK_FALSE(winnie.isTargetInSight(target));
    }
  }

  GIVEN("The target at the same position as the mouse")
  {
    target = {450,150};
    THEN("The target is seen by the mouse")
    {
      CHECK(winnie.isTargetInSight(target));
    }
  }

  GIVEN("The target is not the mouse field of view (same box, other corner)")
  {
    target = {11, 289};

    THEN("the target is not seen by the mouse")
    {
      CHECK_FALSE(mickey.isTargetInSight(target));
    }
  }

  GIVEN("The target is in the mouse field of view (differents boxes)")
  {
    target = {311, 105};
    THEN("the target is not seen by the mouse")
    {
      CHECK_FALSE(mickey.isTargetInSight(target));
    }
  }

  GIVEN("The target in the field of view of the mouse (same box)")
  {
    target = winnie.getPosition() +
 						  initialOrientation * viewDistance / 2;
    THEN("the target is seen by the animal")
    {
 		  CHECK(winnie.isTargetInSight(target));
    }
  }

  GIVEN("A target close to the mouse, on the borders of its view range")
  {
    target = winnie.getPosition() + Polar2Cartesian(viewRange / 2 - 0.002, 1);

    THEN("the target is seen by the animal")
    {
 		  CHECK(winnie.isTargetInSight(target));
    }
  }

  GIVEN("A target close to the mouse but outside its view range")
  {
    target = winnie.getPosition() + Polar2Cartesian((viewRange / 2) + 0.2, 1);

    THEN("the target is not seen by the animal")
    {
      CHECK_FALSE(winnie.isTargetInSight(target));
    }
  }

  GIVEN("A target in the view range of the mouse, at the upper limits of its view distance")
  {
    target = mickey.getPosition() - diagonalHeading * (viewDistance - 0.2);
    mickey.setHeading(-diagonalHeading);

    THEN("the target is seen by the mouse")
    {
      CHECK(mickey.isTargetInSight(target));
    }
  }
   
  GIVEN("A target in the view range of the mouse but too distant")
  { 
    target = mickey.getPosition() - diagonalHeading * (viewDistance + 1);
    mickey.setHeading(-diagonalHeading);	   
    THEN("the target is not seen by the mouse")
    {
 		 CHECK_FALSE(mickey.isTargetInSight(target));
    }
  }
   
  GIVEN("A new orientation of the animal and a target outside its view field")
  {
    const Vec2d newOrientation = Polar2Cartesian(70 * DEG_TO_RAD, 1);
 	  // "Oriente l'animal à 70°:
 	  winnie.setHeading(newOrientation);
 	  // Repositionne la cible sur l'abscisse, donc hors du champs de vision
 	  target = initialPosition + initialOrientation * 2;
	   
    THEN("the target is not seen by the animal")
    {
 		  CHECK_FALSE(winnie.isTargetInSight(target));
    }
  }
 
  GIVEN("A new orientation of the animal and a target inside its view field")
  {
 	  const Vec2d newOrientation = Polar2Cartesian(70 * DEG_TO_RAD, 1);
    // "Oriente l'animal à 70°:
 	  winnie.setHeading(newOrientation);
 	  //Création d'une cible en face de l'animal:
 	  target =  initialPosition + newOrientation * 2;

	  winnie.isTargetInSight(target);
	 
    THEN("the target is seen by the animal")
    {
 		  CHECK(winnie.isTargetInSight(target));
    }
  }
}
