/*
* prjsv 2018
* 2016
* Marco Antognini
* fev 2018
* Antoine Madrona
*/

#include <Application.hpp>
#include <Env/Mouse.hpp>
#include <Env/Cheese.hpp>
#include <Config.hpp>
#include <catch.hpp>
#include <iostream>

SCENARIO("Mouse vs SimulatedEntity", "[Mouse]")
{

	SimulatedEntity* mickey(new Mouse({0,0}));
    SimulatedEntity* winnie(new Mouse({0,0}));
    SimulatedEntity* gruyere(new Cheese({0,0}));

	GIVEN("A mouse")
	{
		THEN("No autophagy")
		{
			CHECK_FALSE(mickey->eatable(mickey));
		}
	}

	GIVEN("Two mice")
	{
		THEN("No cannibalism")
		{
			CHECK_FALSE(mickey->eatable(winnie));
			CHECK_FALSE(winnie->eatable(mickey));
		}
	}

	GIVEN("A mouse and a cheese")
	{
		THEN("the cheese is eatable by the mouse")
		{
			CHECK(mickey->eatable(gruyere));
		}
		THEN("the mouse is not eatable by the cheese")	
		{
			CHECK_FALSE(gruyere->eatable(mickey));
		}
	}

	delete mickey;
	delete winnie;
	delete gruyere;
}

SCENARIO("Cheese vs SimulatedEntity", "[Cheese]")
{

	SimulatedEntity* mickey(new Mouse({0,0}));
    SimulatedEntity* parmesan(new Cheese({0,0}));
    SimulatedEntity* gruyere(new Cheese({0,0}));

	GIVEN("A cheese")
	{
		THEN("No autophagy")
		{
			CHECK_FALSE(parmesan->eatable(parmesan));
		}
	}

	GIVEN("Two cheeses")
	{
		THEN("No cannibalism")
		{
			CHECK_FALSE(gruyere->eatable(parmesan));
			CHECK_FALSE(parmesan->eatable(gruyere));
		}
	}

	GIVEN("A cheese and a mouse")
	{   
		THEN("The cheese is eatable by the mouse")
		{
			CHECK(mickey->eatable(parmesan));
		}
		THEN("the mouse is not eatable by the cheese")	
		{
			CHECK_FALSE(parmesan->eatable(mickey));
		}
	}

	delete mickey;
	delete parmesan;
	delete gruyere;
}
