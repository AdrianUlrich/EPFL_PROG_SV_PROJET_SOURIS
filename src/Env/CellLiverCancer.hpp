#ifndef CELLLIVERCANCER_HPP
#define CELLLIVERCANCER_HPP

#include "CellLiver.hpp"

class CellLiverCancer: public CellLiver
{
	public:
		using CellLiver::CellLiver;
		
		virtual double getFractUptake() const override;
		virtual bool update(sf::Time) override;
		virtual double getKrebsKm() const override;
		virtual double getKrebsVmax() const override;
		virtual void ATPSynthesis(sf::Time dt) const override;

	private:
		/* add your private declarations */
};

#endif /* CELLLIVERCANCER_HPP */ 
