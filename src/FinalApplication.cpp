/*
 * prjsv 2016
 * 2013, 2014, 2016
 * Marco Antognini
 */

#include <Config.hpp>
#include <FinalApplication.hpp>
#include <Env/Mouse.hpp>
#include <Env/Cheese.hpp>
#include <Env/Box.hpp>
#include <iostream>
#include <cassert>

IMPLEMENT_MAIN(FinalApplication);

void FinalApplication::onRun()
{
    // Setup stats
	Application::onRun();

}

void FinalApplication::onSimulationStart()
{
    // TODO add more stuff here
}

void FinalApplication::onEvent(sf::Event event, sf::RenderWindow&)
{
    if (event.type == sf::Event::KeyReleased) {
        switch (event.key.code){

			case sf::Keyboard::M:
			{
				if (!isOrganViewOn()){
					getAppEnv().addAnimal(new Mouse
										  (getCursorPositionInView()));
				}
			}
				break;
	
			case sf::Keyboard::F: // F for food
			{	if (!isOrganViewOn()){
						getAppEnv().addCheese(new Cheese
											  (getCursorPositionInView()));
					}
					
			}
				break;
			
			case sf::Keyboard::S: // S stands for Substance
			{
				if (isOrganViewOn()){
					toggleConcentrationView();
				}
			}
				break;


			case sf::Keyboard::Num1:
			{
				getAppEnv().updateTrackedAnimal();
			}
				break;

			case sf::Keyboard::T:
			{
				getAppEnv().trackAnimal(getCursorPositionInView());
            }
				break;
			
			case sf::Keyboard::O:
			{
				getAppEnv().switchToView(ECM);
            }
				break;	
			
			case sf::Keyboard::Z:
			{
				if (!isOrganViewOn()){
					getAppEnv().stopTrackingAnyEntity();
				}
			}
				break;

        default:
            break;
        }
    }
}
