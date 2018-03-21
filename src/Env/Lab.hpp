#ifndef I_LAB_HPP
#define I_LAB_HPP

#include <vector>
#include <Utility/Vec2d.hpp>
#include <SFML/Graphics.hpp>
#include <Application.hpp>
#include "Animal.hpp"
#include "Cheese.hpp"
#include "Box.hpp"

class Lab
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

private:
	std::vector<std::vector<Box*>> boite;
	Animal* animal;
	Cheese* cheese;

};

#endif //I_LAB_HPP
