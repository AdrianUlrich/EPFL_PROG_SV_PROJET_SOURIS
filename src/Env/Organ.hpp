#ifndef ORGAN_HPP
#define ORGAN_HPP

#include "Substance.hpp"

#include <SFML/Graphics.hpp>
#include <Application.hpp>
#include <Utility/Utility.hpp>
#include <Types.hpp>

#include <vector>
using std::vector;

class CellHandler;


/** \brief Classe modeliasnt un orane (ici le foie)
 */
class Organ
{
	public:

    /** \brief Differents types de cellules individuelles
     */
		enum class Kind : short {ECM,Liver,Artery,Capillary,CANCER};

	public:

    /** \brief Constructeur
     *
     * \param si vrsi, l'organe est genere
     */
		Organ(bool generation);

    /** \brief Destructeur polymorphique (desalloue les cellules
     * allouees dynamiquement)
     */
		virtual ~Organ() = default;


    /** \brief Passage du temps
     * Cree le pas de temps necessaire aux objets que Organ contient
     *
     * \return void
     */
		void update();

    /** \brief Methode d'affichache SFML
     *
     * \param sf::RenderTarget& fenetre a afficher
     * \return void
     */
		void drawOn(sf::RenderTarget& target);

    /**
     * \return Largeur de l'organe
     */
		double getWidth() const;

    /**
     * \return Hauteur de l'organe
     */
		double getHeight() const;

    /**
     * \param CellCoord position
     * \return vrai si la position est valide dans l'organe
     */
		bool isOut(CellCoord const&) const;

    /** \brief Convertit une position concrete sf::vector2<float> en
     * position discrete sf::vector2<int>
     *
     * \param Vec2d (sf::vector2<float>)
     * \return CellCoord (sf::vector2<int>)
     */
		virtual CellCoord toCellCoord(Vec2d const&) const;

    /** \brief Rafraichit la representation graphique de l'organe
     *
     * \param si vrai rafraichit aussi la representation de chaque cellule
     * \return void
     */
		void updateRepresentation(bool also_update=true);

    /** \brief Rafraichit la representation d'une cellule specifique
     *
     * \param CellCoord position de la cellule
     * \return void
     */
		virtual void updateRepresentationAt(CellCoord const&);

    /** \brief Donne une subtance a la partie ECM d'une cellule
     *
     * \param CellCoord position de la cellule
     * \param Substance a donner a la cellule
     * \return void
     */
		void updateCellHandlerAt(CellCoord const&, Substance const&);

    /** \brief Acces a la concentration d'une substance d'une cellule
     *
     * \param CellCoord position
     * \param SubstanceId type de substance
     * \return double concentration
     */
		double getConcentrationAt(CellCoord const&,SubstanceId) const;

    /** \brief Modifie le type de substance actuellement traque
     *
     * \param SubstanceId type de substance a traquer
     * \return void
     */
		void setSubstance(SubstanceId const& id);

    /** \brief Applique une cellule de cancer a une position specifiee
     *
     * \param Vec2d position
     * \return void
     */
		void setCancerAt(Vec2d const& pos);

    /** \brief Methode de debug affichant sur la console la quantite
     * d'une substance donnee a une position donnee
     *
     * \param SubstanceId type de substance
     * \param Vec2d position
     * \return void
     */
		void printSubstanceAt(SubstanceId id, Vec2d const& pos) const;

    /** \brief Assigne un certain type de cellule a une position donnee
     *
     * \param CellCoord position
     * \param Kind type de cellule
     * \return vrai si succes
     */
		bool propagate(CellCoord const&,Kind);

	protected:

    /** \brief Genere l'organe
     * (appelle createLiver et createBloodSystem entre autres)
     *
     * \return void
     */
		virtual void generate();

    /** \brief Methode responsable de redimensionner l'organe selon
     * la configuration
     *
     * \return void
     */
		void reloadConfig();

    /** \brief Rafraichissement des ensembles de sommets des cellules
     *
     * \return void
     */
		void reloadCacheStructure();

    /** \brief Creation du foie delimite par deux arcs de cercles
     * partant des coins bas-gauche, haut-droite
     *
     * \return void
     */
		void createLiver();

    /** \brief Genere le reseau sanguin (artere et capillaires)
     *
     * \param generateCapillaries=true bool
     * \return void
     *
     */
		void createBloodSystem(bool generateCapillaries=true);

    /** \brief Genere l'artere entre deux abcisses
     *
     * \param limite de gauche
     * \param limite de droite
     * \return void
     */
		virtual void generateArtery(int,int);

    /** \brief Progression de la creation du capillaire
     *
     * \param CellCoord position actuelle de la progression du capillaire
     * \param CellCoord dierection de la progression du capillaire
     * \param nombre de cellules du capillaire deja creees
     * \param nombre maximal de cellules que le capillaire pourra creer
     * \return vrai si cellule de capillaire creee avec succes
     */
		virtual bool generateCapillaryOneStep(CellCoord& p, CellCoord const& dir, int& NBcells, int const& maxLength);

    /** \brief Cree un capillaire en appellant generateCapillaryOneStep
     *
     * \param position initiale
     * \param direction
     * \return void
     */
		virtual void generateCapillaryFromPosition(CellCoord& p, CellCoord dir);

    /** \brief Applique un type de cellule donne a une case donnee
     *
     * \param CellCoord position
     * \param type de cellule
     * \return vrai
     */
		virtual bool updateCellHandler(CellCoord const&,Kind);

	private:

    /** \brief Applique les textures de cellules sur
     * le cache de representation
     *
     * \return void
     */
		void drawRepresentation();

    /** \brief Methode de debug affichanta la console la moyenne
     * des concentrations d'une substance donnee dans l'organe
     *
     * \param type de substance
     * \return void
     */
		void printAvgSubst(SubstanceId id) const;

	private:
		int nbCells; /**< Nombre de cellules par ligne/colonne */
		float cellSize; /**< Taille du cote d'une cellule */
		sf::RenderTexture renderingCache; /**< Cache de representation */
		vector<vector<CellHandler*>> cellHandlers; /**< Ensemble des cellules */
		vector<sf::Vertex> bloodVertexes; /**< Sommets de representation des cellules sanguines */
		vector<sf::Vertex> liverVertexes; /**< Sommets de representation des cellules hepatiques */
		vector<sf::Vertex> concentrationVertexes; /**< Sommets de representation des concentrations */
		vector<sf::Vertex> cancerVertexes; /**< Sommets de representation des cellules hepatiques cancereuses */

		SubstanceId currentSubst; /**< Type de substance actuellement traque */
};

#endif // ORGAN_HPP
