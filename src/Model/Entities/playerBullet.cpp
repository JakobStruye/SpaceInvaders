/*
 * PlayerBullet.cpp
 *
 *  Created on: Dec 15, 2013
 *      Author: Jakob Struye
 */

#include "playerBullet.h"
#include "playerShip.h"


namespace Model {

    bool PlayerBullet::collidesWith(Entity* that) {
    	//PlayerBullets can't hit other PlayerBullets or PlayerShips
        if (dynamic_cast<const PlayerBullet*>(that) || dynamic_cast<const PlayerShip*>(that))
            return false;
        else
            return Entity::collidesWith(that);

    }
}


