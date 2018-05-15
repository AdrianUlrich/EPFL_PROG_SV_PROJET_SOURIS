#include "Lab.hpp"
#include <exception>
#include <Application.hpp>
#include "Organ.hpp"

//DEBUG:
//#include <iostream>
//using namespace std;

Lab::Lab()
:	NTTs(2),
	tracked(nullptr)
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
	for (auto& val : NTTs) //Type: vector<sim*>
	{size_t nNTTs(val.size());
		for (size_t i(0); i<nNTTs; ++i)
		{
			val[i]->update(dt);
			if (val[i]->isDead())
			{
				// NTTs[i]->resetBox(); //! La boite est liberee dans le destructeur de animal
				delete val[i];
				val[i]=val[--nNTTs];
				val.pop_back();
				//NTTs[i]=nullptr;
				//NTTs.erase(NTTs.begin()+i);
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
	for (auto& val : NTTs)
	{	for (auto NTT : val)
		{
			NTT->drawOn(target);
		}
	}
}

void Lab::reset()
{
	for (auto& val : NTTs)
	{	for (auto NTT : val)
		{
			delete NTT;
			NTT = nullptr;
		}
	}
	NTTs.clear();
}

bool Lab::addEntity(SimulatedEntity* ntt, size_t i)
{
	NTTs[i].push_back(ntt);
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
					bool succ(addEntity(mickey,1));
					if (succ)
						val->addOccupant(); //! La boite est occuppée
					return succ;
				}
			}
		}
	}
	delete mickey;
	return false;
}

bool Lab::addCheese(Cheese* c)
{
if (c==nullptr) return false;
	for (auto& vec : boites)
	{
		for (auto val : vec)
		{
			if (c->canBeConfinedIn(val))
			{
				//if (val->isEmpty())
				{
					c->confine(val); //! Le fromton est déja créée mais maintenant elle est dans une boite
					return addEntity(c,0);
				}
			}
		}
	}
	delete c;
	return false;
}


void Lab::trackAnimal(const Vec2d& p)
{
	for (auto val : NTTs[1])
	{
		if (val->isPointInside(p))
		{
			trackAnimal(val);
			break;
		}
	}
}

void Lab::switchToView(View view)
{
	getApp().switchToView(view);	
}

void Lab::stopTrackingAnyEntity()
{
	tracked=nullptr;
}


void Lab::updateTrackedAnimal() 
{
	if (tracked != nullptr)
	{
		tracked->updateOrgan();
	}
}

void Lab::drawCurrentOrgan(sf::RenderTarget& target)
{
	if(tracked != nullptr)
	{
		tracked->drawCurrentOrgan(target);
	}
}

void Lab::trackAnimal(Animal* n) 
{
	tracked = n;
}
