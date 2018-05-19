#ifndef CELLLIVER_HPP
#define CELLLIVER_HPP

#include "CellOrgan.hpp"

class CellLiver: public CellOrgan
{
	public:
		CellLiver(CellHandler*,double atp = 100);

		virtual bool update(sf::Time) override;
	private:
		double atp;
};

#endif // CELLLIVER_HPP
