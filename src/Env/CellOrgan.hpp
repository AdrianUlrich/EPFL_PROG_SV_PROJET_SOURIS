#ifndef CELLORGAN_HPP
#define CELLORGAN_HPP

#include "Substance.hpp"
#include <Utility/Utility.hpp>
class CellHandler;

/** \brief Classe abstraite modelisant une cellule
 */
class CellOrgan
{
	public:

    /** \brief Constructeur
     *
     * \param pointeur vers la case courante
     */
		CellOrgan(CellHandler*);

    /** \brief Destructeur desallouant la Substance
     * allouee dynamiquement
     */
		virtual ~CellOrgan() = 0;

    /** \brief Incremente la subtance
     *
     * \param Substance a recevoir
     * \return void
     */
		void updateSubstance(Substance const&);

    /**
     * \param type de substance
     * \return quantite du type de substance donne
     */
		Quantity getQuantity(SubstanceId) const;

    /** \brief Transfere une fraction de la substance a une
     * substance d'une autre instance de CellOrgan
     *
     * \param fraction
     * \param autre CellOrgan
     * \param type de substance
     * \return void
     */
		void uptakeOnGradient(double,CellOrgan*,SubstanceId);

    /** \brief Passage du temps
     *
     * \param sf::Time Pas de temps
     * \return vrai si la cellule est en fin de vie
     */
		virtual bool update(sf::Time);

	protected:

		Substance* substance; /**< Substance contenue dans la cellule */

		CellHandler* handler; /**< Pointeur vers la case courante */
};

#endif // CELLORGAN_HPP
