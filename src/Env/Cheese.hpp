#ifndef CHEESE_HPP
#define CHEESE_HPP

#include "SimulatedEntity.hpp"


/** \brief Entite de type Fromage
 */
class Cheese : public SimulatedEntity
{
	public:
    /** \brief Constructeur
     *
     * \param position initiale desiree du fromage
     */
    Cheese(Vec2d const&);

    /** \brief Methode d'affichache SFML
     *
     * \param sf::RenderTarget& fenetre a afficher
     * \return void
     */
		void drawOn(sf::RenderTarget&) override;

    /** \brief Le fromage se fait manger
     *
     * \param quantite d'energie demandee
     * \return quantite d'energie donnee
     */
		virtual Quantity provideEnergy(Quantity) override;

    /** \brief Masquage de isDead() pour devenir instanciable
     * (le fromage pourrait finir moisi)
     *
     * \return vrai si perime
     */
		bool isDead() const override;

		/**
		 * \return vrai si l'entite est mangeable par un fromage
		 */
		bool eatable(SimulatedEntity const* ntt) const override;

		/**
		 * \return faux car les fromages ne mangent pas de fromage
		 */
		bool eatableBy(Cheese const*) const override;

		/**
		 * \return vrai car les souris mangent des fromages
		 */
		bool eatableBy(Mouse const*) const override;
};

#endif // CHEESE_HPP
