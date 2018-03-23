//#include "Cheese.hpp"
//#include <Application.hpp>
//#include <algorithm>
//
//Cheese::Cheese()
//: texture(getAppConfig().cheese_texture),
//	energy(getAppConfig().cheese_initial_energy)
//	entitySprite
//	(
//		buildSprite
//		(
//			pos,
//			energy,
//			texture
//		)
//	),
//	maxSide(std::max(texture.getSize().x, texture.getSize().y)
//{}
//
//void Cheese::drawOn(sf::RenderTarget& target)
//{
//	//SimulatedEntity::drawOn(target);
//	entitySprite.setScale(Vec2d(energy,energy)/maxSide);
//	entitySprite.setRotation(angle/ DEG_TO_RAD);
//	target.draw(entitySprite);
//}
