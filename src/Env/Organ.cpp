#include "Organ.hpp"

#include <Application.hpp>


void Organ::update()
{
	
}
	
void Organ::drawOn(sf::RenderTarget target)
{
	sf::Sprite image(renderingCache_.getTexture()); // transforme l'image en texture
	target.draw(image); // affiche la texture	
}


void Organ::generate()
{
	
}


void Organ::reloadConfig()
{
	nbCells_ = getAppConfig().simulation_organ_nbCells;
	cellSize_ = getWidth();
}

void Organ::reloadCacheStructure()
{
	renderingCache_.create(horizontalSize, verticalSize);	
}


void Organ::createLiver()
{
	
	
}

void Organ::createBloodSystem()
{
	
}

void updateRepresentation()
{
	renderingCache_.clear(sf::Color(223,196,176));
	renderingCache_.display();	
}
