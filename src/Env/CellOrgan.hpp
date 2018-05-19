#ifndef CELLORGAN_HPP
#define CELLORGAN_HPP

#include "Substance.hpp"
#include <Utility/Utility.hpp>
class CellHandler;

class CellOrgan ///ABSTRACT
{
	public:
		CellOrgan(CellHandler*);
		
		virtual ~CellOrgan() = 0;
		
		void updateSubstance(Substance const&);
		Quantity getQuantity(SubstanceId) const;
		void uptakeOnGradient(double,CellOrgan*,SubstanceId);
		
		virtual bool update(sf::Time);
			
	protected:
		Substance* substance;
		
		CellHandler* handler;
};

#endif // CELLORGAN_HPP 
