#include "Organ.hpp"

#include <Application.hpp>

Organ::Organ (bool generation)
: generation (true)
{
	if (generation==true) genrate();	
}



void Organ::update()
{
	//updateRepresentation()
}
	
void Organ::drawOn(sf::RenderTarget& target)
{
	sf::Sprite image(renderingCache_.getTexture()); // transforme l'image en texture
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
	cellSize = getWidth();
}

void Organ::reloadCacheStructure()
{
	renderingCache.create(horizontalSize, verticalSize);	
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

/*
void Organ::updateRepresentationAt()
{
	renderingCache.clear(sf::Color(223,196,176));
	renderingCache.display();	
}
*/

double Organ::getWidth() 
{
	return getAppConfig().simulation_organ_size;
}

	
double Organ::getHeight() 
{
	return getAppConfig().simulation_organ_size;
}
