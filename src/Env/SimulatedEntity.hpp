#ifndef SIMULATEDENTITY_HPP
#define SIMULATEDENTITY_HPP

#include <SFML/Graphics.hpp>
#include <Utility/Utility.hpp>
#include "Box.hpp"
#include "Collider.hpp"
#include <Utility/Vec2d.hpp>
#include <vector>
using std::vector;

class Mouse;
class Cheese;


/** \brief Classe generale abstraite representant
 * une entite et ses caracteristiques
 */
class SimulatedEntity : public Collider /// ABSTRACT
{
	public:

    /** \brief Constructeur
     *
     * \param Vec2d position initiale desiree
     * \param double energie
     * \param sf::Texture* texture SFML
     * \param double rayon
     *
     */
		SimulatedEntity(Vec2d const& pos, double energy, sf::Texture* texture, double rayon);

    /** \brief Methode d'affichache SFML
     *
     * \param sf::RenderTarget& fenetre a afficher
     * \return void
     */
		virtual void drawOn(sf::RenderTarget&);

    /** \brief Passage du temps
     *
     * \param sf::Time Pas de temps
     * \return void
     */
		virtual void update(sf::Time);

    /**
     * \return vrai si l'entite est en fin de vie pour
     * des raisons specifiees par les classes derivees
     */
		virtual bool isDead() const = 0;

    /** \brief Surcharge de isDead permettant a l'entite
     * de savoir qu'une autre entite est en fin de vie
     *
     * \param SimulatedEntity*
     * \return virtual void
     *
     */
		virtual void isDead(SimulatedEntity*);

    /** \brief Redefinition de methode de Collider
     * \return centre du Collider de l'entite
     */
		Vec2d getCenter() const override;

    /** \brief Redefinition de methode de Collider
     * \return rayon du Collider de l'entite
     */
		double getRadius() const override;

    /**
     * \param Box*
     * \return vrai si l'entite est a l'interieur de la boite
     */
		virtual bool canBeConfinedIn(Box*) const;

    /** \brief Pseudo test de type
     * \return vrai si l'entite est mangeable pour l'instance courante
     */
		virtual bool eatable(SimulatedEntity const*) const = 0;

    /** \brief Pseudo test de type
     * \return vrai si l'instance courante est mangeable pour une souris
     */
		virtual bool eatableBy(Mouse const*) const = 0;

    /** \brief Pseudo test de type
     * \return vrai si l'instance courante est mangeable pour du fromage
     */
		virtual bool eatableBy(Cheese const*) const = 0;

    /** \brief Methode pour que l'instance courante se fasse manger
     *
     * \param quantite d'energie demandee
     * \return quantite d'energie donnee
     */
		virtual Quantity provideEnergy(Quantity);

    /** \brief Assigne a l'entite une boite
     *
     * \param Box* boite
     * \return void
     */
    void confineInBox(Box* b);

    /**
     * \return Vec2d unitaire corresponadnt a l'angle actuel de l'entite
     */
		virtual Vec2d getHeading() const;

    /** \brief Destructeur polymorphique
     */
		virtual ~SimulatedEntity() = default;

    /** \brief Rend la boite actuelle inoccupee
     * \return void
     */
		void resetBox();

    /** \brief Ajuste la position de l'entite dans la boite
     *
     * \param Box* boite
     * \return void
     */
		void confine(Box*);

	protected:

		Vec2d pos; /**< Position actuelle */
		double entity_size; /**< Taille actuelle de l'entite */
		Angle angle; /**< Angle actuel de l'entite */

		Box* box; /**< Boite actuelle de l'entite */

		double energy; /**< Energie disponible a ou dans l'entite */
		sf::Time age; /**< Age de l'entite */
		sf::Time longevity; /**< Age maximum de l'entite */

		sf::Texture* texture; /**< Texture SFML */
		sf::Sprite entitySprite; /**< Representation de l'entite */
		sf::Text text; /**< Texte de debug de l'entite */

};

#endif // SIMULATEDENTITY_HPP
