/*
 * prjsv 2018
 * Antoine Madrona
 */

#include <Application.hpp>
#include <Env/CellLiver.hpp>
#include <Env/Organ.hpp>
#include <Env/CellBlood.hpp>
#include <Env/CellHandler.hpp>
#include <Env/CellOrgan.hpp>
#include <Tests/UnitTests/CheckUtility.hpp>
#include <Utility/Constants.hpp>

#include <catch.hpp>
#include <iostream>

class EmptyOrgan : public Organ
{
public:
	EmptyOrgan()
		:Organ(false)
		{
			generate();
		}
     // shadowing here
	// overriding is useless since polymorphic behaviour is ignored
	// in constructors
	void generate() 
	{
		// a minimal content for the organ
		reloadConfig();
		reloadCacheStructure();

	}
	// no need to update the representation for an empty organ
	void updateRepresentationAt(const CellCoord&) override
		{}

};


SCENARIO("Constructing CellBlood", "[CellHandler]")
{
	WHEN("There is no blood cell")
    {
    	
		Organ* emptyOrgan(new EmptyOrgan());
		
		CellCoord pos(getAppConfig().simulation_organ_nbCells/2,
					  getAppConfig().simulation_organ_nbCells/2);

        CellHandler ch(pos, emptyOrgan);

        THEN("no substance is present on the ECM ")
        {
			CHECK(isEqual(emptyOrgan->getConcentrationAt(pos,GLUCOSE), 0.));
        }
		THEN("if an artery cell is added and updated one time, no GLUCOSE is diffused on the ECM")
        {
			ch.setBlood(TypeBloodCell::ARTERY);
			ch.update(sf::seconds(0.1));
			CHECK(isEqual(emptyOrgan->getConcentrationAt(pos,GLUCOSE), 0.));
        }
		
		delete emptyOrgan;
    }



	WHEN("There is no blood cell")
    {
		Organ* emptyOrgan(new EmptyOrgan());
		
		CellCoord pos(getAppConfig().simulation_organ_nbCells/2,
					  getAppConfig().simulation_organ_nbCells/2);
		
        CellHandler ch(pos, emptyOrgan);
        THEN("no substance is present on the ECM ")
        {
			CHECK(isEqual(emptyOrgan->getConcentrationAt(pos,GLUCOSE), 0.));
        }
	
		THEN("if a capillary cell is added and updated one time, some GLUCOSE is diffused on the ECM")
        {
			double dt(0.01);
			CellCoord neighbor(pos.x-1, pos.y-1);
			ch.setBlood(TypeBloodCell::CAPILLARY);
			ch.update(sf::seconds(dt));
			CHECK_FALSE(isEqual(emptyOrgan->getConcentrationAt(pos,GLUCOSE), 0.));
			Substance s(0.,  getAppConfig().base_glucose, 0.);
			// null distance 
			double coeff = 0.5;
			s = s * coeff;
			CHECK_APPROX_EQUAL(emptyOrgan->getConcentrationAt(pos,GLUCOSE),
							   s[GLUCOSE]);
			// non null distance (one of the immediate neighbors)
			auto l(Vec2d(-1,-1).length());
			s = s * (1-erf(l/sqrt(4* getAppConfig().substance_diffusion_constant*dt)));
			CHECK_APPROX_EQUAL(emptyOrgan->getConcentrationAt(neighbor,GLUCOSE),
							   s[GLUCOSE]);
        }
		
		
		delete emptyOrgan;
	}
	
}
