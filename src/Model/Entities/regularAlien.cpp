/*
 * regularAlien.cpp
 *
 *  Created on: 4-dec.-2013
 *      Author: Jakob Struye
 */

#include "regularAlien.h"
#include "alienBullet.h"


namespace Model {
	Bullet* RegularAlien::shoot() {
		//Shoot from top middle of RegularAlien
        AlienBullet* bullet = dynamic_cast<AlienBullet*>
        	(bulletFactory_->getEntity((xLoc_ + (0.5 * xSize_)), yLoc_, 30));
	    return bullet;
	}


    bool RegularAlien::collidesWith(Entity* entity) {
    	//Check if it hit anything
    	if (!Entity::collidesWith(entity))
    		return false;
    	//If it something other than a Bullet, it flew into something
    	if (!dynamic_cast<Bullet*>(entity))
    		collidedWithSomething_ = true;
    	return true;
    }

    bool RegularAlien::collidedWithSomething() const {return collidedWithSomething_; }
}


