#include <Substance.hpp>
#include <Utility/Constants.hpp>
#include <Utility/Utility.hpp>
#include <Application.hpp>

#include <iostream>
#include <algorithm>

Substance::Substance()
: cTOT(0), fVGEF(0), fGLU(0), fBMP(0)
{}

Substance::Substance(double fVGEF, double fGLU, double fBMP)
: 	cTOT(fVGEF + fGLU + fBMP),
	fVGEF((cTOT)? fGLU/cTOT : 0),
	fGLU((cTOT)? fGLU/cTOT : 0),
	fBMP((cTOT)? fBMP/cTOT : 0),
	SUBSTANCE_max(getAppConfig().substance_max_value)
{
	normalise();	
}

void Substance::normalise()
{
	if(isNull()) 
		cTOT = fVGEF = fGLU = fBMP = 0.0;
	if(cTOT * fVGEF > SUBSTANCE_max)
		fVGEF = SUBSTANCE_max /(cTOT-(cTOT * fVGEF - SUBSTANCE_max));
	if(cTOT * fGLU > SUBSTANCE_max)
		fGLU = SUBSTANCE_max /(cTOT-(cTOT * fGLU - SUBSTANCE_max));
	if(cTOT * fBMP > SUBSTANCE_max)
		fBMP = SUBSTANCE_max /(cTOT-(cTOT * fBMP - SUBSTANCE_max));
}

bool Substance::isNull()
{
	return((isEqual(fVGEF * cTOT, 0, SUBSTANCE_PRECISION))	
		and(isEqual(fGLU * cTOT, 0, SUBSTANCE_PRECISION))
		and(isEqual(fBMP * cTOT, 0, SUBSTANCE_PRECISION)));
}

bool Substance::operator ==(Substance const& sub) const
{
	return((isEqual(fVGEF*cTOT, sub[fVGEF], SUBSTANCE_PRECISION)) 
		and(isEqual(fGLU*cTOT, sub[fGLU], SUBSTANCE_PRECISION))
		and(isEqual(fBMP*cTOT, sub[fBMP], SUBSTANCE_PRECISION)));
}

bool operator !=(Substance const& sub1, Substance const& sub2 ) const
{
	return not(sub1==sub2);
}

double Substance::operator[](const SubstanceId index) const
{
	switch(index)
	{
		case VGEF:
			return(fVGEF * cTOT);
		case GLUCOSE:
			return(fGLU * cTOT);
		case BROMOPYRUVATE:
			return(fBMP * cTOT);
		default:
			std::cerr << "Wrong index" << std::endl;
			throw;
	} 
}

ostream& operator <<(ostream& sortie, Substance const& sub)
{
	sortie	<<"[VGEF] : "<<sub[2]
			<<"\n[GLUCOSE] : "<<sub[0]
			<<"\n[BROMOPYRUVATE] : "<<sub[1]
			<<std::endl;
return sortie;
}

Substance& Substance::operator +=(Substance const& sub)
{
	double newqVGEF=min((fVGEF*cTOT+sub[VGEF]),0);
	double newqGLU=min((fGLU*cTOT+sub[GLUCOSE]),0);
	double newqBMP=min((fBMP*cTOT+sub[BROMOPYRUVATE]),0);
	cTOT=(fVGEF + fGLU + fBMP);
	fVGEF=((cTOT)? fGLU/cTOT : 0),
	fGLU=((cTOT)? fGLU/cTOT : 0),
	fBMP=((cTOT)? fBMP/cTOT : 0)
	normalise();
	return *this;
}

Substance& Substance::operator -=(Substance const& sub)
{
	double newqVGEF=max((fVGEF*cTOT-sub[VGEF]),SUBSTANCE_max);
	double newqGLU=max((fGLU*cTOT-sub[GLUCOSE]),SUBSTANCE_max);
	double newqBMP=max((fBMP*cTOT-sub[BROMOPYRUVATE]),SUBSTANCE_max);
	cTOT=(fVGEF + fGLU + fBMP);
	fVGEF=((cTOT)? fGLU/cTOT : 0),
	fGLU=((cTOT)? fGLU/cTOT : 0),
	fBMP=((cTOT)? fBMP/cTOT : 0)
	normalise();
	return *this;
}


Substance& Substance::operator *=(double scalaire)
{
	cTOT*=scalaire;
	return *this;
	
}

Substance operator *(Substance const sub, double scalaire)
{
	return sub*=scalaire;
}

void update(SubstanceId subId, double c)
{
}
