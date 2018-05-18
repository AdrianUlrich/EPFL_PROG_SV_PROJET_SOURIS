#ifndef ORGAN_HPP
#define ORGAN_HPP

#include <SFML/Graphics.hpp>
#include <Application.hpp>
#include <Utility/Utility.hpp>
#include <vector>
using std::vector;

class CellHandler;


class Organ 
{
	public:
		Organ(bool generation);
		
		virtual ~Organ() = default;
		
		void update();
		void drawOn(sf::RenderTarget& target);
		
		/** simply return config size of organ */
		double getWidth() const;
		double getHeight() const;
		
		bool isOut(CellCoord const&) const;
		CellCoord toCellCoord(Vec2d const&) const;

		void updateRepresentation();
		virtual void updateRepresentationAt(CellCoord const&);

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
		vector<vector<CellHandler*>> cellHandlers;
};


#endif // ORGAN_HPP
