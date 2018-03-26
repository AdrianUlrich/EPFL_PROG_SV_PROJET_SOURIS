#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include "SimulatedEntity.hpp"


class Animal : public SimulatedEntity
{
	public:
		/** constructor */
		Animal(Vec2d const& pos, double energy, sf::Texture texture);
};

#endif // ANIMAL_HPP
