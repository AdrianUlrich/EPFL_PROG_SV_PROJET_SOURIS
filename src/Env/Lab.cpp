#include "Lab.hpp"
#include <exception>
#include <Application.hpp>

Lab::Lab()
:	animal(nullptr),
	cheese(nullptr)
{
	makeBoxes(getAppConfig().simulation_lab_nb_boxes);
}

void Lab::makeBoxes(unsigned int nbCagesPerRow)
{
	if (!(boites.empty()))
		destroyBoxes();
	if (nbCagesPerRow < 1)
		throw std::invalid_argument("Cannot have zero or less cages");
	double largeur((getApp().getLabSize().x)/nbCagesPerRow);
	double hauteur((getApp().getLabSize().y)/nbCagesPerRow);
	for (unsigned int i(0); i<nbCagesPerRow; ++i)
	{
		boites.push_back(std::vector<Box*>(0));
		for (unsigned int j(0); j<nbCagesPerRow; ++j)
		{
			boites[i].push_back(new Box({(i+0.5)*largeur,(j+0.5)*hauteur},largeur,hauteur,largeur*0.025));
		}
	}
}

void Lab::destroyBoxes()
{
	for (auto& vec : boites)
	{
		for (auto& val : vec)
		{
			delete val;
			val=nullptr;
		}
	}
	boites.clear();
}

Lab::~Lab()
{
	destroyBoxes();
	reset();
}

void Lab::update(sf::Time dt)
{
	if (animal != nullptr)
	{
		animal->update(dt);
		if (animal->isDead())
		{
			delete animal;
			animal=nullptr;
		}
	}
	if (cheese!=nullptr)
	{
		cheese->update(dt);
		if (cheese->isDead())
		{
			delete cheese;
			cheese = nullptr;
		}
	}
}

void Lab::drawOn(sf::RenderTarget& target)
{
	for (auto& vec : boites)
	{
		for (auto& val : vec)
		{
			if (val != nullptr)
			val->drawOn(target);
		}
	}
	if (animal != nullptr)
		animal->drawOn(target);
	if (cheese !=nullptr)
		cheese->drawOn(target);
}

void Lab::reset()
{
	if (animal != nullptr)
	{
		delete animal;
		animal=nullptr;
	}
	if (cheese !=nullptr)
	{
		delete cheese;
		cheese=nullptr;
	}
}

bool Lab::addAnimal(Mouse* mickey)
{
	if (animal != nullptr)
		return false;
	delete animal;
	animal=mickey;
	return true;
}

bool Lab::addCheese(Cheese* caprice_des_dieux)
{
	if (cheese != nullptr)
		return false;
	delete cheese;
	cheese=caprice_des_dieux;
	return true;
}
