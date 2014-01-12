/*
 * playerShip.cpp
 *
 *  Created on: 4-dec.-2013
 *      Author: Jakob Struye
 */

#include "playerShip.h"
#include "playerBullet.h"

namespace Model {


	Bullet* PlayerShip::shoot() {
		//Shoot PlayerBullet from top middle of PlayerShip
        PlayerBullet* bullet = dynamic_cast<PlayerBullet*>
        	(bulletFactory_->getEntity((xLoc_ + (0.5 * xSize_)), yLoc_, 20));
        return bullet;
	}
}


