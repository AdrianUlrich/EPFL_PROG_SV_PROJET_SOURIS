#ifndef CELLLIVER_HPP
#define CELLLIVER_HPP

#include "CellOrgan.hpp"
#include <Utility/Utility.hpp>


class CellLiver: public CellOrgan
{
	public:
		CellLiver(CellHandler*,double atp = 100);

		virtual bool update(sf::Time) override;
		void printAtp() const;
	
	protected:
		virtual double getFractUptake() const;
		virtual double getKrebsKm() const;
		virtual double getKrebsVmax() const;
		virtual double getGlycoKm() const;
		virtual double getGlycoVmax() const;
		virtual double getFractGlu() const;
		virtual void ATPSynthesis(sf::Time dt);
		virtual void Krebs(sf::Time dt);
		void glycolysis(sf::Time dt);	

	private:
		double atp;
};

#endif // CELLLIVER_HPP
