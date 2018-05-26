#ifndef CELLLIVER_HPP
#define CELLLIVER_HPP

#include "CellOrgan.hpp"
#include "Organ.hpp"
#include <Utility/Utility.hpp>


class CellLiver: public CellOrgan
{
	public:

    /** \brief Constructeur
     *
     * \param Pointeur vers la case courante
     * \param valeur initiale d'atp
     */
		CellLiver(CellHandler*,double atp = 100);

    /** \brief Passage du temps, consommation de atp et glucose
     *
     * \param sf::Time Pas de temps
     * \return vrai si en fin de vie
     */
		virtual bool update(sf::Time) override;

    /** \brief Methode de debug affichant a la console
     * la valeur d'atp
     *
     * \return void
     */
		void printAtp() const;

	protected:

    /**
     * \return valeur configuree
     */
		virtual double getFractUptake() const;

    /**
     * \return valeur configuree
     */
		virtual double getKrebsKm() const;

    /**
     * \return valeur configuree
     */
		virtual double getKrebsVmax() const;

    /**
     * \return valeur configuree
     */
		virtual double getGlycoKm() const;

    /**
     * \return valeur configuree
     */
		virtual double getGlycoVmax() const;

    /**
     * \return valeur configuree
     */
		virtual double getFractGlu() const;

    /** \brief Consommation de glucose, creation d'atp
     *
     * \param sf::Time Pas de temps
     * \return void
     */
		virtual void ATPSynthesis(sf::Time dt);

    /** \brief Cycle de Krebs de l'acide citrique
     * (glucose->atp)
     *
     * \param sf::Time Pas de temps
     * \return void
     */
		virtual void Krebs(sf::Time dt);

    /** \brief Glycolyse
     * (glucose->atp)
     *
     * \param sf::Time Pas de temps
     * \return void
     */
		void glycolysis(sf::Time dt);

    /** \brief Division cellulaire
     *
     * \param Type de cellule
     * \return void
     */
		virtual void divide(Organ::Kind k = Organ::Kind::Liver);

	private:

		double atp; /**< Adenosyne tri-phosphate */
};

#endif // CELLLIVER_HPP
