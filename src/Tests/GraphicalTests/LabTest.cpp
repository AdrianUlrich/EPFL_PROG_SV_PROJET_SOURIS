/*
 * infosv
 * 2017
 * Marco Antognini
 * fev 2018
 * Antoine Madrona
 */

#include <Tests/GraphicalTests/LabTest.hpp>
#include <Env/Lab.hpp>
//#include <Env/Mouse.hpp> // A DECOMENTER pour src2.2
//#include <Env/Cheese.hpp> // A DECOMENTER pour src2.2
#include <Utility/Utility.hpp>

IMPLEMENT_MAIN(LabTest)

void LabTest::onRun()
{
	Application::onRun();

	getAppEnv().destroyBoxes();

	mLastCreatedCheese = nullptr;
}

void LabTest::onEvent(sf::Event event, sf::RenderWindow&)
{
if (event.type == sf::Event::KeyPressed) {
	switch (event.key.code) {
		case sf::Keyboard::M:
			{
				/*getAppEnv().addAnimal(new Mouse
				  (getCursorPositionInView()));*/
			}
				break;
	
		case sf::Keyboard::F: // F for food
			{
				/*
				Cheese* pieceOfCheese(new Cheese
									  (getCursorPositionInView()));
				if (getAppEnv().addCheese(pieceOfCheese))
				mLastCreatedCheese = pieceOfCheese; */
			}
				break;

		case sf::Keyboard::E: //E for "Eat"
		{
			/*if (mLastCreatedCheese != nullptr)
			  mLastCreatedCheese->provideEnergy(10);*/
		}
		break;
				
		case sf::Keyboard::Num0: 
			{
				getLab().destroyBoxes();
			}
				break;
		
		case sf::Keyboard::Num1:
			{
				getLab().reset();
				getLab().destroyBoxes();
				getLab().makeBoxes(1);
            }
            	break;

        case sf::Keyboard::Num2:
			{
				getLab().reset();
				getLab().destroyBoxes();
				getLab().makeBoxes(2);
            }
			break;
			
		case sf::Keyboard::Num3:
		{
			getLab().reset();
			getLab().destroyBoxes();
			getLab().makeBoxes(3);
		}
		break;
		
		case sf::Keyboard::Num4:
		{
			getLab().reset();
			getLab().destroyBoxes();
			getLab().makeBoxes(4);
		}
		break;

		case sf::Keyboard::Num5:
		{
			getLab().reset();
			getLab().destroyBoxes();
			getLab().makeBoxes(5);
		}
		break;  
		default:
			break;
			}
	}
}
