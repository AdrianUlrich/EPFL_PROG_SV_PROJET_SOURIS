#ifndef I_LAB_HPP
#define I_LAB_HPP

#include <vector>
#include <Utility/Vec2d.hpp>
#include <SFML/Graphics.hpp>
#include "Cheese.hpp"
#include "Box.hpp"
#include "Mouse.hpp"
using std::vector;

class Lab : public sf::NonCopyable
{
public :
	/** default constructor
		* uses makeboxes(getAppConfig().simulation_lab_nb_boxes)
		*/
	Lab();

	/** destructor deletes pointers etc
		* uses reset() and destroyBoxes()
		*/
	~Lab();

	void makeBoxes(unsigned int nbCagesPerRow);
	void destroyBoxes();

	void update(sf::Time dt);
	void drawOn(sf::RenderTarget&);
	void reset();

	bool addCheese(Cheese*);
	bool addAnimal(Animal*);

	vector<SimulatedEntity*>* findTargetsInSightOf(Animal*);

private:
	bool addEntity(SimulatedEntity*);

	vector<vector<Box*>> boites;
	vector<SimulatedEntity*> NTTs;
};

#endif //I_LAB_HPP
