#include "Organ.hpp"
#include "CellHandler.hpp"
#include "CellECM.hpp"
#include "CellBlood.hpp"
#include "CellLiver.hpp"
#include "CellLiverCancer.hpp"
#include <Types.hpp>
#include <Utility/Utility.hpp>

#include <iostream>

CellHandler::CellHandler(CellCoord pos, Organ* o)
	:	pos(pos)
	,	organ(o)
	,	ecm(new CellECM(this))
	,	liver(nullptr)
	,	blood(nullptr)
	,	cancer(false)
{

}

CellHandler::~CellHandler()
{
	delete ecm;
	delete liver;
	delete blood;
}

CellCoord CellHandler::getPos() const
{return pos;}
Organ* CellHandler::gesdtOrgan() const
{return organ;}

bool CellHandler::hasECM() const
{return ecm!=nullptr;}
bool CellHandler::hasLiver() const
{return liver!=nullptr;}
bool CellHandler::hasBlood() const
{return blood!=nullptr;}
bool CellHandler::hasCancer() const
{return cancer;}

bool CellHandler::setECM()
{if(ecm==nullptr){ecm=new CellECM(this);return true;}return false;}
bool CellHandler::setLiver()
{if(liver==nullptr){liver=new CellLiver(this);return true;}return false;}
bool CellHandler::setBlood(TypeBloodCell t)
{if(blood==nullptr){blood=new CellBlood(this,t);return true;}return false;}
bool CellHandler::setCANCER()
{
	if (cancer) return false;
	cancer=true;
	CellLiverCancer* cancer(new CellLiverCancer(this));
	if (liver!=nullptr)
		cancer->updateSubstance({.0,liver->getQuantity(SubstanceId::GLUCOSE),.0});
	delete liver;
	liver=cancer;
	return true;
}

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

bool CellHandler::update(sf::Time dt)
{
	bool changed(false);
	/// update will return true if the CellOrgan died
	if (hasECM() and ecm->update(dt)) {delete ecm;ecm=nullptr;changed=true;}
	if (hasLiver() and liver->update(dt)) {delete liver;liver=nullptr;cancer=false;changed=true;}
	if (hasBlood() and blood->update(dt)) {delete blood;blood=nullptr;changed=true;}
	return changed;
}

void CellHandler::printAtp() const
{if (hasLiver()) liver->printAtp(); else std::cout<<"no liver cell here"<<std::endl;}

void CellHandler::updateCellHandlerAt(CellCoord const& c, Substance const& S)
{if (c==pos) updateSubstance(S); else organ->updateCellHandlerAt(c,S);}

bool CellHandler::updateCellHandlerAt(CellCoord const& c, Kind k)
{return c!=CellCoord{0,0} and organ->propagate(c+pos,S);}
