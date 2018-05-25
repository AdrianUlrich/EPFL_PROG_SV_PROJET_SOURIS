#include "CellBlood.hpp"
#include "Organ.hpp"
#include "CellHandler.hpp"

#include <Application.hpp>

#include <cmath>

CellBlood::CellBlood(CellHandler* h,TypeBloodCell t)
	:	CellOrgan(h)
	,	type(t)
{}

TypeBloodCell CellBlood::getType() const
{return type;}

bool CellBlood::update(sf::Time dt)
{
	if (type==TypeBloodCell::CAPILLARY)
	{
		CellCoord pos(handler->getPos());
		int RAYON_DIFFUSION(getAppConfig().substance_diffusion_radius);
		double m(getAppConfig().substance_max_value);
		Substance C0
		(
			std::min(m,std::max(-m,getAppEnv().getDelta(SubstanceId::VGEF))),
			std::min(m,std::max(-m,getAppConfig().base_glucose+getAppEnv().getDelta(SubstanceId::GLUCOSE))),
			std::min(m,std::max(-m,getAppConfig().base_bromo+getAppEnv().getDelta(SubstanceId::BROMOPYRUVATE)))
		);
		double D(getAppConfig().substance_diffusion_constant);
		for (int i(-RAYON_DIFFUSION);i<=RAYON_DIFFUSION;++i)
		{
			for (int j(-RAYON_DIFFUSION);j<=RAYON_DIFFUSION;++j)
			{
				double r(Vec2d(i,j).length());
				Substance C(C0*0.5*(1-std::erf(r/sqrt(4*D*dt.asSeconds()))));
				handler->updateCellHandlerAt(pos+CellCoord(i,j),C);
			}
		}
		
	}
	return false;//CellOrgan::update(dt) would return true if dead (i.e of cancer)
}

