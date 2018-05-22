#include "CellLiverCancer.hpp"
#include <Application.hpp>

double CellLiverCancer::getFractUptake() const
{return getAppConfig().cancer_fract_uptake;}

double CellLiverCancer::getKrebsKm() const
{return getAppConfig().cancer_km_glycolysis;}

double CellLiverCancer::getKrebsVmax() const
{return getAppConfig().cancer_km_max_glycolysis;}

double CellLiverCancer::getFractGlu() const
{return getAppConfig().cancer_glucose_usage;}

//void CellLiverCancer::ATPSynthesis(sf::Time dt)
//{CellLiver::ATPSynthesis(dt);}

//bool CellLiverCancer::update(sf::Time dt)
//{return CellLiver::update(dt);}

void CellLiverCancer::Krebs(sf::Time)
{}
