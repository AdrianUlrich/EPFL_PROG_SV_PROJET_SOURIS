#ifndef I_LAB_HPP
#define I_LAB_HPP

#include <vector>
#include <Utility/Vec2d.hpp>
#include <SFML/Graphics.hpp> 
#include <Application.hpp>

class Lab
{
public :
	void makeBoxes(unsigned int nbCagesPerRow);
	void destroyBoxes();
	void update(sf::Time dt);
	void drawOn(sf::RenderTarget& targetWindow);
	void drawOn(sf::RenderTarget& targetWindow);



private:
	vector <Box*> boite ();
	

	
};

#endif //I_LAB_HPP
