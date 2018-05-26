#ifndef I_LAB_HPP
#define I_LAB_HPP

#include <SFML/Graphics.hpp>

#include <vector>
#include <Utility/Vec2d.hpp>
#include <Types.hpp>
#include "Cheese.hpp"
#include "Box.hpp"
#include "Mouse.hpp"
#include "Animal.hpp"
using std::vector;

/** \brief Classe contenant la majorite des objets de la simulation
 * ainsi que des methodes d'interface
 */
class Lab final : public sf::NonCopyable
{
	public:

		/** \brief Constructeur par defaut
		 * utilisant \fn makeboxes()
		 */
		Lab();

    /** \brief Destructeur responsable de nettoyer les objets
     * alloues dynamiquement
     * \brief appelle destroyBoxes()
     */
		~Lab();

    /** \brief Methode responsable de remplir le Lab de boites
     * \brief appelle destroyBoxes()
     *
     * \param nbCagesPerRow nombre de boites par colonne/ligne
     * \return void
     */
		void makeBoxes(unsigned int nbCagesPerRow);

    /** \brief Nettoie les boites (allouees dynamiquement)
     *
     * \return void
     */
		void destroyBoxes();

    /** \brief Implemente le passage du temps egalement parmi ses entites
     *
     * \param sf::Time Pas de temps
     * \return void
     */
		void update(sf::Time dt);

    /** \brief Methode d'affichache SFML
     *
     * \param sf::RenderTarget& fenetre a afficher
     * \return void
     */
		void drawOn(sf::RenderTarget&);

    /** \brief Nettoie le Lab de ses entites
     *
     * \return void
     */
		void reset();

    /** \brief Permet d'ajouter un Fromage au Lab
     *
     * \param Cheese* pointeur a allouer dynamiquement en dehors de la classe
     * \return vrai si succes
     */
		bool addCheese(Cheese*);

    /** \brief Permet d'ajouter une Souris au Lab
     *
     * \param Animal* pointeur a allouer dynamiquement en dehors de la classe
     * \return vrai si succes
     */
		bool addAnimal(Animal*);

    /** \brief Le Lab se concentre sur l'animal pointe
     *
     * \param Animal*
     * \return void
     */
		void trackAnimal(Animal* n);

    /** \brief Recherche un animal a la position donnee et le traque si trouve
     *
     * \param Vec2d position
     * \return void
     */
		void trackAnimal(const Vec2d&);

    /** \brief Permet l'entree en vue Organe
     *
     * \param View
     * \return void
     */
		void switchToView(View view);

    /** \brief Arrete de traquer l'entite traquee
     *
     * \return void
     */
		void stopTrackingAnyEntity();

    /** \brief Appelle la fonction update de l'animal traque
     * (utile pour la vision interne)
     *
     * \return void
     */
		void updateTrackedAnimal();

    /** \brief Methode passant la fenetre d'affichage a l'organe
     * de l'entite traquee pour lui permettre de s'y afficher
     *
     * \param sf::RenderTarget& fenetre d'affichage
     * \return void
     */
		void drawCurrentOrgan(sf::RenderTarget& target);

    /** \brief Partmet a un animal d'avoir acces a toutes
     * les entites dans son champ de vision
     * (l'animal est libre de traiter cette information comme bon lui semble)
     *
     * \param pointeur vers l'Animal desirant sa vision
     * \return ensemble des entites dans le champ de vision
     */
		vector<SimulatedEntity*>* findTargetsInSightOf(Animal*);

    /**
     * \return Le delta de la substance specifiee
     */
		double getDelta(SubstanceId) const;

    /**
     * \return Le substance actuellement traquee
     */
		SubstanceId getCurrentSubst() const;

    /** \brief Fait passer la substance traquee a la suivante
     */
		SubstanceId nextSubstance();

    /** \brief Augmente le delta de la substance traquee
     *
     * \return void
     */
		void increaseCurrentSubst();

    /** \brief Rabaisse le delta de la substance traquee
     *
     * \return void
     */
		void decreaseCurrentSubst();

    /** \brief Permet l'application locale d'une tumeur a
     * l'organe de l'animal traque
     *
     * \param position dans l'organe
     * \return void
     */
		void setCancerAt(Vec2d const& pos);

    /** \brief Methode utilitaire affichant a la console le
     * niveau d'une substance specifiee a une position specifiee
     *
     * \param pos Vec2d const&
     * \return void
     *
     */
		void printSubstanceAt(Vec2d const& pos) const;

	private:

    /** \brief Methode privee responsable d'ajouter les entites a
     * leur ensemble
     *
     * \param SimulatedEntity*
     * \return vrai si succes
     */
		bool addEntity(SimulatedEntity*);

		vector<vector<Box*>> boites; /**< Ensemble des boites du labo */

		vector<Animal*> animals; /**< Ensemble des animaux */
		vector<Cheese*> cheeses; /**< Ensemble des fromages */
		vector<SimulatedEntity*> NTTs; /**< Ensemble des entites */
		Animal* tracked; /**< L'animal traque */
		sf::Sprite* cross; /**< Icone s'affichant sur l'animal traque */

		SubstanceId currentSubstance; /**< Substance actuellement traquee */
		double deltaGlucose; /**< Gradient de glucose */
		double deltaBromo; /**< Gradient de bromopyruvate */
		double deltaVGEF; /**< Gradient de VGEF */
};

#endif //I_LAB_HPP
