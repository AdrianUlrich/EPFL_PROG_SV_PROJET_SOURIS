#ifndef CELLBLOOD_HPP
#define CELLBLOOD_HPP

#include "CellOrgan.hpp"
#include <Types.hpp>

class CellBlood: public CellOrgan
{
	public:
		CellBlood(CellHandler*,TypeBloodCell t=ARTERY);
		
		virtual bool update(sf::Time) override;
	private:
		TypeBloodCell type;
};

#endif // CELLBLOOD_HPP
