/*
 * concreteEntityFactories.cpp
 *
 *  Created on: 17-dec.-2013
 *      Author: Jakob
 */

#include "concreteEntityFactories.h"
#include "../Entities/alienBullet.h"
#include "../Entities/bonusAlien.h"
#include "../Entities/playerBullet.h"
#include "../Entities/playerShip.h"
#include "../Entities/regularAlienTypes.h"
#include "../Entities/shield.h"

namespace Factory {

	Model::Entity* AlienBulletFactory::getEntity(int xSize, int ySize, int relativeSize) {
		return new Model::AlienBullet(xSize, ySize, relativeSize);
	}


	Model::Entity* BonusAlienFactory::getEntity(int xSize, int ySize, int relativeSize) {
		return new Model::BonusAlien(xSize, ySize, relativeSize);
	}


	Model::Entity* PlayerBulletFactory::getEntity(int xSize, int ySize, int relativeSize) {
		return new Model::PlayerBullet(xSize, ySize, relativeSize);
	}


	Model::Entity* PlayerShipFactory::getEntity(int xSize, int ySize, int relativeSize) {
		return new Model::PlayerShip(xSize, ySize, relativeSize);
	}


	Model::Entity* RegularAlienBotFactory::getEntity(int xSize, int ySize, int relativeSize) {
		return new Model::RegularAlienBot(xSize, ySize, relativeSize);
	}


	Model::Entity* RegularAlienMidFactory::getEntity(int xSize, int ySize, int relativeSize) {
		return new Model::RegularAlienMid(xSize, ySize, relativeSize);
	}


	Model::Entity* RegularAlienTopFactory::getEntity(int xSize, int ySize, int relativeSize) {
		return new Model::RegularAlienTop(xSize, ySize, relativeSize);
	}


	Model::Entity* ShieldFactory::getEntity(int xSize, int ySize, int relativeSize) {
		return new Model::Shield(xSize, ySize, relativeSize);
	}
}
