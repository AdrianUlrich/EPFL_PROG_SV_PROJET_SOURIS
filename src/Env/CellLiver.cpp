#include "CellLiver.hpp"

#include <Random/Random.hpp>
#include <Application.hpp>
#include <Types.hpp>
#include <Utility/utility>

#include <cmath>


CellLiver::CellLiver(CellHandler* h, double atp)
	:	CellOrgan(h)
	,	atp(atp)
{}

bool CellLiver::update(sf::Time dt)
{
	uptake(SubstanceId::GLUCOSE,getFractUptake());
	ATPSynthesis(dt);
	atp*=1-exp(-getAppConfig().liver_decay_atp*dt.asSeconds());
	atp-=uniform(getAppConfig().base_atp_usage , getAppConfig().base_atp_usage+getAppConfig().range_atp_usage);
	uptake(SubstanceId::GLUCOSE,getFractUptake());
	return atp<=0;//or CellOrgan::update(dt);
}

double CellLiver::getFractUptake() const
{return getAppConfig().liver_fract_uptake;}

void CellLiver::uptake(SubstanceId id, double fract)
{
	handler->liverTakeFromEcm(id,fract);
}

double CellLiver::getKrebsKm() const
{return getAppConfig().liver_km_glycolysis;}

double CellLiver::getKrebsVmax() const
{return getAppConfig().liver_km_max_glycolysis;}

void CellLiver::ATPSynthesis(sf::Time dt) const
{
	//Quantity s = (*substance)[SubstanceId::GLUCOSE] * .8;
	//double t = dt.asSeconds();
	Krebs(s,t);
	glycolysis(s,t); 
}
