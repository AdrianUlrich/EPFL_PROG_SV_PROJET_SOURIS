#include "Organ.hpp"
#include "CellHandler.hpp"

#include <Application.hpp>
#include <Utility/Vertex.hpp>
#include <Types.hpp>

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


void Organ::createLiver()
{
	
}

void Organ::createBloodSystem()
{
	
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

