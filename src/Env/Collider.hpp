#ifndef I_COLLIDER_HPP
#define I_COLLIDER_HPP

#include <Utility/Vec2d.hpp>

/** \brief Classe abstraite permettant la detection
 * de collisions
 */
class Collider
{
public:
	//Collider(Vec2d const& position, double rayon);

  /** \brief Methode pure virtuelle garante de la position
   * de l'entite
   * Doit etre implementee par les classes derivees
   */
	virtual Vec2d getCenter() const = 0;

  /** \brief Methode pure virtuelle garante du rayon
   * de l'entite
   * Doit etre implementee par les classes derivees
   */
  virtual double getRadius() const = 0;

  /** \brief Detection de collision entre
   *
   * \param Collider autre
   * \return vrai si les entites se superposent
   */
	bool isColliding(Collider const& other) const;

  /** \brief Signalisation de l'inclusion d'un point
   * dans l'entite
   *
   * \param Vec2d point
   * \return vrai si le point est a l'interieur de l'entite
   */
	bool isPointInside(Vec2d const&) const;

  /** \brief Destructeur virtuel
   */
	virtual ~Collider() = default;

private:
	//Vec2d position;
	//double rayon;
};

/** \brief Operateur appellant isColliding
 */
bool operator |(Collider const& body1, Collider const& body2);

/** \brief Operateur lie a isPointInside
 */
bool operator >(Collider const& body, Vec2d const& point);


#endif //I_COLLIDER_HPP
