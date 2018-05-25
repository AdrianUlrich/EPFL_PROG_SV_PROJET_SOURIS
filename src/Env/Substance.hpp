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
   * \param cVGEF quantit� de VGEF
   * \param cGLU quantit� de glucose
   * \param cBMP quantit�� de bromopyruvate
   */
  Substance(double cVGEF, double cGLU, double cBMP);

  /** \brief Constructeur par d�faut initialisant
   * les concentrations � z�ro
   */
	Substance();

  /** \brief Constructeur de copie par d�faut
   */
	Substance(const Substance& sub) = default;

  /** \brief Op�rateur d'assignement par d�faut
   *
   * \param Substance � assigner
   * \return L'instance assign�e
   */
	Substance& operator=(Substance const&) = default;

  /** \brief Destructeur par d�faut
   */
	~Substance() = default;

  /**
   * \param precision (par d�faut SUBSTANCE_PRECISION)
   * \return vrai si les quantit�s sont nulles
   */
	bool isNull(double precision = SUBSTANCE_PRECISION);

  /** \brief Multiplie la valeur d'une concentration
   * sp�cifi�e
   *
   * \param SubstanceId La substance � modifier
   * \param scalaire Le param�tre de modification
   * (Si 0, annule toutes les quantit�s)
   * \return void
   */
	void update(SubstanceId,double scalaire);

  /** \brief Prend une fraction d'une concentration de
   * l'instance courante et la donne � une autre
   * instance
   *
   * Si la quantit� � transf�rer est inf�rieure �
   * SUBSTANCE_PRECISION, on ne transf�re pas
   *
   * \param double fraction � transf�rer
   * \param Substance& receveur
   * \param SubstanceId Substance � transf�rer
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
   * \return vrai si identiques � SUBSTANCE_PRECISION pr�s
   */
	bool operator==(Substance const&) const;

  /** \brief Acc�s en lecture seule des quantit�s
   * \param SubstanceId Lla quantit� � lire
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

  /** \brief M�thode priv�e responsable de restreindre
   * les valeurs des substances entre SUBSTANCE_PRECISION
   * et substance_max_value
   */
	void normalise();

private:

	static const double cMAX; /**< substance_max_value */

	double cVGEF; /**< quantit� de VGEF */
	double cGLU; /**< quantit� de glucose */
	double cBMP; /**< quantit� de bromopyruvate */
};

/** \brief multiplication par un scalaire
 *
 * \param Substance � multiplier
 * \param scalaire
 */
Substance& operator*(Substance,double);

/** \brief Comparaison entre instances de substance
 * \return l'inverse de l'op�rateur==
 */
bool operator!=(Substance const&,Substance const&);

/** \brief surcharge de l'op�rateur de flux pour affichage
 * dans la console
 */
std::ostream& operator<<(std::ostream&, Substance const&);

#endif //I_SUBSTANCE_HPP

/** \brief Conteneur pour substances et methodes
 * utillitaires pour leur manipulation
 */
class Substance
{
public:

  /** \brief Constructeur utilisant des concentrations
   * initiales
   *
   * \param cVGEF quantit� de VGEF
   * \param cGLU quantit� de glucose
   * \param cBMP quantit�� de bromopyruvate
   */
  Substance(double cVGEF, double cGLU, double cBMP);

  /** \brief Constructeur par d�faut initialisant
   * les concentrations � z�ro
   */
	Substance();

  /** \brief Constructeur de copie par d�faut
   */
	Substance(const Substance& sub) = default;

  /** \brief Op�rateur d'assignement par d�faut
   *
   * \param Substance � assigner
   * \return L'instance assign�e
   */
	Substance& operator=(Substance const&) = default;

  /** \brief Destructeur par d�faut
   */

  /**
   * \param precision (par d�faut SUBSTANCE_PRECISION)
   * \return vrai si les quantit�s sont nulles
   */
	bool isNull(double precision = SUBSTANCE_PRECISION);

  /** \brief Multiplie la valeur d'une concentration
   * sp�cifi�e
   *
   * \param SubstanceId La substance � modifier
   * \param scalaire Le param�tre de modification
   * (Si 0, annule toutes les quantit�s)
   * \return void
   */
	void update(SubstanceId,double scalaire);

  /** \brief Prend une fraction d'une concentration de
   * l'instance courante et la donne � une autre
   * instance
   *
   * Si la quantit� � transf�rer est inf�rieure �
   * SUBSTANCE_PRECISION, on ne transf�re pas
   *
   * \param double fraction � transf�rer
   * \param Substance& receveur
   * \param SubstanceId Substance � transf�rer
   *
   * \return void
   */
	void uptakeOnGradient(double c,Substance&,SubstanceId);
  /**
   * \return Fraction de VGEF
   */

  /**
   * \return Fraction de glucose
   */

  /**
   * \return Fraction de bromopyruvate
   */

  /**
   * \return Concentration totale
   */
  /** \brief Comparaison entre instances Substance
   * \return vrai si identiques � SUBSTANCE_PRECISION pr�s
   */

  /** \brief Acc�s en lecture seule des quantit�s
   * \param SubstanceId Lla quantit� � lire
   */
	double const& operator[](SubstanceId) const;

  /** \brief Addition entre instances Substance
   */

  /** \brief Soustraction entre instances Substance
   */

  /** \brief Multiplication d'une substance par un scalaire
   */

  /** \brief M�thode priv�e responsable de restreindre
   * les valeurs des substances entre SUBSTANCE_PRECISION
   * et substance_max_value
   */
private:

	static const double cMAX; /**< substance_max_value */

	double cVGEF; /**< quantit� de VGEF */
	double cGLU; /**< quantit� de glucose */
	double cBMP; /**< quantit� de bromopyruvate */
/** \brief multiplication par un scalaire
 *
 * \param Substance � multiplier
 * \param scalaire
 */
Substance& operator*(Substance,double);

/** \brief Comparaison entre instances de substance
 * \return l'inverse de l'op�rateur==
 */
bool operator!=(Substance const&,Substance const&);

/** \brief surcharge de l'op�rateur de flux pour affichage
 * dans la console
 */