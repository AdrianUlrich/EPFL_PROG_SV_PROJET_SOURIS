#include "CellLiverCancer.hpp"
#include "Organ.hpp"
#include <Application.hpp>

double CellLiverCancer::getFractUptake() const
{return getAppConfig().cancer_fract_uptake;}

double CellLiverCancer::getGlycoKm() const
{return getAppConfig().cancer_km_glycolysis;}

double CellLiverCancer::getGlycoVmax() const
{return getAppConfig().cancer_km_max_glycolysis;}

double CellLiverCancer::getFractGlu() const
{return getAppConfig().cancer_glucose_usage;}

double CellLiverCancer::getDivisionEnergy() const
{return getAppConfig().cancer_division_energy;}

//void CellLiverCancer::ATPSynthesis(sf::Time dt)
//{CellLiver::ATPSynthesis(dt);}

//bool CellLiverCancer::update(sf::Time dt)
//{return CellLiver::update(dt);}

void CellLiverCancer::Krebs(sf::Time)
{}

void CellLiverCancer::divide(Organ::Kind)
{CellLiver::divide(Organ::Kind::CANCER);}
