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
	
	/**Focus sur un animal*/
	void trackAnimal(Animal* n) {tracked = n;}
	void trackAnimal(const Vec2d&);
	void switchToView(View view);
	void stopTrackingAnyEntity();
	
	/** lien entre animal et organ */
	
	void updateTrackedAnimal();
	void drawCurrentOrgan((sf::RenderTarget& target);
	
private:
	vector<vector<Box*>> boites;
	vector<SimulatedEntity*> NTTs;
	Animal* tracked;
};

#endif //I_LAB_HPP
