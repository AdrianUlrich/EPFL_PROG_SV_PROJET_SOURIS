#ifndef CELLECM_HPP
#define CELLECM_HPP

#include "CellOrgan.hpp"

/** \brief Matrice extra-cellulaire pourrait etre resume
 * par typedef CellOrgan CellECM;
 */
class CellECM: public CellOrgan
{
	public:
    /** \brief Constructeur de CellOrgan
     */
    using CellOrgan::CellOrgan;
};

#endif // CELLECM_HPP
