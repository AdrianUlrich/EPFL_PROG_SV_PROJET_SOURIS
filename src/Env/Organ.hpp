#ifndef ORGAN_HPP
#define ORGAN_HPP

#include <SFML/Graphics.hpp>
#include <Application.hpp>

class Organ 
{
	public:
		Organ(bool generation);
		void update();
		void drawOn(sf::RenderTarget& target);
		void updateRepresentation();
		//void updateRepresentationAt();	
		double getWidth();
		double getHeight();

	protected:
		void generate();
		void reloadConfig();
		void reloadCacheStructure();
		void createLiver();
		void createBloodSystem();

	private:
		int nbCells;
		float cellSize;
		sf::RenderTexture renderingCache;
		bool generation;

};


#endif // ORGAN_HPP
