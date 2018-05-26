#ifndef MOUSE_HPP
#define MOUSE_HPP

#include "Animal.hpp"

/** \brief Entite Animale de type Souris
 */
class Mouse : public Animal
{
	public:

    /** \brief Constructeur
     *
     * \param position initiale desiree de la souris
     */
		Mouse(Vec2d const&);

    /** \brief Methode d'affichache SFML
     *
     * \param sf::RenderTarget& fenetre a afficher
     * \return void
     */
		void drawOn(sf::RenderTarget&) override;

    /** \brief On peut enfin definir des facteurs de
     * fin de vie specifiques aux souris
     *
     * \return vrai si en fin de vie
     */
		virtual bool isDead() const override;

    /**
     * \return vrai si l'entite est mangeable par une souris
     */
		bool eatable(SimulatedEntity const* ntt) const override;

		/**
		 * \return faux car les fromages ne mangent pas de souris
		 */
		bool eatableBy(Cheese const*) const override;

		/**
		 * \return faux car les souris ne mangent pas de souris
		 */
		bool eatableBy(Mouse const*) const override;

    /** \brief definition de la vitesse maximale d'une souris
     */
		virtual double getMaxSpeed() const override;

    /** \brief definition du facteur de pertes d'energie dues
     * a l'effort d'une souris
     */
		virtual double getLossFactor() const override;

    /** \brief definition du poids d'une souris
     */
		virtual double getMass() const override;

    /** \brief definition de la taille de bouchées d'une souris
     */
		virtual Quantity getBite() const override;

};

#endif // MOUSE_HPP
