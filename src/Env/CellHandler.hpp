#ifndef CELLHANDLER_HPP
#define CELLHANDLER_HPP

#include <Utility/Utility.hpp>
#include "Types.hpp"
#include "Substance.hpp"
#include "Organ.hpp"
class CellECM;
class CellBlood;
class CellLiver;


/** \brief Classe d'emballage d'une case de cellules
 */
class CellHandler final
{
	public:

    /** \brief Constructeur
     *
     * \param position dans l'organe
     * \param pointeur a l'organe courant
     */
		CellHandler(CellCoord,Organ*);

    /** \brief Destructeur responsable de
     * desallouer les cellules allouees dynamiquement
     */
		~CellHandler();

    /**
     * \return CellCoord position dans l'organe
     */
		CellCoord getPos() const;

    /** \brief methode non utilisee
     * car brise l'encapsulation
     * \return pointeur a l'organe courant
     * \deprecated
     */
		Organ* getOrgan() const;

    /**
     * \return vrai si possede un ECM
     */
		bool hasECM() const;

    /**
     * \return vrai si possede une cellule hepatique
     */
		bool hasLiver() const;

    /**
     * \return vrai si possede une cellule sanguine
     */
		bool hasBlood() const;

    /**
     * \return vrai si a le cancer
     */
		bool hasCancer() const;

    /** \brief Cree une cellule ECM
     *
     * \return vrai si succes
     */
		bool setECM();

    /** \brief Cree une cellule hepatique
     *
     * \return vrai si succes
     */
		bool setLiver();

    /** \brief Cree une cellule sanguine
     *
     * \return vrai si succes
     */
		bool setBlood(TypeBloodCell);

    /** \brief Cree une cellule Cancereu
     * (supplante cellule hepatique si presente)
     *
     * \return vrai si succes
     */
		bool setCANCER();

    /** \brief Donne une subtance a la partie ECM
     *
     * \param Substance a donner a la cellule
     * \return void
     */
		void updateSubstance(Substance const&);

    /**
     * \param type de substance
     * \return quantite de la substance dans ECM
     */
		Quantity getECMQuantity(SubstanceId) const;

    /**
     * \param type de substance
     * \return quantite de la substance dans cellule hepatique
     */
		Quantity getLiverQuantity(SubstanceId) const;

    /**
     * \param type de substance
     * \return quantite de la substance dans cellule sanguine
     */
		Quantity getBloodQuantity(SubstanceId) const;

    /** \brief Transfere une fraction d'un type de substance
     * de l'ECM a la cellule hepatique
     *
     * \param type de substance
     * \param fraction
     * \return void
     */
		void liverTakeFromEcm(SubstanceId,double fract);

    /** \brief Transfere une fraction d'un type de substance
     * de l'ECM a la cellule sanguine
     *
     * \param type de substance
     * \param fraction
     * \return void
     */
		void bloodTakeFromEcm(SubstanceId,double fract);

    /**
     * \param CellCoord position
     * \return vrai si la position est valide dans l'organe
     */
		bool isOut(CellCoord const&);


    /** \brief Passage du temps
     *
     * \param sf::Time Pas de temps
     * \return vrai si il y a eu un changement dans la cellule
     */
		bool update(sf::Time);

    /** \brief Acces a la methode correspondante dans l'organe
     *
     * \param CellCoord position
     * \param Substance
     * \return void
     */
		void updateCellHandlerAt(CellCoord const&, Substance const&);

    /** \brief Acces a la methode correspondante dans l'organe
     *
     * \param CellCoord position
     * \param Organ::Kind type de cellule
     * \return vrai si succes
     */
		bool updateCellHandlerAt(CellCoord const&, Organ::Kind);

    /** \brief Methode de debug permettant d'afficher a la console
     * le niveau d'atp dans la cellule hepatique
     *
     * \return void
     */
    void printAtp() const;

	private:

		CellCoord pos; /**< Position dans l'organe */
		Organ* organ; /**< Organe courant */

		CellECM* ecm; /**< Matrice extra-cellulaire */
		CellLiver* liver; /**< Cellule hepatique */
		CellBlood* blood; /**< Cellule sanguine */

		bool cancer; /**< A le cancer */
};

#endif // CELLHANDLER_HPP
