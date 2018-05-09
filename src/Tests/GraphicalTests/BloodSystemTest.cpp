/*
 * infosv
 * 2017
 * Marco Antognini
 * fev 2018
 * Antoine Madrona
 */

#include <Tests/GraphicalTests/BloodSystemTest.hpp>
#include <Utility/Utility.hpp>
#include <Env/Organ.hpp>
#include <Env/Lab.hpp>
#include <Env/Mouse.hpp>

IMPLEMENT_MAIN(BloodSystemTest)

void BloodSystemTest::onRun()
{
    // Setup stats
	Application::onRun();
}
void BloodSystemTest::onSimulationStart()
{
	mCurrentOrgan = new TransplantOrgan();
	mGuineaPig = new GuineaPigMouse(getLabSize()/2);
	mGuineaPig->transplant(mCurrentOrgan);
	mStartCapillary = true;
	mSimulationStart = true;
	mCurrentCapillaryLength = 0;
}

void BloodSystemTest::onUpdate(sf::Time /*dt*/)
{
	if (mSimulationStart){
		getAppEnv().destroyBoxes();
		getAppEnv().makeBoxes(1);
		getAppEnv().addAnimal(mGuineaPig);
		getAppEnv().trackAnimal(mGuineaPig);
		getApp().switchToView(ECM);
		mSimulationStart = false;
	}
}

void TransplantOrgan::generateCapillaryOneStep(CellCoord& current_position, const CellCoord& initial_dir, int& nbCells, const int& maxLength)
		{

			Organ::generateCapillaryOneStep(current_position, initial_dir, nbCells, maxLength);
		}

void BloodSystemTest::onEvent(sf::Event event, sf::RenderWindow&)
{
if (event.type == sf::Event::KeyPressed) {
	switch (event.key.code) {
			case sf::Keyboard::Num0: // to start a new capillary
			{
				mStartCapillary = true;
				mCurrentCapillaryLength = 0;
			}
			break;
			
		case sf::Keyboard::Add:
			{
				if (mStartCapillary)
				{
					auto position(getCursorPositionInView());
					mCurrentStart = mCurrentOrgan->toCellCoord(position);
					mStartCapillary = false;
					mCurrentDir = CellCoord(1,0);					

				}
		        mCurrentOrgan->generateCapillaryOneStep(mCurrentStart, mCurrentDir, mCurrentCapillaryLength, getAppConfig().simulation_organ_nbCells/2);
            }
            	break;
		
		case sf::Keyboard::Subtract:
			{
				if (mStartCapillary)
				{
					auto position(getCursorPositionInView());
					mCurrentStart = mCurrentOrgan->toCellCoord(position);
					mStartCapillary = false;
					mCurrentDir = CellCoord(-1,0);					

				}
		        mCurrentOrgan->generateCapillaryOneStep(mCurrentStart, mCurrentDir, mCurrentCapillaryLength, getAppConfig().simulation_organ_nbCells/2);
            }
            	break;

				case sf::Keyboard::O:
			{
				getAppEnv().switchToView(ECM);
            }
				break;	
		default:
			break;
			}
	}
}
