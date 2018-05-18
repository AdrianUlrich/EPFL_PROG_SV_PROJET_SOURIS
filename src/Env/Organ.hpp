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

		void updateRepresentation(bool);
		virtual void updateRepresentationAt(CellCoord const&);
		
	protected:
		virtual void generate();
		void reloadConfig();
		void reloadCacheStructure();
		void createLiver();
		void createBloodSystem();

	private:
		void drawRepresentation ();
		
		int nbCells;
		float cellSize;
		sf::RenderTexture renderingCache;
		vector<vector<CellHandler*>> cellHandlers;
		vector <sf::Vertex> bloodVertexes;
		vector <sf::Vertex> liverVertexes;
};


#endif // ORGAN_HPP
