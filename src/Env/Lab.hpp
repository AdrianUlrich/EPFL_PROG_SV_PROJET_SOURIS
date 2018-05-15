#ifndef I_LAB_HPP
#define I_LAB_HPP

#include <SFML/Graphics.hpp>

#include <vector>
#include <Utility/Vec2d.hpp>
#include <Types.hpp>
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

	/**Focus sur un animal*/
	void trackAnimal(Animal* n);
	void trackAnimal(const Vec2d&);
	void switchToView(View view);
	void stopTrackingAnyEntity();
	
	/** lien entre animal et organ */
	void updateTrackedAnimal();
	void drawCurrentOrgan(sf::RenderTarget& target);
  
  /** providing vision to animals */
	vector<SimulatedEntity*>* findTargetsInSightOf(Animal*);

private:
	bool addEntity(SimulatedEntity*,unsigned char);

	vector<vector<Box*>> boites;

	vector<Animal*> animals;
	vector<Cheese*> cheeses;
	vector<SimulatedEntity*> NTTs;
};

#endif //I_LAB_HPP
