/*
 * projet 2018
 * Antoine Madrona
 */

#include <Tests/UnitTests/CheckUtility.hpp>
#include <Random/Random.hpp>
#include <Application.hpp>
#include <Env/Substance.hpp>

#include <catch.hpp>

#include <iostream>

constexpr size_t REPEAT(10);

SCENARIO("Constructing Substance", "[Substance]")
{
    WHEN("Default constructor is used")
    {
        Substance s;

        THEN("All concentrations are equal to 0.")
        {
            CHECK(s.getFractVGEF() == 0.);
            CHECK(s.getFractGlucose() == 0.);
            CHECK(s.getFractInhibitor() == 0.);
            CHECK(s.getTotalConcentration() == 0.);
			CHECK(s.isNull());
        }

        AND_WHEN("A second Substance is default constructed")
        {
            Substance t;

            THEN("They are equal")
            {
                CHECK(s == t);
            }
        }
    }
	
	WHEN("Explicit constructor is used with too small values (<= SUBSTANCE_PRECISION)")
	{
    	Substance s1 (SUBSTANCE_PRECISION/10, 300., 400.);
    	Substance s2 (200., SUBSTANCE_PRECISION/10, 400);
    	Substance s3 (200., 400., SUBSTANCE_PRECISION/10);
		Substance s4 (SUBSTANCE_PRECISION/10, SUBSTANCE_PRECISION/10, SUBSTANCE_PRECISION/10);

	THEN("the too  small values  are ignored (for total concentration and composants fraction)")
    	{
			std::cout << s1 << std::endl;
    	CHECK(s1.getTotalConcentration() == 700.);
    	CHECK(s2.getTotalConcentration() == 600.);
    	CHECK(s3.getTotalConcentration() == 600.);
		CHECK(s1.getFractVGEF() == 0. );
   		CHECK(s2.getFractGlucose() == 0.);
   		CHECK(s3.getFractInhibitor() == 0.);
		CHECK(s4.isNull());
		}

	}
	
		
		
    WHEN("Explicit constructor is used with anormal values (<= 0)")
    {
    	Substance s1 (-200, -300, -400);
    	Substance s2 (0., 0., 0.);
    	Substance s3 (0., 0., -100.);
    	Substance s4 (200., 200., -100.);

    	THEN("Negatives values are ignored (for total concentration and composants fraction)")
    	{
    	CHECK(s1.getTotalConcentration() == 0.);
    	CHECK(s2.getTotalConcentration() == 0.);
    	CHECK(s3.getTotalConcentration() == 0.);
   		CHECK(s4.getTotalConcentration() == 400.);

   		CHECK(s4.getFractVGEF() == 0.5);
   		CHECK(s1.getFractGlucose() == 0.);
   		CHECK(s3.getFractInhibitor() == 0.);
    	}
    }
	

	WHEN("Explicit constructor is used with anormal values (> getAppConfig().substance_max_value)")
    {
		auto max_value(getAppConfig().substance_max_value);
    	Substance s1 (max_value + 200., 300., 400.);
    	Substance s2 (200., max_value+300., 400.);
    	Substance s3 (200., 300., max_value+500.);
    	Substance s4 (max_value+100, max_value+200., max_value+300.);

    	THEN("Exceedingly large values are ignored (for total concentration and composants fraction)")
    	{
			auto max_value_s1(max_value + 700.);
			auto max_value_s2(max_value + 600.);
			auto max_value_s3(max_value + 500.);
			CHECK(s1.getTotalConcentration() == max_value_s1);
			CHECK(s2.getTotalConcentration() == max_value_s2);
			CHECK(s3.getTotalConcentration() == max_value_s3);
			CHECK(s4.getTotalConcentration() == max_value*3);

   		CHECK_APPROX_EQUAL(s1.getFractVGEF(), max_value/max_value_s1);
   		CHECK_APPROX_EQUAL(s2.getFractGlucose(), max_value/max_value_s2);
   		CHECK_APPROX_EQUAL(s3.getFractInhibitor(), max_value/max_value_s3);
    	}
    }

	
    WHEN("Explicit constructor is used with normal values")
    {
    	Substance s1(300., 200., 100.);
    	Substance s2(45., 675., 43.);

    	THEN("Total concentration is equal to the sum of concentrations")
    	{
    		CHECK(s1.getTotalConcentration() == 600.);
    		CHECK(s2.getTotalConcentration() == 763.);
    	}

    	THEN("The fraction of each composants is well computed")
    	{
    		CHECK_APPROX_EQUAL(s1.getFractVGEF(), 1.0/2);
    		CHECK_APPROX_EQUAL(s1.getFractGlucose(), 1.0/3);
    		CHECK_APPROX_EQUAL(s1.getFractInhibitor(), 1.0/6);

    		CHECK_APPROX_EQUAL(s2.getFractGlucose(), 675.0/763);
    	}

    	GIVEN("A substance")
    	{
        	Substance s(111., 333., 666.);

        	WHEN("Copy constructor is used")
        	{
           		Substance t(s);

            	THEN("They are equal (using == and != operators)")
            	{
                	CHECK(s == t);
                	CHECK_FALSE(s != t);
            	}
        	}
    	}
    }
}
SCENARIO("Displaying substance", "operator << ")
{
	Substance s1(300., 200., 100.);
	Substance s2(45., 675., 43.);

	std::cout << s1 << std::endl;
	std::cout << s2 << std::endl;
}

SCENARIO("Assigning Substance", "[Substance]")
{
	GIVEN("A substance")
    {
        Substance s(3.14, 69., 2018.);

        WHEN("Copy assignment is used")
        {
            Substance t;
            s = t;

            THEN("They are equal")
            {
                CHECK(s == t);
            }
        }
    }
}

SCENARIO("Testing the operators", "[Substance]")
{
	
	
    GIVEN("Substance (250., 50., 500.)")
    {
        Substance s(250., 50., 500.);

        WHEN("Using operator *")
        {
            Substance temp (s*2);

        	THEN("All attributes are appropriately multiplied")
        	{
        		CHECK(temp == Substance(500., 100., 1000.));
        	}
        }


        WHEN("Using operator -=")
        {
            s -= Substance (50.2, 60., 500.);

            THEN("Attributes are modified appropriately (no negative value)")
            {
                CHECK(s == Substance (199.8, 0., 0.));
            }
        }

        WHEN("Using operator +=")
        {
            s += Substance(0, getAppConfig().substance_max_value, 250.);

            THEN("Attributes are modified appropriately (no value exceeding the maximum)")
            {
                CHECK(s == Substance(250., getAppConfig().substance_max_value, 750.));
            }
        }

		 WHEN("Using operator +=")
        {
            s += Substance(0, getAppConfig().substance_max_value+200., 250.);

            THEN("Attributes are modified appropriately (no value exceeding the maximum)")
            {
                CHECK(s == Substance(250, getAppConfig().substance_max_value, 750));
            }
        }

        WHEN("Using operator []")
        {
			
        	THEN("Corresponding composant is returned, a negative value is returned for unknown substances")
        	{
				
        		CHECK(s[VGEF] == 250.);
        		CHECK(s[GLUCOSE] == 50.);
        		CHECK(s[BROMOPYRUVATE] == 500.);
				// checking random default value
				
				for (size_t count(0); count < REPEAT; ++ count)
					CHECK_THROWS(s[(SubstanceId)uniform(4, 100)]);
        	}
    	}
	}

	GIVEN ("Three substances")
	{
		Substance s(111., 333., 666.);
		Substance t(s);
		Substance u(222., 444., 555.);

		THEN("s and t are equals")
		{
			CHECK(s == t);
			CHECK_FALSE (s != t);
		}

		THEN("s and u are not equals")
		{
			CHECK(s != u);
			CHECK_FALSE(s == u);
		}
	}

	 GIVEN("Substance (0.0, 0.0, 0.0)")
    {
		double small_value (+1E-09);
        Substance s( 0., 0., 0.);

        WHEN("Using operator *")
        {
            Substance temp (s*2.);

        	THEN("the substance remains unchanged")
        	{
        		CHECK(temp == Substance(0., 0., 0.));
        	}
        }

        WHEN("Using operator -=")
        {
            s -= Substance (small_value, small_value, small_value);

            THEN("")
            {
                CHECK(s == Substance (0., 0., 0.));
            }
        }

	}
	 
}

SCENARIO("Testing update method", "[Substance]")
{
	GIVEN("A substance")
	{
		Substance s(100., 200., 300.);

		WHEN("Updating VGEF by 0.7")
		{
			s.update(VGEF, 0.7);

			THEN("VGEF changes (and total concentration accordingly), GLU and BRO don't")
			{
				CHECK(s == Substance(70., 200., 300.));
				CHECK_APPROX_EQUAL (s[VGEF], 70);
			}
		}

		WHEN("Updating GLUCOSE by -3.1")
		{
            s.update(GLUCOSE, -3.1);

			THEN("GLU changes to 0, total concentration changes accordingly, VGEF and BRO don't")
			{
				CHECK(s == Substance(100., 0., 300.));
				CHECK_APPROX_EQUAL(s[GLUCOSE], 0.);
			}
		}

		WHEN("Updating Inhibitor by 0")
		{
            s.update(BROMOPYRUVATE, 0.);

			THEN("All attribut are equals to 0.")
			{
				CHECK(s == Substance(0.,0.,0.));
			}
		}
	}
}


SCENARIO("Testing uptakeOnGradient method", "[Substance]") {
	
	GIVEN("Substance 1: (50., 50., 50.) and Substance 2 with fractions lower than minimal precision "){
		Substance sub1( 50., 50., 50.);
		double small_value(SUBSTANCE_PRECISION /10.);
        Substance sub2( small_value, small_value, small_value);
		WHEN("Substance 1 receives half of Substance 2 GLUCOSE")
        {
            sub2.uptakeOnGradient(0.5, sub1, GLUCOSE);

            THEN("Substance 1 remains unchanged")
            {
                CHECK ( sub1 == Substance(50.,50.,50.));
			}

		}
	}
	
    GIVEN("Two substance")
    {
        Substance sub1(100., 200., 300.); //VGEF, GLU, INHIB
        Substance sub2(300., 200., 100.);

        WHEN("Sub2 receive half of Sub1 GLUCOSE")
        {
            sub1.uptakeOnGradient(0.5, sub2, GLUCOSE);

            THEN("GLUCOSE fraction of both substance is well updated")
            {
                CHECK_APPROX_EQUAL(sub1.getFractGlucose(), 100.0/500);
                CHECK_APPROX_EQUAL(sub2.getFractGlucose(), 300.0/700);
            }

            THEN("Other product fractions change according to the new total concentration")
            {
                CHECK_APPROX_EQUAL(sub1.getFractVGEF(), 100.0/500);
                CHECK_APPROX_EQUAL(sub1.getFractInhibitor(), 300.0/500);

                CHECK_APPROX_EQUAL(sub2.getFractVGEF(), 300.0/700);
                CHECK_APPROX_EQUAL(sub2.getFractInhibitor(), 100.0/700);
            }
        }

        WHEN("Sub2 receive all of Sub1 VGEF")
        {
            sub1.uptakeOnGradient(1.0, sub2, VGEF);

            THEN("VGEF fraction of both substances is well updated")
            {
                CHECK_APPROX_EQUAL(sub1.getFractVGEF(), 0);
                CHECK_APPROX_EQUAL(sub2.getFractVGEF(), 400.0/700);
            }

            THEN("Other product fractions change according to the new total concentration")
            {
                CHECK_APPROX_EQUAL(sub1.getFractGlucose(), 200.0/500);
                CHECK_APPROX_EQUAL(sub1.getFractInhibitor(), 300.0/500);

                CHECK_APPROX_EQUAL(sub2.getFractGlucose(), 200.0/700);
                CHECK_APPROX_EQUAL(sub2.getFractInhibitor(), 100.0/700);
            }
        }
    }
}
