#ifndef I_LAB_HPP
#define I_LAB_HPP

#include <vector>
#include <Utility/Vec2d.hpp>
#include <SFML/Graphics.hpp>
#include "Animal.hpp"
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

	/** destructor deletes pointers etc */
	~Lab();

	void makeBoxes(unsigned int nbCagesPerRow);
	void destroyBoxes();

	void update(sf::Time dt);
	void drawOn(sf::RenderTarget&);
	void reset();

	bool addAnimal(Mouse*);
	bool addCheese(Cheese*);
	bool addEntity(SimulatedEntity*);

private:
	vector<vector<Box*>> boites;
	vector<SimulatedEntity*> NTTs;
};

#endif //I_LAB_HPP
