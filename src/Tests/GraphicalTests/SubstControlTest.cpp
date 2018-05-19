/*
 * infosv
 * 2017
 * Marco Antognini
 * fev 2018
 * Antoine Madrona
 */

#include <Tests/GraphicalTests/LiverTest.hpp>
#include <Utility/Utility.hpp>
#include <Env/Organ.hpp>
#include <Env/Lab.hpp>
#include <Env/Mouse.hpp>

IMPLEMENT_MAIN(LiverTest)

void LiverTest::onRun()
{
    // Setup stats
	Application::onRun();

}
void LiverTest::onSimulationStart()
{
	mSimulationStart = true;
	mGuineaPig = new GuineaPigMouse(getApp().getLabSize()/2);
	mCurrentOrgan = new TransplantOrgan();
	mGuineaPig->transplant(mCurrentOrgan);
}

void LiverTest::onUpdate(sf::Time /*dt*/)
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

void LiverTest::onEvent(sf::Event event, sf::RenderWindow&)
{
if (event.type == sf::Event::KeyPressed) {
	switch (event.key.code) {
		case sf::Keyboard::B:
			{
				Vec2d physicalPos(getCursorPositionInView());
				CellCoord pos(mCurrentOrgan->toCellCoord(physicalPos));
				mCurrentOrgan->updateCellHandler(pos, Organ::Kind::Capillary);
			}
				break;
		case sf::Keyboard::H:
			{
				Vec2d physicalPos(getCursorPositionInView());
				CellCoord pos(mCurrentOrgan->toCellCoord(physicalPos));
				mCurrentOrgan->updateCellHandler(pos, Organ::Kind::Liver);
			}
				break;
	
			case sf::Keyboard::O:
			{
				getAppEnv().switchToView(ECM);
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
					//	std::cout << "## debug increase " << std::endl;
					getAppEnv().increaseCurrentSubst();
				}
			}
				break;

			case sf::Keyboard::PageDown: // decrease substance
			{
				if (isOrganViewOn()){
					//std::cout << "##debug decrease " << std::endl;
					getAppEnv().decreaseCurrentSubst();
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
		default:
			break;
			}
	}
}
