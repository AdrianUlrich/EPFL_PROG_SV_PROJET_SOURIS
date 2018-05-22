#ifndef CELLLIVERCANCER_HPP
#define CELLLIVERCANCER_HPP

#include "CellLiver.hpp"

class CellLiverCancer: public CellLiver
{
	public:
		using CellLiver::CellLiver;
		
		virtual double getFractUptake() const override;
		//virtual bool update(sf::Time) override;
		
	protected:
		virtual double getKrebsKm() const override;
		virtual double getKrebsVmax() const override;
		virtual double getFractGlu() const override;
		//virtual void ATPSynthesis(sf::Time dt) override;
		virtual void Krebs(sf::Time) override;

	private:
};

#endif // CELLLIVERCANCER_HPP
