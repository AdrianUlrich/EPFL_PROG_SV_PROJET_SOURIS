#include "CellLiver.hpp"
#include "CellHandler.hpp"
#include "Substance.hpp"

#include <Random/Random.hpp>
#include <Application.hpp>
#include <Types.hpp>
#include <Utility/Utility.hpp>

#include <cmath>
#include <iostream>

CellLiver::CellLiver(CellHandler* h, double atp)
	:	CellOrgan(h)
	,	atp(atp)
{}

bool CellLiver::update(sf::Time dt)
{
	handler->liverTakeFromEcm(SubstanceId::GLUCOSE,getFractUptake());//*dt.asSeconds());
	handler->liverTakeFromEcm(SubstanceId::BROMOPYRUVATE,getFractUptake());//*dt.asSeconds());
	ATPSynthesis(dt);
	atp*=1-exp(-getAppConfig().liver_decay_atp*dt.asSeconds());
	atp-=uniform(getAppConfig().base_atp_usage , getAppConfig().base_atp_usage+getAppConfig().range_atp_usage);
	if (atp>getDivisionEnergy()) divide();
	return atp<=0 or atp!=atp; ///< Checking for -nan value
}
void CellLiver::ATPSynthesis(sf::Time dt)
{
	glycolysis(dt);
	Krebs(dt);
}

void CellLiver::Krebs(sf::Time dt)
{
	double P(.8);
	Quantity S(P*(*substance)[SubstanceId::GLUCOSE]);
	substance->update(SubstanceId::GLUCOSE,1-P);
	atp+=1.5*((S*getKrebsVmax())/(S+getKrebsKm()))*dt.asSeconds();
}

void CellLiver::glycolysis(sf::Time dt)
{
	double P(getFractGlu()*dt.asSeconds());
	Quantity S(P*(*substance)[SubstanceId::GLUCOSE]);
	substance->update(SubstanceId::GLUCOSE,1-P);
	Quantity I((*substance)[SubstanceId::BROMOPYRUVATE]);
	substance->update(SubstanceId::BROMOPYRUVATE,0.001*dt.asSeconds());
	atp+=0.5*(S*getGlycoVmax())/(S*getGlycoKm()*(1+I*1.666))*dt.asSeconds();
}

double CellLiver::getFractUptake() const
{return getAppConfig().liver_fract_uptake;}

double CellLiver::getKrebsKm() const
{return getAppConfig().liver_km_krebs;}

double CellLiver::getKrebsVmax() const
{return getAppConfig().liver_km_max_krebs;}

double CellLiver::getGlycoKm() const
{return getAppConfig().liver_km_glycolysis;}

double CellLiver::getGlycoVmax() const
{return getAppConfig().liver_km_max_glycolysis;}

double CellLiver::getFractGlu() const
{return getAppConfig().liver_glucose_usage;}

double CellLiver::getDivisionEnergy() const
{return getAppConfig().liver_division_energy;}

void CellLiver::printAtp() const
{
	using namespace std;
	cout<<atp<<endl;
}

void CellLiver::divide(Organ::Kind k)
{
  CellCoord offset(uniform(-1,1),uniform(-1,1));
  if (handler->updateCellHandlerAt(offset,k))
    atp-=getAppConfig().liver_division_cost;
}
