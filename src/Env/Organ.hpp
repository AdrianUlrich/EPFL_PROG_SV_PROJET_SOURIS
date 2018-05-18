#ifndef ORGAN_HPP
#define ORGAN_HPP

#include <SFML/Graphics.hpp>
#include <Application.hpp>

class Organ 
{
	public:
		Organ(bool generation);
		
		virtual ~Organ() = default;
		
		void update();
		void drawOn(sf::RenderTarget& target);
		
		double getWidth();
		double getHeight();

		void updateRepresentation();
		//void updateRepresentationAt();

	protected:
		virtual void generate();
		void reloadConfig();
		void reloadCacheStructure();
		void createLiver();
		void createBloodSystem();

	private:
		int nbCells;
		float cellSize;
		sf::RenderTexture renderingCache;
		//bool generation;
};


#endif // ORGAN_HPP
