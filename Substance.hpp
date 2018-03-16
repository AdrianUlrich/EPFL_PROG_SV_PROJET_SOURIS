#ifndef I_SUBSTANCE_HPP
#define I_SUBSTANCE_HPP




class Substance 
{
	
public:

	Substance(double, double, double);
	Substance();
	Substance(const Substance& sub) = default;
	~Substance() = default;
	
	bool isNull();

	double getFractfVGEF() const {return fVGEF;}
	double getFractfGLU() const {return fGLU;}
	double getFractVfBMP() const {return fBMP;}
	double getTotalConcentration() const {return cTOT;}

	
	Substance& operator =(Substance const&) = default;
	bool operator ==(Substance const&) const;
	double operator[](const SubstanceId index) const;
	Substance& Substance::operator +=(Substance const&);
	Substance& Substance::operator -=(Substance const&);
	Substance& Substance::operator *=(double);
	
	
private:
		double SUBSTANCE_max;

		void normalise(); 

		double cTOT;
		double fVGEF;
		double fGLU;
		double fBMP;
}

Substance Substance::operator *(Substance);
bool operator !=(Substance const&,Substance const&) const;

#endif //I_SUBSTANCE_HPP
