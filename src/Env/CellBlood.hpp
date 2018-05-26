#ifndef CELLBLOOD_HPP
#define CELLBLOOD_HPP

#include "CellOrgan.hpp"
#include <Types.hpp>

/** \brief Cellule sanguine
 */
class CellBlood: public CellOrgan
{
	public:

    /** \brief Constructeur
     *
     * \param pointeur vers la case courante
     * \param type de cellule sanguine
     */
		CellBlood(CellHandler*,TypeBloodCell t=ARTERY);

    /** \brief Passage du temps, diffusion de substances
     * aux cellules voisines
     *
     * \param sf::Time Pas de temps
     * \return vrai si en fin de vie
     */
		virtual bool update(sf::Time) override;

    /**
     * \return type de cellule sanguine (artere/capillaire)
     */
		TypeBloodCell getType() const;

	private:

		TypeBloodCell type; /**< Type de cellule sanguine */
};

#endif // CELLBLOOD_HPP
