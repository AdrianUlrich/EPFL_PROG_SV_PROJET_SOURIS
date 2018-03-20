#include "Lab.hpp"
#include <exception>

void Lab::makeBoxes(unsigned int nbCagesPerRow)
{
	if (nbCagesPerRow<1)
		throw std::invalid_argument("Cannot have zero or less cages");
	double largeur(getApp().getLabSize().x);
	double hauteur(getApp().getLabSize().y);
	for (int i(0); i<nbCagesPerRow; ++i)
	{
		boite.push_back(vector<Box*>);
		for (int j(0); j<nbCagesPerRow; ++j)
		{
			boite[i].push_back(new Box(Vec2d(i*largeur,j*hauteur),largeur,hauteur,largeur/40))
		}
	}
}

void Lab::destroyBoxes()
{
	for (auto vec : boite)
	{
		for (auto val : vec)
		{
			delete val;
			val=nullptr;
		}
	}
	boite.clear();
}

void Lab::update(sf::Time dt)
{

}

void Lab::drawOn(sf::RenderTarget& targetWindow)
{

}

void Lab::drawOn(sf::RenderTarget& targetWindow)
{


}
