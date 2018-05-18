#include "CellOrgan.hpp"
#include "CellHandler.hpp"

CellOrgan::CellOrgan(CellHandler* h)
	:	substance(new Substance(0,0,0))
	,	handler(h)
{}

CellOrgan::~CellOrgan()
{delete substance;}

void CellOrgan::updateSubstance(Substance const& s)
{substance->operator+=(s);}

Quantity CellOrgan::getQuantity(SubstanceId id) const
{return substance->operator[](id);}

void CellOrgan::uptakeOnGradient(double fract,CellOrgan* other,SubstanceId id)
{substance->uptakeOnGradient(fract,*(other->substance),id);}
