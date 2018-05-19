/*
 * infosv
 * fev 2018
 * Antoine Madrona
 */

#ifndef INFOSV_DIFFUSION_TEST_HPP
#define INFOSV_DIFFUSION_TEST_HPP

#include <Application.hpp>
#include <Env/Mouse.hpp>
#include <Env/Organ.hpp>

/*!
 * Test generation of capilarity
 *
 * Choose one point of the artery
 * Generate one cell of capilary on click
 */

class TransplantOrgan : public Organ
{
public:
	TransplantOrgan()
		:Organ(false) // precludes content generation
		{
		
			generate();
		}

	// shadowing here
	// overriding is useless since polymorphic behaviour is ignored
	// in constructors
	void generate() 
	{
		reloadConfig();
		reloadCacheStructure();
		updateRepresentation();
	}
public:
	// breaking encapsulation for testing purpose:
	virtual CellCoord toCellCoord(Vec2d const& substrateCoord) const override{
		return Organ::toCellCoord(substrateCoord);
	}
	virtual void updateCellHandler(CellCoord const& pos, Kind kind) override
		{
			Organ::updateCellHandler(pos, kind);
		}
};


class GuineaPigMouse : public Mouse
{
public:
	GuineaPigMouse(Vec2d const& position)
	: Mouse(position)
	{}
	
	void transplant(TransplantOrgan* org)
	{
		setOrgan(org);
	}

};

class DiffusionTest : public Application
{
public:
	DiffusionTest(int argc, char const** argv)
		: Application(argc, argv)
		{
		}
	virtual void onRun() override final;
	virtual void onUpdate(sf::Time dt) override final;
	virtual void onEvent(sf::Event event, sf::RenderWindow& window) override final;
	virtual void onSimulationStart() override final;
private:
	TransplantOrgan* mCurrentOrgan;
	GuineaPigMouse* mGuineaPig;
	bool mSimulationStart;
};
#endif // INFOSV_DIFFUSION_TEST_HPP
