/*
 * infosv
 * 2017
 * Marco Antognini
 * fev 2018
 * Antoine Madrona
 */

#include <Tests/GraphicalTests/DiffusionTest.hpp>
#include <Utility/Utility.hpp>
#include <Env/Organ.hpp>
#include <Env/Lab.hpp>
#include <Env/Mouse.hpp>

IMPLEMENT_MAIN(DiffusionTest)

void DiffusionTest::onRun()
{
    // Setup stats
	Application::onRun();


}
void DiffusionTest::onSimulationStart()
{
	mCurrentOrgan = new TransplantOrgan();
	mGuineaPig = new GuineaPigMouse(getApp().getLabSize()/2);
	mGuineaPig->transplant(mCurrentOrgan);
	mSimulationStart = true;
}

void DiffusionTest::onUpdate(sf::Time /*dt*/)
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

void DiffusionTest::onEvent(sf::Event event, sf::RenderWindow&)
{
if (event.type == sf::Event::KeyPressed) {
	switch (event.key.code) {
		case sf::Keyboard::A:
			{
				Vec2d physicalPos(getCursorPositionInView());
				CellCoord pos(mCurrentOrgan->toCellCoord(physicalPos));
				mCurrentOrgan->updateCellHandler(pos, Organ::Kind::Artery);
			}
				break;
		case sf::Keyboard::B:
			{
				Vec2d physicalPos(getCursorPositionInView());
				CellCoord pos(mCurrentOrgan->toCellCoord(physicalPos));
				mCurrentOrgan->updateCellHandler(pos, Organ::Kind::Capillary);
			}
				break;
	
			case sf::Keyboard::O:
			{
				getAppEnv().switchToView(ECM);
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
