/*
 * alienBullet.cpp
 *
 *  Created on: Dec 15, 2013
 *      Author: Jakob Struye
 */


#include "alienBullet.h"
#include "regularAlien.h"


namespace Model {

    bool AlienBullet::collidesWith(Entity* that) {
    	//AlienBullets can't hit other AlienBullets or RegularAliens
        if (dynamic_cast<const AlienBullet*>(that) || dynamic_cast<const RegularAlien*>(that))
            return false;
        else
            return Entity::collidesWith(that);

    }

}
