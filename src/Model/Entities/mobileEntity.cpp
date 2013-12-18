/*
 * mobileEntity.cpp
 *
 *  Created on: 4-dec.-2013
 *      Author: Jakob
 */

#include "mobileEntity.h"

namespace Model {

	void MobileEntity::move(Direction dir, int distance) {
		switch (dir) {
		case L:
		    xLoc_ -= distance;
		    break;
        case R:
            xLoc_ += distance;
            break;
        case U:
            yLoc_ -= distance;
            break;
        case D:
            yLoc_ += distance;
            break;
		}
	}
}


