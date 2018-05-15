#ifndef I_LAB_HPP
#define I_LAB_HPP

#include <SFML/Graphics.hpp>

#include <vector>
#include <Utility/Vec2d.hpp>
#include <Types.hpp>
#include "Cheese.hpp"
#include "Box.hpp"
#include "Mouse.hpp"
#include "Animal.hpp"
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
	bool addEntity(SimulatedEntity*,size_t);
	
	/**Focus sur un animal*/
	void trackAnimal(Animal* n);
	void trackAnimal(const Vec2d&);
	void switchToView(View view);
	void stopTrackingAnyEntity();
	
	/** lien entre animal et organ */
	
	void updateTrackedAnimal();
	void drawCurrentOrgan(sf::RenderTarget& target);
	
private:
	vector<vector<Box*>> boites;
	
	/** index:
	 * 1 => animals
	 * 0 => cheeses
	 * */
	vector<vector<SimulatedEntity*>> NTTs;
	Animal* tracked;
};

#endif //I_LAB_HPP
