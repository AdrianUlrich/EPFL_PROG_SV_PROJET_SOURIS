#include "CellLiver.hpp"

#include <Random/Random.hpp>
#include <Application.hpp>

#include <cmath>


CellLiver::CellLiver(CellHandler* h, double atp)
	:	CellOrgan(h)
	,	atp(atp)
{}

bool CellLiver::update(sf::Time dt)
{
	atp*=1-exp(-getAppConfig().liver_decay_atp*dt.asSeconds());
	atp-=uniform(getAppConfig().base_atp_usage , getAppConfig().base_atp_usage+getAppConfig().range_atp_usage);
	return CellOrgan::update(dt) or atp<=0;
}
