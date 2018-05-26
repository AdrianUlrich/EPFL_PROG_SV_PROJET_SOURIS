#ifndef CELLLIVERCANCER_HPP
#define CELLLIVERCANCER_HPP

#include "CellLiver.hpp"

/** \brief Cellule de cancer hepatique
 */
class CellLiverCancer : public CellLiver
{
	public:
    /** \brief Constructeur de CellLiver
     */
		using CellLiver::CellLiver;

	protected:

    /**
     * \return redefinition de valeur configuree
     */
		virtual double getFractUptake() const override;

    /**
     * \return redefinition de valeur configuree
     */
		virtual double getGlycoKm() const override;

    /**
     * \return redefinition de valeur configuree
     */
		virtual double getGlycoVmax() const override;

    /**
     * \return redefinition de valeur configuree
     */
		virtual double getFractGlu() const override;

    /**
     * \return redefinition de valeur configuree
     */
		virtual double getDivisionEnergy() const override;

    /** \brief Cycle de Krebs inactif pour la cellule cancereuse
     */
		virtual void Krebs(sf::Time) override;
    //virtual void ATPSynthesis(sf::Time dt) override; // NON-MODIFIE
		//virtual bool update(sf::Time) override; // NON-MODIFIE

    /** \brief Division Cellulaire
     *
     * \return virtual void
     */
    virtual void divide(Organ::Kind) override;
};

#endif // CELLLIVERCANCER_HPP
