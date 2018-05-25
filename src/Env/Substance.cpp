#include "Substance.hpp"
#include <Utility/Constants.hpp>
#include <Utility/Utility.hpp>
#include <Application.hpp>
#include <Types.hpp>

#include <iostream>
#include <algorithm>
#include <exception>
#include <cmath>

const double Substance::cMAX = getAppConfig().substance_max_value;

Substance::Substance()
  : cVGEF(0)
  , cGLU(0)
  , cBMP(0)
{}

Substance::Substance(double cVGEF, double cGLU, double cBMP)
  :	cVGEF(cVGEF)
  ,	cGLU(cGLU)
  ,	cBMP(cBMP)
{
	normalise();
}

void Substance::normalise()
{
	if (isNull()) {cVGEF = cGLU = cBMP = 0.0; return;}
	if (cVGEF > cMAX)	cVGEF = cMAX;
	if (cGLU > cMAX)	cGLU = cMAX;
	if (cBMP > cMAX)	cBMP = cMAX;
	if (cVGEF < SUBSTANCE_PRECISION)	cVGEF = 0;
	if (cGLU < SUBSTANCE_PRECISION)		cGLU = 0;
	if (cBMP < SUBSTANCE_PRECISION)		cBMP = 0;

	/*
	cVGEF= min(cMAX,max(0,cVGEF));
	cGLU = min(cMAX,max(0,cGLU));
	cBMP = min(cMAX,min(0,cBMP));
	*/
}

bool Substance::isNull(double precision)
{
	return ((isEqual(cVGEF,0, precision))
		and (isEqual(cGLU, 0, precision))
		and (isEqual(cBMP, 0, precision)));
}

double Substance::getFractVGEF() const
{
	if (cVGEF < SUBSTANCE_PRECISION) return 0;
	return cVGEF/getTotalConcentration();
}
double Substance::getFractGlucose() const
{
	if (cGLU < SUBSTANCE_PRECISION) return 0;
	return cGLU/getTotalConcentration();
}
double Substance::getFractInhibitor() const
{
	if (cBMP < SUBSTANCE_PRECISION) return 0;
	return cBMP/getTotalConcentration();
}
double Substance::getTotalConcentration() const
{
	return (cVGEF + cGLU + cBMP);
}

bool Substance::operator ==(Substance const& sub) const
{
	return ((isEqual(cVGEF,sub[VGEF], 			SUBSTANCE_PRECISION))
		and (isEqual(cGLU, sub[GLUCOSE], 		SUBSTANCE_PRECISION))
		and (isEqual(cBMP, sub[BROMOPYRUVATE], 	SUBSTANCE_PRECISION)));
}

bool operator !=(Substance const& sub1, Substance const& sub2 )
{
	return not (sub1==sub2);
}

double const& Substance::operator[](SubstanceId index) const
{
	switch (index)
	{
		case VGEF:
			return cVGEF;

		case GLUCOSE:
			return cGLU;

		case BROMOPYRUVATE:
			return cBMP;

		default:
			throw std::invalid_argument("Valid arguments are [0,1,2]");
	}
}

std::ostream& operator<<(std::ostream& sortie, Substance const& sub)
{
	sortie	<<"[VGEF] : "			<<sub[VGEF]
			<<"\n[GLUCOSE] : "		<<sub[GLUCOSE]
			<<"\n[BROMOPYRUVATE] : "<<sub[BROMOPYRUVATE]
			<<std::endl;
return sortie;
}

Substance& Substance::operator+=(Substance const& sub)
{
	normalise();

	cVGEF+=sub[VGEF];
	cGLU +=sub[GLUCOSE];
	cBMP +=sub[BROMOPYRUVATE];

	normalise();
	return *this;
}

Substance& Substance::operator-=(Substance const& sub)
{
	normalise();

	cVGEF-=sub[VGEF];
	cGLU -=sub[GLUCOSE];
	cBMP -=sub[BROMOPYRUVATE];

	normalise();
	return *this;
}


Substance& Substance::operator*=(double scalaire)
{
	normalise();

	cVGEF*= scalaire;
	cGLU *= scalaire;
	cBMP *= scalaire;
	normalise();

	return *this;
}

Substance& operator*(Substance sub, double scalaire)
{
	return sub *= scalaire;
}

void Substance::update(SubstanceId subId, double scalaire)
{
	if (std::abs(scalaire)<EPSILON)
		cVGEF = cGLU = cBMP = 0;
	switch (subId)
	{
		case 2: // VGEF
			cVGEF*= scalaire;
			break;

		case 0: // GLUCOSE
			cGLU *= scalaire;
			break;

		case 1: // BROMOPYRUVATE
			cBMP *= scalaire;
			break;

		default:
			throw std::invalid_argument("Valid arguments are [0,1,2]");
	}
	normalise();
}

void Substance::uptakeOnGradient(double c, Substance& receiver, SubstanceId id)
{
	switch (id)
	{
		case SubstanceId::VGEF :
		{
			double oho(c*cVGEF);
			if (std::abs(oho)<SUBSTANCE_PRECISION) return;
			cVGEF-=oho;
			receiver.cVGEF+=oho;
		}
		break;

		case SubstanceId::GLUCOSE :
		{
			double oho(c*cGLU);
			if (std::abs(oho)<SUBSTANCE_PRECISION) return;
			cGLU-=oho;
			receiver.cGLU+=oho;
		}
		break;

		case SubstanceId::BROMOPYRUVATE :
		{
			double oho(c*cBMP);
			if (std::abs(oho)<SUBSTANCE_PRECISION) return;
			cBMP-=oho;
			receiver.cBMP+=oho;
		}
		break;

		default:
			throw std::invalid_argument("Valid arguments are [0,1,2]");
	}
	normalise();



	/*
	double grad((this->operator[](id))*c);
	if (grad<SUBSTANCE_PRECISION) return;
	receiver.update(id,1+grad/receiver[id]);
	switch (id)
	{
		case 2: // VGEF
			cVGEF-=grad;
			break;

		case 0: // GLUCOSE
			cGLU -= grad;
			break;

		case 1: // BROMOPYRUVATE
			cBMP -= grad;
			break;

		default:
			throw std::invalid_argument("Valid arguments are [0,1,2]");
	}
	*/
}
