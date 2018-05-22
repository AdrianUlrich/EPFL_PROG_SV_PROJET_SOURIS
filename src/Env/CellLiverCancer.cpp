#include "CellLiverCancer.hpp"


CellLiverCancer::CellLiverCancer()
	:	CellLiver()
{}

double CellLiverCancer::getFractUptake() const
{return getAppConfig().cancer_fract_uptake;}

double CellLiverCancer::getKrebsKm() const
{return getAppConfig().cancer_km_glycolysis;}

double CellLiverCancer::getKrebsVmax() const
{return getAppConfig().cancer_km_max_glycolysis;}

void CellLiverCancer::ATPSynthesis(sf::Time dt) const
{CellLiver::ATPSynthesis(dt);}

bool update(sf::Time dt)
{return CellLiver::update(dt);}
