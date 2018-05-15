/*
 * infosv
 * fev 2018
 * Antoine Madrona
 */

#ifndef INFOSV_BLOODSYSTEM_TEST_HPP
#define INFOSV_BLOODSYSTEM_TEST_HPP

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
		createBloodSystem(false); // blood system only with artery
		updateRepresentation();
	}
public:
	// breaking encapsulation for the TransplantOrgan class
	void generateCapillaryOneStep(CellCoord& current_position, const CellCoord& initial_dir, int& nbCells, const int& maxLength) override;

	CellCoord toCellCoord(Vec2d const& substrateCoord) const override
		{
			return Organ::toCellCoord(substrateCoord);
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

class BloodSystemTest : public Application
{
public:
	BloodSystemTest(int argc, char const** argv)
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
	CellCoord mCurrentStart;
	CellCoord mCurrentDir;
	bool mStartCapillary;
	bool mSimulationStart;
	int mCurrentCapillaryLength;
};
#endif // INFOSV_BLOODSYSTEM_TEST_HPP
