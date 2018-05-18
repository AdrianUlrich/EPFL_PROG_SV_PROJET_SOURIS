/*
 * infosv
 * 2017
 * Marco Antognini
 * fev 2018
 * Antoine Madrona
 */

#include <Tests/GraphicalTests/DrawOrganTest.hpp>
#include <Utility/Utility.hpp>
#include <Env/Organ.hpp>
#include <Env/Lab.hpp>
#include <Env/Mouse.hpp>

IMPLEMENT_MAIN(DrawOrganTest)

void DrawOrganTest::onRun()
{
    // Setup stats
	Application::onRun();
}
void DrawOrganTest::onSimulationStart()
{
	mCurrentOrgan = new TransplantOrgan();
	mGuineaPig = new GuineaPigMouse(getLabSize()/2);
	mGuineaPig->transplant(mCurrentOrgan);
	mSimulationStart = true;
}

void DrawOrganTest::onUpdate(sf::Time /*dt*/)
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

void DrawOrganTest::onEvent(sf::Event event, sf::RenderWindow&)
{
if (event.type == sf::Event::KeyPressed) {
	switch (event.key.code) {
		case sf::Keyboard::B:
			{
				Vec2d physicalPos(getCursorPositionInView());
				CellCoord pos(mCurrentOrgan->toCellCoord(physicalPos));
				mCurrentOrgan->updateCellHandler(pos, Organ::Kind::Artery);
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
		default:
			break;
			}
	}
}
