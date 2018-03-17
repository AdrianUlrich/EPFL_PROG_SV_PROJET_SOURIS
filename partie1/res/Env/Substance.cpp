#include <Substance.hpp>
#include <Utility/Constants.hpp>
#include <Utility/Utility.hpp>
#include <Application.hpp>
#include <Types.hpp>

#include <iostream>
#include <algorithm>
#include <exception>

Substance::Substance()
: cVGEF(0), cGLU(0), cBMP(0)
{}

Substance::Substance(double cVGEF, double cGLU, double cBMP)
:	cVGEF(cVGEF),
	cGLU(cGLU),
	cBMP(cBMP),
{
	normalise();	
}

void Substance::normalise()
{
	if (isNull()) cVGEF = cGLU = cBMP = 0.0;
	/* potentially faster
	if (cVGEF > cMAX)	cVGEF = cMAX;
	if (cGLU > cMAX)	cGLU = cMAX;
	if (cBMP > cMAX)	cBMP = cMAX;
	if (cVGEF < 0)		cVGEF = 0;
	if (cGLU < 0)		cGLU = 0;
	if (cBMP < 0)		cBMP = 0;
	*/
	cVGEF= min(cMAX,max(0,cVGEF));
	cGLU = min(cMAX,max(0,cGLU));
	cBMP = min(cMAX,min(0,cBMP));

}

bool Substance::isNull(double precision)
{
	return ((isEqual(cVGEF,0, precision))	
		and (isEqual(cGLU, 0, precision))
		and (isEqual(cBMP, 0, precision)));
}

double getFractVGEF() const;
{
	if (cVGEF==0) return 0;
	return cVGEF/getTotalConcentration();
}
double getFractGlucose() const;
{
	if (cGLU==0) return 0;
	return cGLU/getTotalConcentration();
}
double getFractInhibitor() const
{
	if (cBMP==0) return 0;
	return cBMP/getTotalConcentration();
}
double getTotalConcentration() const
{
	return cVGEF + cGLU + cBMP;
}

bool Substance::operator ==(Substance const& sub) const
{
	return ((isEqual(cVGEF,sub[VGEF], 			SUBSTANCE_PRECISION)) 
		and (isEqual(cGLU, sub[GLUCOSE], 		SUBSTANCE_PRECISION))
		and (isEqual(cBMP, sub[BROMOPYRUVATE], 	SUBSTANCE_PRECISION)));
}

bool operator !=(Substance const& sub1, Substance const& sub2 ) const
{
	return not (sub1==sub2);
}

double Substance::operator[](SubstanceId index) const
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
			throw std::invalid_argument;
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

Substance operator*(Substance sub, double scalaire)
{
	return sub *= scalaire;
}

void update(SubstanceId subId, double scalaire)
{
	switch (subID)
	{
		case VGEF:
			cVGEF*= scalaire;
			break;
			
		case GLUCOSE:
			cGLU *= scalaire;
			break;
			
		case BROMOPYRUVATE:
			cBMP *= scalaire;
			break;
			
		default:
			throw std::invalid_argument;
	}
	normalise();
}

void uptakeOnGradient(double fraction, Substance& receiver, SubstanceId id)
{
	double grad((this->operator[](id))*(1-fraction));
	if (grad<SUBSTANCE_PRECISION) return;
	update(id,1-fraction);
	reciever.update(id,(grad+reciever[id])/reciever[id]);
}





