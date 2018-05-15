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

template<typename T,typename Q>
struct NTTZ
{
	unsigned char nbTypes=2;
	vector<Cheese*> first;
	vector<Animal*> second;
	vector<SimulatedEntity*>& operator[](size_t i)
	{	switch(i)
		{	case 0:
			return first;
			
			case 1:
			return second;
		}
	}
}
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
	bool addEntity(SimulatedEntity*,size_t);

	vector<vector<Box*>> boites;

	vector<NTTZ*> NTTs;
	Animal* tracked;
};

#endif //I_LAB_HPP
