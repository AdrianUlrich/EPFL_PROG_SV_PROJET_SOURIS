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
		virtual double getGlycoKm() const override;
		virtual double getGlycoVmax() const override;
		virtual double getFractGlu() const override;
		//virtual void ATPSynthesis(sf::Time dt) override;
		virtual void Krebs(sf::Time) override;
		virtual void divide() override;

	private:
};

#endif // CELLLIVERCANCER_HPP
