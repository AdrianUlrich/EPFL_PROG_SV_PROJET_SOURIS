#include "Lab.hpp"
#include <exception>
#include <Application.hpp>
#include "Types.hpp"
#include <iostream>
using namespace std;

Lab::Lab()
:	tracked(nullptr)
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
				// NTTs[i]->resetBox(); //! La boite est liberee dans le destructeur de animal
				delete NTTs[i];
				NTTs[i]=NTTs[NTTs.size()-1];
				NTTs.pop_back();
				//NTTs[i]=nullptr;
				//NTTs.erase(NTTs.begin()+i);
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

bool Lab::addEntity(SimulatedEntity* ntt)
{
	if (ntt==nullptr)// || NTTs.size()>100)
		return false;
	NTTs.push_back(ntt);
	return true;
}

bool Lab::addAnimal(Mouse* mickey)
{
	if (mickey==nullptr) return false;
	for (auto& vec : boites)
	{
		for (auto val : vec)
		{
			if (mickey->canBeConfinedIn(val))
			{
				if (val->isEmpty())
				{
					mickey->confine(val); //! La souris est déja créée mais maintenant elle est dans une boite
					bool succ(addEntity(mickey));
					if (succ)
						val->addOccupant(); //! La boite est occuppée
					return succ;
				}
			}
		}
	}
	if (mickey!=nullptr)
		delete mickey;
	return false;
}

bool Lab::addCheese(Cheese* caprice_des_dieux)
{
	return addEntity(caprice_des_dieux);
}


void Lab::trackAnimal(const Vec2d& p)
{
	for (auto val : NTTs)
	{
		if ((p-val->getCenter()).lengthSquared() < val->getRadius()*val->getRadius())
		{
			trackAnimal(val);
		}
	}
}

void Lab::switchToView(sf::View view)
{
	getApp().switchToView(view);	
}

void Lab::stopTrackingAnyEntity()
{
	tracked=nullptr;
}


void Lab::updateTrackedAnimal() 
{
	if (foie != nullprt)
	{
		Organ::update();
	}
}

void Lab::drawCurrentOrgan(sf::RenderTarget& target)
{
	if(foie =! nullprt)
	{
		tracked -> Animal::drawCurrentOrgan(target);
	}
}

void Lab::trackAnimal(Animal* n) 
{
	tracked = n;
}
