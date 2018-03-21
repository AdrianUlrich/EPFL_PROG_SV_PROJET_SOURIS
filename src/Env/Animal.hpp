#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include "SimulatedEntity.hpp"


class Animal : public SimulatedEntity
{
	public:
		/** constructor */
		Animal(Vec2d pos, double energy);
};

#endif // ANIMAL_HPP
