#ifndef CELLLIVER_HPP
#define CELLLIVER_HPP

#include "CellOrgan.hpp"

class CellLiver: public CellOrgan
{
	public:
		CellLiver(CellHandler*,double atp = 100);

		virtual bool update(sf::Time) override;
		
		virtual double getFractUptake() const;
		void uptake(SubstanceId id, double fract);
		virtual double getKrebsKm() const;
		virtual double getKrebsVmax() const;
		virtual void ATPSynthesis(sf::Time dt) const;
		
	private:
		double atp;
};

#endif // CELLLIVER_HPP
