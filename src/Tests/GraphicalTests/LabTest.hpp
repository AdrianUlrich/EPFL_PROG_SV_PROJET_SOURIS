/*
 * infosv
 * fev 2018
 * Antoine Madrona
 */

#ifndef INFOSV_LAB_TEST_HPP
#define INFOSV_LAB_TEST_HPP

#include <Application.hpp>

/*!
 * Test confining and behaviour of mice in boxes
 *
 * Generate one target on click
 */

class LabTest : public Application
{
public:
	LabTest(int argc, char const** argv)
		: Application(argc, argv)
		{
		}
	virtual void onRun() override final;
		
	virtual void onEvent(sf::Event event, sf::RenderWindow& window) override final;
};
#endif // INFOSV_LAB_TEST_HPP
