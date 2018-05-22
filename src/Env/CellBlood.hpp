#ifndef CELLBLOOD_HPP
#define CELLBLOOD_HPP

#include "CellOrgan.hpp"
#include <Types.hpp>

class CellBlood: public CellOrgan
{
	public:
		CellBlood(CellHandler*,TypeBloodCell t=ARTERY);
		
		virtual bool update(sf::Time) override;
		
		TypeBloodCell getType() const;
	private:
		TypeBloodCell type;
};

#endif // CELLBLOOD_HPP
