#ifndef I_SUBSTANCE_HPP
#define I_SUBSTANCE_HPP

#include <Types.hpp>
#include <Utility/Constants.hpp>
#include <Utility/Utility.hpp>

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
	double operator[](SubstanceId index) const;
	Substance& operator +=(Substance const&);
	Substance& operator -=(Substance const&);
	Substance& operator *=(double);
	

private:
	void normalise();
	
	double cMAX;

	double cVGEF;
	double cGLU;
	double cBMP;
};

Substance operator*(Substance,double);
bool operator!=(Substance const&,Substance const&);
std::ostream& operator<<(std::ostream&, Substance const&);

#endif //I_SUBSTANCE_HPP
