#ifndef CELLHANDLER_HPP
#define CELLHANDLER_HPP

#include <Utility/Utility.hpp>
#include "Types.hpp"
#include "Substance.hpp"
#include "Organ.hpp"
class CellECM;
class CellBlood;
class CellLiver;


class CellHandler final
{
	public:
		CellHandler(CellCoord,Organ*);
		
		~CellHandler();
			
			
		CellCoord getPos() const;
		Organ* getOrgan() const;
			
		/** 4.2 gets sets interacts and checks for CellXXXs */
		bool hasECM() const;
		bool hasLiver() const;
		bool hasBlood() const;
		bool hasCancer() const;
		void setECM();
		void setLiver();
		void setBlood(TypeBloodCell);
		void setCANCER();
		void updateSubstance(Substance const&);
		Quantity getECMQuantity(SubstanceId) const;
		Quantity getLiverQuantity(SubstanceId) const;
		Quantity getBloodQuantity(SubstanceId) const;
		void liverTakeFromEcm(SubstanceId,double fract);
		void bloodTakeFromEcm(SubstanceId,double fract);
		
		/** isOut method from organ pointer */		
		bool isOut(CellCoord const&);
		
		void update(sf::Time);
		
			
	private:
		CellCoord pos;
		Organ* organ;
		
		CellECM* ecm;
		CellLiver* liver;
		CellBlood* blood;	
		
		bool cancer;	
};

#endif // CELLHANDLER_HPP
