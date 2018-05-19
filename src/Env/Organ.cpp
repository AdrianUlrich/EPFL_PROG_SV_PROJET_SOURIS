#include "Organ.hpp"
#include "CellHandler.hpp"

#include <Application.hpp>
#include <Utility/Vertex.hpp>
#include <Types.hpp>
#include <Random/Random.hpp>

#include <algorithm>
#include <vector>
using std::vector;

Organ::Organ(bool generation)
{
	if (generation) generate();	
}

double Organ::getWidth() const
{return getAppConfig().simulation_organ_size;}

double Organ::getHeight() const
{return getAppConfig().simulation_organ_size;}

bool Organ::isOut(CellCoord const& c) const
{return c.x<0 or c.y<0 or c.x>nbCells-1 or c.y>nbCells-1;}

CellCoord Organ::toCellCoord(Vec2d const& pos) const
{return vec2dToCellCoord(pos,getWidth(),getHeight(),cellSize);}

void Organ::update()
{
	sf::Time dt(sf::seconds(getAppConfig().simulation_fixed_step));
	for (auto& vec : cellHandlers)
		for (auto val : vec)
			val->update(dt);		
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
	liverVertexes = generateVertexes(getAppConfig().simulation_organ["textures"], nbCells, cellSize);
	bloodVertexes = liverVertexes;
}

void Organ::updateRepresentation(bool also_update)
{
	renderingCache.clear(sf::Color(223,196,176));

	if (also_update)
		for (int y(0); y<nbCells; ++y)
			for (int x(0); x<nbCells; ++x)
				updateRepresentationAt({x,y}); // implicit constructor of CellCoord
	
	drawRepresentation();
	
	renderingCache.display();	
	
}

void Organ::drawRepresentation ()
{
	sf::RenderStates rs;
	auto textures = getAppConfig().simulation_organ["textures"];
	rs.texture = &getAppTexture(textures["liver"].toString()); // ici pour la texture liée une cellule hépatique
	renderingCache.draw(liverVertexes.data(), bloodVertexes.size(), sf::Quads, rs); 	
	rs.texture = &getAppTexture(textures["blood"].toString()); // ici pour la texture liée une cellule sanguine
	renderingCache.draw(bloodVertexes.data(), bloodVertexes.size(), sf::Quads, rs); 
}


void Organ::updateRepresentationAt(CellCoord const& c)
{
	int x(c.x),y(c.y);
	auto i(indexesForCellVertexes(x,y,nbCells));
	
	/// lots of lines but minimises number of assignments(8) and checks(1 or 2)
	if(cellHandlers[x][y]->hasBlood())
	{
		bloodVertexes[i[0]].color.a=
		bloodVertexes[i[1]].color.a=
		bloodVertexes[i[2]].color.a=
		bloodVertexes[i[3]].color.a=255;
		liverVertexes[i[0]].color.a=
		liverVertexes[i[1]].color.a=
		liverVertexes[i[2]].color.a=
		liverVertexes[i[3]].color.a=0;
	}
	else if(cellHandlers[x][y]->hasLiver())
	{
		liverVertexes[i[0]].color.a=
		liverVertexes[i[1]].color.a=
		liverVertexes[i[2]].color.a=
		liverVertexes[i[3]].color.a=255;
		bloodVertexes[i[0]].color.a=
		bloodVertexes[i[1]].color.a=
		bloodVertexes[i[2]].color.a=
		bloodVertexes[i[3]].color.a=0;
	}
	else
	{
		bloodVertexes[i[0]].color.a=
		bloodVertexes[i[1]].color.a=
		bloodVertexes[i[2]].color.a=
		bloodVertexes[i[3]].color.a=0;
		liverVertexes[i[0]].color.a=
		liverVertexes[i[1]].color.a=
		liverVertexes[i[2]].color.a=
		liverVertexes[i[3]].color.a=0;
	}
}

void Organ::updateCellHandler(CellCoord const& c, Kind k)
{
	switch (k)
	{
		case Kind::ECM :
		cellHandlers[c.x][c.y]->setECM();
		break;
		
		case Kind::Liver :
		cellHandlers[c.x][c.y]->setLiver();
		break;
		
		case Kind::Artery :
		cellHandlers[c.x][c.y]->setBlood(TypeBloodCell::ARTERY);
		break;
		
		case Kind::Capillary :
		cellHandlers[c.x][c.y]->setBlood(TypeBloodCell::CAPILLARY);
		break;
		
		default:
		//NOPE
		break;
	}
}


void Organ::createLiver()
{
	int r(nbCells+1);
	for (int x(0); x<nbCells; ++x)
	{
		int ox(x-nbCells);
		for (int y(0); y<nbCells; ++y)
		{
			int oy(y-nbCells);
			if (x*x+oy*oy<r*r and ox*ox+y*y<r*r)
				cellHandlers[x][y]->setLiver();
		}
	}
}

void Organ::createBloodSystem(bool generateCapillaries)
{
	/// Making Artery
	int SIZE_ARTERY(std::max(.03*nbCells,1.));
	int startX((nbCells-SIZE_ARTERY)/2),endX(startX+SIZE_ARTERY);
	generateArtery(startX,endX);
	
	if (generateCapillaries)
	{
		/// Making Capillaries
		int MIN_DIST(getAppConfig().blood_capillary_min_dist+1);
		int START_CREATION_FROM(getAppConfig().blood_creation_start);
		int NB_CAPILLARY((nbCells-START_CREATION_FROM)/3);
		--endX;
		int counter(0);
		for(int y(0); y<nbCells-START_CREATION_FROM && counter<NB_CAPILLARY; ++y)
		{
			if(uniform(1,3)==1)
			{
				CellCoord c(startX,y);
				generateCapillaryFromPosition(c,{-1,0});
				++counter;
				y+=MIN_DIST;
			}
		}
		counter = 0;
		for(int y(0); y<nbCells-START_CREATION_FROM && counter<NB_CAPILLARY; ++y)
		{
			if(uniform(1,3)==1)
			{
				CellCoord c(endX,y);
				generateCapillaryFromPosition(c,{1,0});
				++counter;
				y+=MIN_DIST;
			}
		}
	}

}

void Organ::generateArtery(int startX, int endX)
{
	for(int x(startX); x<endX; ++x)
	{
		for(int y(0); y<nbCells; ++y)
		{
			cellHandlers[x][y]->setBlood(TypeBloodCell::ARTERY);
		}
	}
}

bool Organ::generateCapillaryOneStep(CellCoord& p, CellCoord const& dir, int& NBcells, int const& maxLength)
{
	if (NBcells>=maxLength) return false;
	
	bool tried1(false),tried2(false);
	while (not (tried1 and tried2))
	{
		switch (uniform(1,6))
		{
			case 1:
			{
				tried1=true;
				CellCoord c(p.x,p.y-1);
				if (!isOut(c) and !cellHandlers[c.x][c.y]->hasBlood())
				{
					cellHandlers[c.x][c.y]->setBlood(TypeBloodCell::CAPILLARY);
					p=c;
					++NBcells;
					return true;
				}
			}
			/* Else falls through. */
			case 2:
			{
				tried2=true;
				CellCoord c(p.x,p.y+1);
				if (!isOut(c) and !cellHandlers[c.x][c.y]->hasBlood())
				{
					cellHandlers[c.x][c.y]->setBlood(TypeBloodCell::CAPILLARY);
					p=c;
					++NBcells;
					return true;
				}
			}
			/* Else falls through. */
			default:
			{
				CellCoord c(p+dir);
				if (!isOut(c) and !cellHandlers[c.x][c.y]->hasBlood())
				{
					cellHandlers[c.x][c.y]->setBlood(TypeBloodCell::CAPILLARY);
					p=c;
					++NBcells;
					return true;
				}
			}
		}
	}
	return false;
}

void Organ::generateCapillaryFromPosition(CellCoord& p, CellCoord dir)
{
	/// Growing Capillaries
	const int LENGTH_CAPILLARY((nbCells/2)-4);
	int length(1);
	while (generateCapillaryOneStep(p,dir,length,LENGTH_CAPILLARY))
	// cout<<'{'<<p.x<<','<<p.y<<'}'<<endl;
	;
}
