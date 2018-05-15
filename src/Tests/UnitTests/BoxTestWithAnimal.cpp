/*
 * prjsv 2018
 * fev 2018
 * Antoine Madrona
 */

#include <Tests/UnitTests/CheckUtility.hpp>
#include <Application.hpp>
#include <Env/Box.hpp>
#include <Env/Mouse.hpp>

#include <catch.hpp>
#include <iostream>


SCENARIO("Constructing Box", "[Box]")
{
    WHEN("Explicit constructor is used with default values")
    {
        Box box1 ({400, 400});

        THEN("Attributes are well initialised")
        {
            CHECK(box1.getCenter().x == 400);
            CHECK(box1.getCenter().y == 400);
            CHECK(box1.getHeight() == 300);
            CHECK(box1.getWidth() == 300);
            CHECK(box1.getWallWidth() == 10);
            CHECK(box1.isEmpty()); 
        }
    }
}

SCENARIO("Confining animals in a Box", "[Box]")
{
	WHEN("Creating a box")
	{
		Box box({400,400}, 300, 300, 10);
		THEN("it is empty (no animal inside)"){
			CHECK(box.isEmpty());
		}
	}
	
    WHEN("Trying to put an Animal in a empty box")
    {
    	Box box({400,400}, 300, 300, 10);
		Mouse mickey({400,400});
		THEN("The animal can be confined")
    	{
			CHECK(box.isEmpty());
			CHECK(mickey.canBeConfinedIn(&box));
			box.addOccupant();
		}
    }
    WHEN("Trying to put an Animal in an occupied box")
    {
        Box box({400,400}, 300, 300, 10);
        box.addOccupant();
        Mouse winnie ({280, 280});

        THEN("Can't add another animal in the box")
        {
            CHECK_FALSE(winnie.canBeConfinedIn(&box));
        }

        box.reset();

        THEN("The animal is no more in the box after using reset()")
        {
            CHECK(box.isEmpty());
        }
	}

	 WHEN("Trying to put an Animal in a empty but too distant box")
    {
    	Box box({400,400}, 300, 300, 10); 
		Mouse mickey({0,0});
		THEN("The animal can't be confined in the box")
    	{
			CHECK(box.isEmpty());
			CHECK_FALSE(mickey.canBeConfinedIn(&box));
		}
	}
    WHEN("Trying to put an Animal on the walls of a box")
    {
        Box box({400,400}, 300, 300, 20);
        Mouse mickey({400,245});
        Mouse winnie({545,245});
        Mouse ratatouille({545,545});
        THEN("The animal can't be confined in the box")
        {
            CHECK(box.isEmpty());
            CHECK_FALSE(mickey.canBeConfinedIn(&box)); //middle of top wall
            CHECK_FALSE(winnie.canBeConfinedIn(&box)); //top right corner of the box
            CHECK_FALSE(ratatouille.canBeConfinedIn(&box)); //bottom right corner of the box
        }
    }
}


SCENARIO("Testing isPositionInside method", "[Box]")
{
	GIVEN("A Box centered in (400,400)")
	{
		Box box({400,400});

		WHEN("Testing position (400, 400)")
		{
			THEN("(400, 400) is inside")
			{
				CHECK(box.isPositionInside({400,400}));
			}
		}

        WHEN("Testing position (530, 400)")
        {
            THEN("(530, 400) is inside")
            {
                CHECK(box.isPositionInside({530,400}));
            }
		}

        WHEN("Testing position (270, 400)")
        {
            THEN("(270, 400) is inside")
            {
                CHECK(box.isPositionInside({270,400}));
            }
        }

        WHEN("Testing position (400, 530)")
        {
            THEN("(400, 530) is inside")
            {
                CHECK(box.isPositionInside({400,530}));
            }
        }

        WHEN("Testing position (400, 270)")
        {
            THEN("(400, 270) is inside")
            {
                CHECK(box.isPositionInside({400,270}));
            }
        }

        WHEN("Testing position (540, 540)")
        {
            THEN("(540, 540) is not inside")
            {
                CHECK_FALSE(box.isPositionInside({540,540}));
            }
        }

        WHEN("Testing position (260, 260)")
        {
            THEN("(260, 260) is not inside")
            {
                CHECK_FALSE(box.isPositionInside({260,260}));
            }
        }

		
        WHEN("Testing position (270, 270)")
        {
            THEN("(260, 260) is not inside")
            {
                CHECK(box.isPositionInside({270,270}));
            }
        }

        WHEN("Testing position (538, 468)")
        {
            THEN("(538, 468) is inside")
            {
                CHECK(box.isPositionInside({538,468}));
            }
        }

        WHEN("Testing position (0, 0)")
        {
            THEN("(0, 0) is not inside")
            {
                CHECK_FALSE(box.isPositionInside({0,0}));
            }
        }

        WHEN("Testing position (400, 700)")
        {
            THEN("(400, 700) is not inside")
            {
                CHECK_FALSE(box.isPositionInside({400,700}));
            }
        }

        WHEN("Testing position (700, 400)")
        {
            THEN("(700, 400) is not inside")
            {
                CHECK_FALSE(box.isPositionInside({700,400}));
            }
        }

        WHEN("Testing position (600, 600)")
        {
            THEN("(600, 600) is outside")
            {
                CHECK_FALSE(box.isPositionInside({600,600}));
            }
        }

        WHEN("Testing position (249, 400)")
        {
            THEN("(249, 400) is not inside")
            {
                CHECK_FALSE(box.isPositionInside({249,400}));
            }
        }

        WHEN("Testing position (249, 249)")
        {
            THEN("(249, 249) is not inside")
            {
                CHECK_FALSE(box.isPositionInside({249,249}));
            }
        }
	}
}

SCENARIO("Testing isPositionOnWall method (using isPositionInside too)", "[Box]")
{
    GIVEN("A Box centered in (400,400)")
    {
        Box box({400,400});

        WHEN("Testing position (400, 400)")
        {
            THEN("(400, 400) is inside and not on a wall")
            {
                CHECK((box.isPositionInside({400,400}) && ! box.isPositionOnWall({400,400})));
                CHECK_FALSE(box.isPositionOnWall({400,400}));
            }
        }

        WHEN("Testing position (549, 400)")
        {
            THEN("(549, 400) is on a wall")
            {
                CHECK((!box.isPositionInside({549,400}) && box.isPositionOnWall({549,400})));
                CHECK(box.isPositionOnWall({549,400}));
            }
        }

        WHEN("Testing position (540, 400)")
        {
            THEN("(540, 400) is on a wall")
            {
                CHECK((!box.isPositionInside({540,400}) && box.isPositionOnWall({540,400})));
                CHECK(box.isPositionOnWall({540,400}));
            }
        }

        WHEN("Testing position (251, 400)")
        {
            THEN("(251, 400) is on a wall")
            {
                CHECK((!box.isPositionInside({251,400}) && box.isPositionOnWall({251,400})));
                CHECK(box.isPositionOnWall({251,400}));
            }
        }

        WHEN("Testing position (260, 400)")
        {
            THEN("(260, 400) is on a wall")
            {
                CHECK((!box.isPositionInside({260,400}) && box.isPositionOnWall({260,400})));
                CHECK(box.isPositionOnWall({260,400}));
            }
        }

        WHEN("Testing position (400, 251)")
        {
            THEN("(400, 251) is on a wall")
            {
                CHECK((!box.isPositionInside({400,251}) && box.isPositionOnWall({400,251})));
                CHECK(box.isPositionOnWall({400,251}));
            }
        }

        WHEN("Testing position (400, 260)")
        {
            THEN("(400, 260) is on a wall")
            {
                CHECK((!box.isPositionInside({400,260}) && box.isPositionOnWall({400,260})));
                CHECK(box.isPositionOnWall({400,260}));
            }
        }

        WHEN("Testing position (600, 600)")
        {
            THEN("(600, 600) is not inside and not on a wall")
            {
                CHECK((!box.isPositionInside({600,600}) && !box.isPositionOnWall({600,600}) ));
            }
        }

        WHEN("Testing position (539, 539)")
        {
            THEN("(539, 539) is not on a wall")
            {
                CHECK_FALSE(box.isPositionOnWall({539,539}));
            }
        }

        WHEN("Testing position (400, 539)")
        {
            THEN("(400, 539) is not on a wall")
            {
                CHECK(( box.isPositionInside({400,539}) && !box.isPositionOnWall({400,539}) ));
            }
        }

        WHEN("Testing position (412, 398)")
        {
            THEN("(412, 398) is not on a wall")
            {
                CHECK((box.isPositionInside({412,398}) && !box.isPositionOnWall({412,398}) ));
            }
        }

        WHEN("Testing position (412, 545)")
        {
            THEN("(412, 545) is on a wall")
            {
                CHECK(( !box.isPositionInside({412,545}) && box.isPositionOnWall({412,545}) ));
            }
        }

        WHEN("Testing position (243.7, 600)")
        {
            THEN("(243.7, 600) is not on a wall")
            {
                CHECK_FALSE(box.isPositionOnWall({243.7,600}));
            }
        }
    }
}

SCENARIO("Walls & Limits getters", "[Box]")
{
    GIVEN("A Box centered in (400, 300)")
    {
        Box box({400,300});

        WHEN("Getting the top and bottom limits")
        {
            THEN("The right values are returned")
            {
                CHECK(box.getTopLimit() < box.getBottomLimit());
                CHECK(box.getTopLimit() == 150);
                CHECK(box.getBottomLimit() == 450);
            }
        }

        WHEN("Getting the left and right limits")
        {
            THEN("The right values are returned")
            {
                CHECK(box.getLeftLimit() < box.getRightLimit());
                CHECK(box.getLeftLimit() == 250);
                CHECK(box.getRightLimit() == 550);
            }
        }

        WHEN("Getting the limits with offset")
        {
            THEN("The right values are returned (half of wallwidth took in account)")
            {
                CHECK(box.getTopLimit(true) == 160);
                CHECK(box.getBottomLimit(true) == 440);
                CHECK(box.getLeftLimit(true) == 260);
                CHECK(box.getRightLimit(true) == 540);
            }
        }
    }
}
