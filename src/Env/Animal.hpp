#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include "SimulatedEntity.hpp"
//#include "Organ.hpp"
class Organ;
#include <Utility/Utility.hpp>
#include <Random/Random.hpp>
#include <Types.hpp>

class Organ;

/** \brief Differents etats possibles de l'animal
 */
enum State
{
	FOOD_IN_SIGHT, // nourriture en vue (il sera attiré par la nourriture)
	FEEDING,       // en train de manger (là en principe il arrête de se déplacer)
	WANDERING,     // déambule
	IDLE           // au repos
};

/** \brief Classe genrale abstraite d'une entite animale
 */
class Animal : public SimulatedEntity /// ABSTRACT
{
	public:

    /** \brief Constructeur
     *
     * \param Vec2d position initiale desiree
     * \param double energie
     * \param sf::Texture* texture SFML
     * \param double rayon
     */
		Animal(Vec2d const& pos, double energy, sf::Texture* texture, double rayon);

    /** \brief Destructeur (nettoie l'organe alloue dynamiquement)
     */
		virtual ~Animal();

    /** \brief Methode d'affichache SFML
     *
     * \param sf::RenderTarget& fenetre a afficher
     * \return void
     */
		virtual void drawOn(sf::RenderTarget&) override;

    /** \brief Passage du temps
     *
     * \param sf::Time Pas de temps
     * \return void
     */
		void update(sf::Time) override;

    /** \brief Met a jour l'etat de l'animal selon sa situation
     * energetique, spatiale, etc...
     *
     * \return void
     */
		void updateState();

    /**
     * \param Box*
     * \return vrai si l'entite est a l'interieur de la boite
     * et que celle-ci n'est pas occuppee
     */
		virtual bool canBeConfinedIn(Box*) const override;

    /** \brief Rend la boite actuelle occuppee
     *
     * \return void
     */
		void fillBox();

    /** \brief Mouvement erratique aleatoire
     *
     * \param sf::Time Pas de temps
     * \return void
     */
		void move(sf::Time);

    /** \brief Mouvement accelere
     *
     * \param Vec2d forcef
     * \param sf::Time Pas de temps
     * \return void
     */
		void move(Vec2d const&,sf::Time);

    /**
     * \return Vecteur de velocite
     */
		Vec2d getSpeedVector() const;

    /** \brief Vitesse maximale sera a definir par les classes derivees
     */
		virtual double getMaxSpeed() const = 0;

    /** \brief La perte d'energie due a l'effort sera a definir
     * par les classes derivees
     */
		virtual double getLossFactor() const = 0;

    /** \brief La masse sera a definir par les classes derivees
     */
		virtual double getMass() const = 0;

    /** \brief Methode de distribution aleatoire du nouvel
     * angle de deambulation
     *
     * \return Angle
     */
		Angle getNewRotation() const;

    /**
     * \return vrai si l'animal n'a plus faim
     */
		bool isSatiated() const;

    /**
     *\return Vec2d force d'attirance vers une cible
     * (ex: nourriture)
     */
		Vec2d getFoodPull() const;

    /** \brief La taille de bouchee sera a definir par les classes derivees
     */
		virtual Quantity getBite() const = 0;

    /** \brief Mange la cible
     *
     * \return void
     */
		void feed();

    /**
     * \return double champ de vision de l'animal
     */
		virtual double getViewRange() const;

    /**
     * \return double portee de vue de l'animal
     */
		virtual double getViewDistance() const;

    /**
     * \param position
     * \return vrai si la position est dans le champ de vision
     */
		bool isTargetInSight(const Vec2d& position);

    /** \brief Fait traquer une entite
     *
     * \param entite a traquer
     * \return void
     */
		void setTarget(SimulatedEntity* a);

    /** \brief Methode d'affichache SFML de l'organe
     *
     * \param sf::RenderTarget& fenetre a afficher
     * \return void
     */
		void drawCurrentOrgan(sf::RenderTarget&);

    /** \brief Passage du temps de l'organe
     *
     * \param sf::Time Pas de temps
     * \return void
     */
    void updateOrgan();

    /** \brief Reaction a la fin de vie d'une entite
     * (ne plus la traquer)
     *
     * \param entite en fin de vie
     * \return void
     */
    virtual void isDead(SimulatedEntity*) override;

    /** \brief Signale a l'organe de changer son type de
     * substance traquee
     *
     * \param type de substance
     * \return void
     *
     */
		void updateCurrentSubstance(SubstanceId const& id);

    /** \brief Donne le cancer a une position particuliere de l'organe
     *
     * \param position
     * \return void
     *
     */
		void setCancerAt(Vec2d const& pos);

    /** \brief Methode de debug permettant d'afficher la teneur en
     * un certain type de substance d'une position specifique de
     * l'organe
     *
     * \param type de substance
     * \param position
     * \return void
     */
		void printSubstanceAt(SubstanceId id, Vec2d const& pos) const;

	protected:

    /** \brief Methode necessaire aux Tests
     */
		virtual void setRotation(Angle a);

    /** \brief Methode necessaire aux Tests
     */
    virtual void setOrgan(Organ*o);

	private:

		State etat; /**< Type enumere : etat actuel de l'animal */

		static Intervals intervals; /**< Intervales necessaires a la generation aleatoire de nouveaux angles */
		static Probs probs; /**< Probabilites liees aux intevales */

		double AngleVision; /**< Champ de vision */
		double DistanceVision; /**< Portee de vision */
		double velocite; /**< Norme de la vitesse de l'animal */
		sf::Time compteur; /**< Horloge interne de l'animal */

		SimulatedEntity* cible_actuelle; /**< Cible (esperons nutritive) actuelle de l'animal */

		Organ* foie; /**< organe simule de l'animal */
};

#endif // ANIMAL_HPP
