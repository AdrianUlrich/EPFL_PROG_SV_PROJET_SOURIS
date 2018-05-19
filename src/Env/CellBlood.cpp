#include "CellBlood.hpp"
#include "Organ.hpp"
#include "CellHandler.hpp"

#include <Application.hpp>

#include <cmath>

CellBlood::CellBlood(CellHandler* h,TypeBloodCell t)
	:	CellOrgan(h)
	,	type(t)
{
	
}

bool CellBlood::update(sf::Time dt)
{
	if (type==TypeBloodCell::CAPILLARY)
	{
		CellCoord pos(handler->getPos());
		int RAYON_DIFFUSION(getAppConfig().substance_diffusion_radius);
		Substance C0(0,getAppConfig().base_glucose,getAppConfig().base_bromo);
		double D(getAppConfig().substance_diffusion_constant);
		for (int i(-RAYON_DIFFUSION);i<=RAYON_DIFFUSION;++i)
		{
			for (int j(-RAYON_DIFFUSION);j<=RAYON_DIFFUSION;++j)
			{
				double r(Vec2d(i,j).length());
				Substance C(C0*0.5*(1-std::erf(r/sqrt(4*D*dt.asSeconds()))));
				handler->getOrgan()->updateCellHandlerAt(pos+CellCoord(i,j),C);
			}
		}
		
	}
	return CellOrgan::update(dt);// or ; // return true if dead
}

