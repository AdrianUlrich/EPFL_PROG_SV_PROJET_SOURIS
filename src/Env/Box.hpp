#ifndef I_BOX_HPP
#define I_BOX_HPP

#include <Utility/Vec2d.hpp>
#include <SFML/Graphics.hpp>
#include <array>

typedef std::pair <Vec2d, Vec2d> Wall; //! <bottom right corner, top left corner>

/** \brief Classe representant une boite avec une hauteur, largeur, epaisseur
 * et une limite a sa population
 */
class Box
{
public:

  /** \brief Constructeur prenant comme
   *
   * \param Vec2d position
   * \param double largeur
   * \param double hauteur
   * \param double epaisseur
   */
	Box(Vec2d position, double largeur=300, double hauteur=300, double epaisseur=10);

  /**
   * \return Vec2d position du centre
   */
	Vec2d getCenter() const	{return pos;}

  /**
   * \return largeur
   */
	double getWidth() const	{return l;}

  /**
   * \return hauteur
   */
	double getHeight () const {return h;}

  /**
   * \return epaisseur
   */
	double getWallWidth () const {return e;}

  /**
   * \param bool vrai pour l'interieur (faux par defaut)
   * \return L'abcisse du mur de gauche
   */
	double getLeftLimit(bool intern = false) const;

  /**
   * \param bool vrai pour l'interieur (faux par defaut)
   * \return L'abcisse du mur de draite
   */
	double getRightLimit(bool intern = false) const;

  /**
   * \param bool vrai pour l'interieur (faux par defaut)
   * \return L'ordonnee du mur du haut
   */
	double getTopLimit(bool intern = false) const;

  /**
   * \param bool vrai pour l'interieur (faux par defaut)
   * \return L'abcisse du mur du bas
   */
	double getBottomLimit(bool intern = false) const;

  /**
   * \param Vec2d position
   * \return vrai si le point est dans la boite
   * (a l'interieur des murs)
   */
	bool isPositionInside(const Vec2d&) const;

  /**
   * \param Vec2d position
   * \return vrai si le point est sur les murs
   */
	bool isPositionOnWall(const Vec2d&) const;

  /** \brief Methode d'affichache SFML
   *
   * \param sf::RenderTarget& fenetre a afficher
   * \return void
   */
	void drawOn(sf::RenderTarget&) const;

  /**
   * \return vrai si la boite est vide
   */
	bool isEmpty() const {return empty;}

  /** \brief Rend la boite occuppee
   * (max population : 1)
   *
   * \return void
   */
	void addOccupant() {empty=false;}

  /** \brief Libere la boite
   *
   * \return void
   */
	void reset() {empty=true;}

private:
	Vec2d pos; /**< Position du centre de la boite */
	double l; /**< Largeur de la boite */
	double h; /**< Hauteur de la boite */
	double e; /**< Epaisseur de la boite */

	/**
	 * mur gauche : [0]
	 * mur bas : [1]
	 * mur droit : [2]
	 * mur haut : [3]
	 */
	std::array<Wall,4> murs;

	/**< Comme éla boite est stationnaire, ses murs peuvent n'etre crees qu'une fois */
	std::array<sf::RectangleShape,4> builtRecs; /**< Rectangles SFML */
	sf::Texture* texture; /**< Texture SFML */

	bool empty; /**< Etat d'occupation de la boite */
};


#endif //I_BOX_HPP
