/*
 * bonusAlien.cpp
 *
 *  Created on: Dec 15, 2013
 *      Author: Jakob Struye
 */

#include "bonusAlien.h"

namespace Model {

	//BonusAlien can't shoot
    Bullet* BonusAlien::shoot() { return nullptr;}


    int BonusAlien::getScore() {return 100; }


    bool BonusAlien::checkOutOfBounds(int xReso, int yReso) {
    	//Part of BonusAlien must be within [0, xReso] horizontally and [0, yReso] vertically
        if (xLoc_ < (0 - xSize_) || (xLoc_) > xReso || yLoc_ < 0 || (yLoc_ + ySize_) > yReso)
            return true;
        return false;
    }
}
