#include "Lab.hpp"
#include <exception>
#include <Application.hpp>

Lab::Lab()
:	NTTs(0)
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
size_t nNTTs(NTTs.size());
	for (size_t i(0); i<nNTTs; ++i)
	{
		if (NTTs[i] != nullptr)
		{
			NTTs[i]->update(dt);
			if (NTTs[i]->isDead())
			{
				delete NTTs[i];
				NTTs[i]=nullptr;
				NTTs.erase(NTTs.begin()+i);
				--nNTTs;
			}
		}
	}
}

void Lab::drawOn(sf::RenderTarget& target)
{
	for (auto& vec : boites)
	{
		for (auto val : vec)
		{
			if (val != nullptr)
			val->drawOn(target);
		}
	}
	for (auto NTT : NTTs)
	{
		NTT->drawOn(target);
	}
}

void Lab::reset()
{
	for (auto& NTT : NTTs)
	{
		delete NTT;
		NTT = nullptr;
	}
	NTTs.clear();
}

bool Lab::addAnimal(Mouse* mickey)
{
	if (NTTs.size()>100)
		return false;
	NTTs.push_back(mickey);
	return true;
}

bool Lab::addCheese(Cheese* caprice_des_dieux)
{
	if (NTTs.size()>100)
		return false;
	NTTs.push_back(caprice_des_dieux);
	return true;
}
