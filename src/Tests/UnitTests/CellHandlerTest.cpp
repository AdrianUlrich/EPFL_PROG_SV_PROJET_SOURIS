/*
 * prjsv 2018
 * Antoine Madrona
 */

#include <Application.hpp>
#include <Env/CellLiver.hpp>
#include <Env/CellBlood.hpp>
#include <Env/CellECM.hpp>
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
		reloadConfig();
	}
	void updateRepresentationAt(const CellCoord&) override
		{}
	
	int getGridSize() const 
		{
			return getAppConfig().simulation_organ_nbCells;
		}
	
};

SCENARIO("Constructing CellHandler", "[CellHandler]")
{
    WHEN("Explicit Constructor is used")
    {
    	
		EmptyOrgan* emptyOrgan(new EmptyOrgan());
		CellCoord pos(emptyOrgan->getGridSize()/2,emptyOrgan->getGridSize()/2);
        CellHandler ch(pos, emptyOrgan);

        THEN("CellHandler has ECM but no Liver and no Blood")
        {
            CHECK_FALSE(ch.hasLiver());
            CHECK_FALSE(ch.hasBlood());
            CHECK(ch.hasECM());
        }
		delete emptyOrgan;
    }
}

SCENARIO("Manipulating/Constructing a CellHandler", "[CellHandler]")
{
	GIVEN("An organ with 4 CellHandlers")
	{
		EmptyOrgan* organ(new EmptyOrgan());
		auto x(organ->getGridSize()/2);
		auto y(organ->getGridSize()/2);
		CellCoord pos1(x,y);
        CellCoord pos2(x+1,y);
        CellCoord pos3(x,y+1);
        CellCoord pos4(x+1,y+1);

        CellHandler CellHandler1(pos1, organ);
        CellHandler CellHandler2(pos2, organ);
        CellHandler CellHandler3(pos3, organ);
        CellHandler CellHandler4(pos4, organ);

        WHEN("Adding Blood (type capillary) to CellHandler1")
        {
            CellHandler1.setBlood(TypeBloodCell::CAPILLARY);
            THEN("The Capillary is well added")
            {
                CHECK(CellHandler1.hasBlood());
                CHECK_FALSE(CellHandler1.hasLiver());
            }
        }

        WHEN("Adding Liver to CellHandler1")
        {
            CellHandler1.setLiver();
            THEN("The Liver is well added")
            {
                CHECK_FALSE(CellHandler1.hasBlood());
                CHECK(CellHandler1.hasLiver());
            }
        }
		delete organ;
    }
}

SCENARIO("updateSubstance and liverTakeFromEcm methods, [CellHandler]")
{
    GIVEN("An organ with 4 CellHandlers")
    {
		EmptyOrgan* organ(new EmptyOrgan());
		auto x(organ->getGridSize()/2);
		auto y(organ->getGridSize()/2);
		CellCoord pos1(x,y);

        CellHandler CellHandler1(pos1, organ);

		WHEN("Liver takes 50% GLUCOSE from its ECM and ECM has (200.0, 300.0, 400.) as Substance (1 step)")
        {
			Substance substance(200., 300., 400.);
            CellHandler1.setLiver();
			CellHandler1.updateSubstance(substance);

			THEN("before taking, Liver has zero GLUCOSE")
            {
				 CHECK(CellHandler1.getECMQuantity(GLUCOSE) == 300.);
				 CHECK(CellHandler1.getECMQuantity(VGEF) == 200.);
				 CHECK(CellHandler1.getECMQuantity(BROMOPYRUVATE) == 400.);
				 CHECK(CellHandler1.getLiverQuantity(GLUCOSE) == 0.);
				 CHECK(CellHandler1.getLiverQuantity(BROMOPYRUVATE) == 0.);
				 CHECK(CellHandler1.getLiverQuantity(VGEF) == 0.);
			}

			CellHandler1.liverTakeFromEcm(GLUCOSE, 0.5);

            THEN("after taking, ECM and Liver are well updated")
            {
				CHECK_APPROX_EQUAL(CellHandler1.getECMQuantity(GLUCOSE),150.);
				CHECK(CellHandler1.getECMQuantity(VGEF) == 200.);
				CHECK(CellHandler1.getECMQuantity(BROMOPYRUVATE) == 400.);
				CHECK_APPROX_EQUAL(CellHandler1.getLiverQuantity(GLUCOSE), 150.);
				CHECK(CellHandler1.getLiverQuantity(BROMOPYRUVATE) == 0.);
				CHECK(CellHandler1.getLiverQuantity(VGEF) == 0.);
            }
		}

        WHEN("Liver takes 5% GLUCOSE from its ECM and ECM has (200.0, 300.0, 400.) as Substance (10 steps)")
        {
            Substance substance(200., 300., 400.);
            CellHandler1.setLiver();
            CellHandler1.updateSubstance(substance);
            THEN("before taking, Liver has zero GLUCOSE")
            {
                 CHECK(CellHandler1.getECMQuantity(GLUCOSE) == 300.);
                 CHECK(CellHandler1.getECMQuantity(VGEF) == 200.);
                 CHECK(CellHandler1.getECMQuantity(BROMOPYRUVATE) == 400.);
                 CHECK(CellHandler1.getLiverQuantity(GLUCOSE) == 0.);
                 CHECK(CellHandler1.getLiverQuantity(BROMOPYRUVATE) == 0.);
                 CHECK(CellHandler1.getLiverQuantity(VGEF) == 0.);
            }

            for (unsigned int i(0); i<10; ++i)
            {
                CellHandler1.liverTakeFromEcm(GLUCOSE, 0.05);
            }

            THEN("after taking (10 steps), ECM and Liver are well updated")
            {
                CHECK_APPROX_EQUAL(CellHandler1.getECMQuantity(GLUCOSE), 179.621);
                CHECK_APPROX_EQUAL(CellHandler1.getECMQuantity(VGEF), 200.);
                CHECK_APPROX_EQUAL(CellHandler1.getECMQuantity(BROMOPYRUVATE), 400.);
                CHECK_APPROX_EQUAL(CellHandler1.getLiverQuantity(GLUCOSE), 120.379);
                CHECK_APPROX_EQUAL((CellHandler1.getECMQuantity(GLUCOSE)+
                    CellHandler1.getLiverQuantity(GLUCOSE)), 300);
                CHECK(CellHandler1.getLiverQuantity(BROMOPYRUVATE) == 0.);
                CHECK(CellHandler1.getLiverQuantity(VGEF) == 0.);
            }
        }

        WHEN("Liver takes 50% GLUCOSE from its ECM and ECM has (0., 0., 0.) as Substance (1 step)")
        {
            Substance substance(0., 0., 0.);
            CellHandler1.setLiver();
            CellHandler1.updateSubstance(substance);
            THEN("before taking, Liver has zero GLUCOSE")
            {
                 CHECK(CellHandler1.getECMQuantity(GLUCOSE) == 0.);
                 CHECK(CellHandler1.getECMQuantity(VGEF) == 0.);
                 CHECK(CellHandler1.getECMQuantity(BROMOPYRUVATE) == 0.);
                 CHECK(CellHandler1.getLiverQuantity(GLUCOSE) == 0.);
                 CHECK(CellHandler1.getLiverQuantity(BROMOPYRUVATE) == 0.);
                 CHECK(CellHandler1.getLiverQuantity(VGEF) == 0.);
            }
            CellHandler1.liverTakeFromEcm(GLUCOSE, 0.5);
            THEN("after taking, ECM and Liver are well updated")
            {
                CHECK_APPROX_EQUAL(CellHandler1.getECMQuantity(GLUCOSE), 0.);
                CHECK(CellHandler1.getECMQuantity(VGEF) == 0.);
                CHECK(CellHandler1.getECMQuantity(BROMOPYRUVATE) == 0.);
                CHECK_APPROX_EQUAL(CellHandler1.getLiverQuantity(GLUCOSE), 0.);
                CHECK(CellHandler1.getLiverQuantity(BROMOPYRUVATE) == 0.);
                CHECK(CellHandler1.getLiverQuantity(VGEF) == 0.);
            }
        }

        WHEN("Liver takes 0% VGEF from its ECM and ECM has (200., 400., 300.) as Substance (1 step)")
        {
            Substance substance(400., 400., 300.);
            CellHandler1.setLiver();
            CellHandler1.updateSubstance(substance);
            THEN("before taking, Liver has zero VGEF")
            {
                 CHECK(CellHandler1.getECMQuantity(VGEF) == 400.);
                 CHECK(CellHandler1.getECMQuantity(GLUCOSE) == 400.);
                 CHECK(CellHandler1.getECMQuantity(BROMOPYRUVATE) == 300.);
                 CHECK(CellHandler1.getLiverQuantity(VGEF) == 0.);
                 CHECK(CellHandler1.getLiverQuantity(GLUCOSE) == 0.);
                 CHECK(CellHandler1.getLiverQuantity(BROMOPYRUVATE) == 0.);
            }
            CellHandler1.liverTakeFromEcm(VGEF, 0.);
            THEN("after taking, ECM and Liver are well updated")
            {
                CHECK_APPROX_EQUAL(CellHandler1.getECMQuantity(VGEF), 400.);
                CHECK(CellHandler1.getECMQuantity(GLUCOSE) == 400.);
                CHECK(CellHandler1.getECMQuantity(BROMOPYRUVATE) == 300.);
                CHECK_APPROX_EQUAL(CellHandler1.getLiverQuantity(GLUCOSE), 0.);
                CHECK(CellHandler1.getLiverQuantity(BROMOPYRUVATE) == 0.);
                CHECK(CellHandler1.getLiverQuantity(VGEF) == 0.);
            }
        }

        WHEN("Liver takes 60% BROMOPYRUVATE from its ECM and ECM has (200., 400., 2*SUBSTANCE_PRECISION) as Substance (1 step)")
        {
            Substance substance(400., 400., 2*SUBSTANCE_PRECISION);
            CellHandler1.setLiver();
            CellHandler1.updateSubstance(substance);
            THEN("before taking, Liver has zero BROMOPYRUVATE")
            {
                 CHECK(CellHandler1.getECMQuantity(VGEF) == 400.);
                 CHECK(CellHandler1.getECMQuantity(GLUCOSE) == 400.);
                 CHECK_APPROX_EQUAL(CellHandler1.getECMQuantity(BROMOPYRUVATE), 2*SUBSTANCE_PRECISION);
                 CHECK(CellHandler1.getLiverQuantity(VGEF) == 0.);
                 CHECK(CellHandler1.getLiverQuantity(GLUCOSE) == 0.);
                 CHECK(CellHandler1.getLiverQuantity(BROMOPYRUVATE) == 0.);
            }
            CellHandler1.liverTakeFromEcm(BROMOPYRUVATE, 0.6);
            THEN("after taking, ECM and Liver are well updated (taking care of SUBSTANCE_PRECISION aspect)")
            {
                CHECK(CellHandler1.getECMQuantity(VGEF) == 400.);
                CHECK(CellHandler1.getECMQuantity(GLUCOSE) == 400.);
                CHECK_APPROX_EQUAL(CellHandler1.getECMQuantity(BROMOPYRUVATE), 0.);
                CHECK(CellHandler1.getLiverQuantity(VGEF) == 0.);
                CHECK(CellHandler1.getLiverQuantity(GLUCOSE) == 0.);
                CHECK_APPROX_EQUAL(CellHandler1.getLiverQuantity(BROMOPYRUVATE), 1.2*SUBSTANCE_PRECISION);
            }
        }

        WHEN("Liver takes 1% BROMOPYRUVATE from its ECM and ECM has (200., 400., 2*SUBSTANCE_PRECISION) as Substance (1 step)")
        {
            Substance substance(400., 400., 2*SUBSTANCE_PRECISION);
            CellHandler1.setLiver();
            CellHandler1.updateSubstance(substance);
            THEN("before taking, Liver has zero BROMOPYRUVATE")
            {
                 CHECK(CellHandler1.getECMQuantity(VGEF) == 400.);
                 CHECK(CellHandler1.getECMQuantity(GLUCOSE) == 400.);
                 CHECK_APPROX_EQUAL(CellHandler1.getECMQuantity(BROMOPYRUVATE), 2*SUBSTANCE_PRECISION);
                 CHECK(CellHandler1.getLiverQuantity(VGEF) == 0.);
                 CHECK(CellHandler1.getLiverQuantity(GLUCOSE) == 0.);
                 CHECK(CellHandler1.getLiverQuantity(BROMOPYRUVATE) == 0.);
            }
            CellHandler1.liverTakeFromEcm(BROMOPYRUVATE, 0.01);
            THEN("after taking, ECM and Liver are well updated (taking care of SUBSTANCE_PRECISION aspect)")
            {
                CHECK(CellHandler1.getECMQuantity(VGEF) == 400.);
                CHECK(CellHandler1.getECMQuantity(GLUCOSE) == 400.);
                CHECK_APPROX_EQUAL(CellHandler1.getECMQuantity(BROMOPYRUVATE), 1.98*SUBSTANCE_PRECISION);
                CHECK(CellHandler1.getLiverQuantity(VGEF) == 0.);
                CHECK(CellHandler1.getLiverQuantity(GLUCOSE) == 0.);
                CHECK_APPROX_EQUAL(CellHandler1.getLiverQuantity(BROMOPYRUVATE), 0.);
            }
        }
		delete organ;
	}
}

SCENARIO("isOut() method", "[CellHandler]")
{
    GIVEN("One CellHandler and several coordinates")
    {
		EmptyOrgan* emptyOrgan(new EmptyOrgan());
		auto width = emptyOrgan->getGridSize();
		auto height = emptyOrgan->getGridSize();
	

        CellCoord cc1(width/2,height/2);

		CellHandler CH(cc1, emptyOrgan);
		
        CellCoord cc2(width,height-1);
        CellCoord cc3(width-1,height);
        CellCoord cc4(width,height);
        CellCoord cc5(0,0);
        CellCoord cc6(-5,0);
        CellCoord cc7(-2,-4);

        WHEN("Testing coordinates exceeding the width or height of the organ to which belongs the CellHandler")
        {
            THEN("they are outside")
            {
                CHECK(CH.isOut(cc2));
				CHECK(CH.isOut(cc3));
				CHECK(CH.isOut(cc4));
            }
        }
        WHEN("Testing (width/2,height/2) coordinate")
        {
            THEN("it is inside")
            {
                CHECK_FALSE(CH.isOut(cc1));
            }
        }

		 WHEN("Testing (0,0) coordinate")
        {
            THEN("it is inside")
            {
                CHECK_FALSE(CH.isOut(cc5));
            }
        }
        WHEN("Testing negative coordinates")
        {
            THEN("they are outside")
            {
                CHECK(CH.isOut(cc6));
				CHECK(CH.isOut(cc7));
            }
        }

		delete emptyOrgan;
    }
}
