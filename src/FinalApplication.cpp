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
				
				 // A DECOMMENTER QUAND NECESSAIRE	
			case sf::Keyboard::X: 
			{
				if (isOrganViewOn()){
					getAppEnv().setCancerAt(getCursorPositionInView());
				}

			}
				break;
				
			case sf::Keyboard::N: // next substance
			{
				if (isOrganViewOn()){
					getAppEnv().nextSubstance();
				}
			
			}
				break;

			case sf::Keyboard::PageUp: // increase substance
			{
				if (isOrganViewOn()){
					getAppEnv().increaseCurrentSubst();
				}
			}
				break;

			case sf::Keyboard::PageDown: // decrease substance
			{
				if (isOrganViewOn()){
					getAppEnv().decreaseCurrentSubst();
				}
				
			}
				break;

			case sf::Keyboard::Num1:
			{
				getAppEnv().updateTrackedAnimal();
			}
				break;

			case sf::Keyboard::Num2:
			{
				if (isOrganViewOn()){
					getAppEnv().increaseCurrentSubst();
				}
			}
				break;

			case sf::Keyboard::Num3:
			{
				if (isOrganViewOn()){
					getAppEnv().decreaseCurrentSubst();
				}
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
