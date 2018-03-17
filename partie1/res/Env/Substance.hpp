#ifndef I_SUBSTANCE_HPP
#define I_SUBSTANCE_HPP

#include <Application.hpp>
#include <Utility/Constants.hpp>

class Substance 
{	
public:
	Substance(double, double, double);
	Substance();
	Substance(const Substance& sub) = default;
	Substance& operator=(Substance const&) = default;
	~Substance() = default;
	
	bool isNull(double precision = SUBSTANCE_PRECISION);
	void update(SubstanceId,double);
	void uptakeOnGradient(double,Substance&,SubstanceId);

	double getFractVGEF() const;
	double getFractGlucose() const;
	double getFractInhibitor() const;
	double getTotalConcentration() const;

	bool operator==(Substance const&) const;
	double operator[](const SubstanceId index) const;
	Substance& Substance::operator +=(Substance const&);
	Substance& Substance::operator -=(Substance const&);
	Substance& Substance::operator *=(double);
private:
	void normalise();

	const static double cMAX = getAppConfig().substance_max_value;

	double cVGEF;
	double cGLU;
	double cBMP;
}

Substance Substance::operator *(Substance,Substance const&);
bool operator !=(Substance const&,Substance const&) const;

#endif //I_SUBSTANCE_HPP
