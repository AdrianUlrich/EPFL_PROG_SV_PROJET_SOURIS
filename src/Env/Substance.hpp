#ifndef I_SUBSTANCE_HPP
#define I_SUBSTANCE_HPP

#include <Types.hpp>
#include <Utility/Constants.hpp>


/** \brief Conteneur pour substances et methodes
 * utillitaires pour leur manipulation
 */
class Substance
{
public:

  /** \brief Constructeur utilisant des concentrations
   * initiales
   *
   * \param cVGEF quantité de VGEF
   * \param cGLU quantité de glucose
   * \param cBMP quantitéé de bromopyruvate
   */
  Substance(double cVGEF, double cGLU, double cBMP);

  /** \brief Constructeur par défaut initialisant
   * les concentrations à zéro
   */
	Substance();

  /** \brief Constructeur de copie par défaut
   */
	Substance(const Substance& sub) = default;

  /** \brief Opérateur d'assignement par défaut
   *
   * \param Substance à assigner
   * \return L'instance assignée
   */
	Substance& operator=(Substance const&) = default;

  /** \brief Destructeur par défaut
   */
	~Substance() = default;

  /**
   * \param precision (par défaut SUBSTANCE_PRECISION)
   * \return vrai si les quantités sont nulles
   */
	bool isNull(double precision = SUBSTANCE_PRECISION);

  /** \brief Multiplie la valeur d'une concentration
   * spécifiée
   *
   * \param SubstanceId La substance à modifier
   * \param scalaire Le paramètre de modification
   * (Si 0, annule toutes les quantités)
   * \return void
   */
	void update(SubstanceId,double scalaire);

  /** \brief Prend une fraction d'une concentration de
   * l'instance courante et la donne à une autre
   * instance
   *
   * Si la quantité à transférer est inférieure à
   * SUBSTANCE_PRECISION, on ne transfère pas
   *
   * \param double fraction à transférer
   * \param Substance& receveur
   * \param SubstanceId Substance à transférer
   *
   * \return void
   */
	void uptakeOnGradient(double c,Substance&,SubstanceId);

  /**
   * \return Fraction de VGEF
   */
	double getFractVGEF() const;

  /**
   * \return Fraction de glucose
   */
	double getFractGlucose() const;

  /**
   * \return Fraction de bromopyruvate
   */
	double getFractInhibitor() const;

  /**
   * \return Concentration totale
   */
	double getTotalConcentration() const;

  /** \brief Comparaison entre instances Substance
   * \return vrai si identiques à SUBSTANCE_PRECISION près
   */
	bool operator==(Substance const&) const;

  /** \brief Accès en lecture seule des quantités
   * \param SubstanceId Lla quantité à lire
   */
	double const& operator[](SubstanceId) const;

  /** \brief Addition entre instances Substance
   */
	Substance& operator +=(Substance const&);

  /** \brief Soustraction entre instances Substance
   */
	Substance& operator -=(Substance const&);

  /** \brief Multiplication d'une substance par un scalaire
   */
	Substance& operator *=(double);


private:

  /** \brief Méthode privée responsable de restreindre
   * les valeurs des substances entre SUBSTANCE_PRECISION
   * et substance_max_value
   */
	void normalise();

private:

	static const double cMAX; /**< substance_max_value */

	double cVGEF; /**< quantité de VGEF */
	double cGLU; /**< quantité de glucose */
	double cBMP; /**< quantité de bromopyruvate */
};

/** \brief multiplication par un scalaire
 *
 * \param Substance à multiplier
 * \param scalaire
 */
Substance& operator*(Substance,double);

/** \brief Comparaison entre instances de substance
 * \return l'inverse de l'opérateur==
 */
bool operator!=(Substance const&,Substance const&);

/** \brief surcharge de l'opérateur de flux pour affichage
 * dans la console
 */
std::ostream& operator<<(std::ostream&, Substance const&);

#endif //I_SUBSTANCE_HPP
