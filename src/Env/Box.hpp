#ifndef I_BOX_HPP
#define I_BOX_HPP

#include <Utility/Vec2d.hpp>
#include <SFML/Graphics.hpp>
#include <array>

typedef std::pair <Vec2d, Vec2d> Wall; //! <bottom right corner, top left corner>

class Box
{
public:
	Box (Vec2d position, double largeur=300, double hauteur=300, double epaisseur=10);

	Vec2d getCenter() const	{return pos;}
	double getWidth() const	{return l;}
	double getHeight () const {return h;}
	double getWallWidth () const {return e;}

	double getLeftLimit(bool intern = false);
	double getRightLimit(bool intern = false);
	double getTopLimit(bool intern = false);
	double getBottomLimit(bool intern = false);
	bool isPositionInside(const Vec2d&);
	bool isPositionOnWall(const Vec2d&);

	void drawOn(sf::RenderTarget&);
	bool isEmpty() {return empty;}
	void flipEmpty() {empty=!empty;}

private:
	Vec2d pos;
	double l; //!< Largeur de la boite
	double h; //!< Hauteur de la boite
	double e; //!< Epaisseur de la boite
	
	/**mur gauche : [0]
	 * mur bas : [1]
	 * mur droit : [2]
	 * mur haut : [3]	*/
	std::array<Wall,4> murs;
	
	/*! Graphic files that dont need to be created every time */
	std::array<sf::RectangleShape,4> builtRecs;
	sf::Texture* texture;
	bool empty;
};


#endif //I_BOX_HPP
