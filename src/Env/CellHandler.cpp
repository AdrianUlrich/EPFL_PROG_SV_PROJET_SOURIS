#include "Organ.hpp"
#include "CellHandler.hpp"
#include "CellECM.hpp"
#include "CellBlood.hpp"
#include "CellLiver.hpp"

CellHandler::CellHandler(CellCoord pos, Organ* o)
	:	pos(pos)
	,	organ(o)
	,	ecm(new CellECM(this))
	,	liver(nullptr)
	,	blood(nullptr)
{
	
}

CellHandler::~CellHandler()
{
	delete ecm;
	delete liver;
	delete blood;
}

bool CellHandler::hasECM() const
{return ecm!=nullptr;}
bool CellHandler::hasLiver() const
{return liver!=nullptr;}
bool CellHandler::hasBlood() const
{return blood!=nullptr;}

void CellHandler::setECM()
{ecm=new CellECM(this);}
void CellHandler::setLiver()
{liver=new CellLiver(this);}
void CellHandler::setBlood(TypeBloodCell t)
{blood=new CellBlood(this,t);}

void CellHandler::updateSubstance(Substance const& s)
{ecm->updateSubstance(s);}

Quantity CellHandler::getECMQuantity(SubstanceId id) const
{return hasECM()?ecm->getQuantity(id):0;}
Quantity CellHandler::getLiverQuantity(SubstanceId id) const
{return hasLiver()?liver->getQuantity(id):0;}
Quantity CellHandler::getBloodQuantity(SubstanceId id) const
{return hasBlood()?blood->getQuantity(id):0;}

void CellHandler::liverTakeFromEcm(SubstanceId id, double fract)
{ecm->uptakeOnGradient(fract,liver,id);}
void CellHandler::bloodTakeFromEcm(SubstanceId id, double fract)
{ecm->uptakeOnGradient(fract,blood,id);}

bool CellHandler::isOut(CellCoord const& c)
{return organ->isOut(c);}
