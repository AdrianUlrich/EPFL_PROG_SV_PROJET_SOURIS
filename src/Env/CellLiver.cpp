#include "CellLiver.hpp"
#include "CellHandler.hpp"
#include "Substance.hpp"

#include <Random/Random.hpp>
#include <Application.hpp>
#include <Types.hpp>
#include <Utility/Utility.hpp>

#include <cmath>


CellLiver::CellLiver(CellHandler* h, double atp)
	:	CellOrgan(h)
	,	atp(atp)
{}

bool CellLiver::update(sf::Time dt)
{
	handler->liverTakeFromEcm(SubstanceId::GLUCOSE,getFractUptake()*dt.asSeconds());
	handler->liverTakeFromEcm(SubstanceId::BROMOPYRUVATE,getFractUptake()*dt.asSeconds());
	ATPSynthesis(dt);
	atp*=1-exp(-getAppConfig().liver_decay_atp*dt.asSeconds());
	atp-=uniform(getAppConfig().base_atp_usage , getAppConfig().base_atp_usage+getAppConfig().range_atp_usage);
	return atp<=0;//or CellOrgan::update(dt);
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
	atp+=((S*getKrebsVmax())/(S+getKrebsKm()))*dt.asSeconds();
}

void CellLiver::glycolysis(sf::Time dt)
{
	double P(getFractGlu());
	Quantity S(P*(*substance)[SubstanceId::GLUCOSE]);
	substance->update(SubstanceId::GLUCOSE,1-P);
	Quantity I((*substance)[SubstanceId::BROMOPYRUVATE]);
	//substance->update(SubstanceId::BROMOPYRUVATE,1-P);
	atp+=(S*getKrebsVmax())/(S*getKrebsKm()*(1+I*1/0.6))*dt.asSeconds();
}

double CellLiver::getFractUptake() const
{return getAppConfig().liver_fract_uptake;}

double CellLiver::getKrebsKm() const
{return getAppConfig().liver_km_glycolysis;}

double CellLiver::getKrebsVmax() const
{return getAppConfig().liver_km_max_glycolysis;}

double CellLiver::getFractGlu() const
{return getAppConfig().liver_glucose_usage;}

