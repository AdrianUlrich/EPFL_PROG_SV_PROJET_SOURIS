#include "Organ.hpp"
#include "CellHandler.hpp"

#include <Application.hpp>

Organ::Organ(bool generation)
{
	if (generation) generate();	
}



void Organ::update()
{
	updateRepresentation();
}
	
void Organ::drawOn(sf::RenderTarget& target)
{
	sf::Sprite image(renderingCache.getTexture()); // transforme l'image en texture
	target.draw(image); // affiche la texture	
}


void Organ::generate()
{
	reloadConfig();
	reloadCacheStructure();	
	createLiver();
	createBloodSystem();
	updateRepresentation();
}


void Organ::reloadConfig()
{
	nbCells = getAppConfig().simulation_organ_nbCells;
	cellSize = getWidth()/nbCells;
	if (!cellHandlers.empty())
	{
		for (vector<CellHandler*>& vec : cellHandlers)
		{
			if (!vec.empty())
			{
				for (CellHandler* val : vec)
					delete val;
				vec.clear();
			}
			
		}
		cellHandlers.clear();					
	}
	else
	{
		cellHandlers=vector<vector<CellHandler*>>(nbCells,vector<CellHandler*>(nbCells,nullptr));
		for (int i(0);i<nbCells;++i)
			for (int j(0);j<nbCells;++j)
				cellHandlers[i][j]=new CellHandler({i,j},this);
	}
	
}

void Organ::reloadCacheStructure()
{
	renderingCache.create(cellSize*nbCells, cellSize*nbCells);	
}


void Organ::createLiver()
{
	
}

void Organ::createBloodSystem()
{
	
}

void Organ::updateRepresentation()
{
	renderingCache.clear(sf::Color(223,196,176));
	renderingCache.display();	
}


void Organ::updateRepresentationAt(CellCoord const&)
{}


double Organ::getWidth() const
{return getAppConfig().simulation_organ_size;}

double Organ::getHeight() const
{return getAppConfig().simulation_organ_size;}

bool Organ::isOut(CellCoord const& c) const
{return c.x<0 or c.y<0 or c.x>nbCells-1 or c.y>nbCells-1;}

CellCoord Organ::toCellCoord(Vec2d const& pos) const
{return vec2dToCellCoord(pos,getWidth(),getHeight(),cellSize);}
