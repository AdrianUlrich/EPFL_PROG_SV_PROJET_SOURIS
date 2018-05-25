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
   * \param cVGEF quantite de VGEF
   * \param cGLU quantite de glucose
   * \param cBMP quantitee de bromopyruvate
   */
  Substance(double cVGEF, double cGLU, double cBMP);

  /** \brief Constructeur par defaut initialisant
   * les concentrations a zero
   */
	Substance();

  /** \brief Constructeur de copie par defaut
   */
	Substance(const Substance& sub) = default;

  /** \brief Operateur d'assignement par defaut
   *
   * \param Substance a assigner
   * \return L'instance assignee
   */
	Substance& operator=(Substance const&) = default;

  /** \brief Destructeur par defaut
   */
	~Substance() = default;

  /**
   * \param precision (par defaut SUBSTANCE_PRECISION)
   * \return vrai si les quantites sont nulles
   */
	bool isNull(double precision = SUBSTANCE_PRECISION);

  /** \brief Multiplie la valeur d'une concentration
   * specifiee
   *
   * \param SubstanceId La substance a modifier
   * \param scalaire Le parametre de modification
   * (Si 0, annule toutes les quantites)
   * \return void
   */
	void update(SubstanceId,double scalaire);

  /** \brief Prend une fraction d'une concentration de
   * l'instance courante et la donne a une autre
   * instance
   *
   * Si la quantite a transferer est inferieure a
   * SUBSTANCE_PRECISION, on ne transfere pas
   *
   * \param double fraction a transferer
   * \param Substance& receveur
   * \param SubstanceId Substance a transferer
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
   * \return vrai si identiques a SUBSTANCE_PRECISION pres
   */
	bool operator==(Substance const&) const;

  /** \brief Acces en lecture seule des quantites
   * \param SubstanceId Lla quantite a lire
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

  /** \brief Methode privee responsable de restreindre
   * les valeurs des substances entre SUBSTANCE_PRECISION
   * et substance_max_value
   */
	void normalise();

private:

	static const double cMAX; /**< substance_max_value */

	double cVGEF; /**< quantite de VGEF */
	double cGLU; /**< quantite de glucose */
	double cBMP; /**< quantite de bromopyruvate */
};

/** \brief multiplication par un scalaire
 *
 * \param Substance a multiplier
 * \param scalaire
 */
Substance& operator*(Substance,double);

/** \brief Comparaison entre instances de substance
 * \return l'inverse de l'operateur==
 */
bool operator!=(Substance const&,Substance const&);

/** \brief surcharge de l'operateur de flux pour affichage
 * dans la console
 */
std::ostream& operator<<(std::ostream&, Substance const&);

#endif //I_SUBSTANCE_HPP
