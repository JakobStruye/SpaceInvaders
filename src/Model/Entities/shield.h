/*
 * Shield.h
 *
 *  Created on: Dec 2, 2013
 *      Author: Jakob Struye
 */

#ifndef SHIELD_H_
#define SHIELD_H_



#include "entity.h"

namespace Model {

    /**
     * Class representing a shield
     */
    class Shield : public Entity {
    public:
        /**
         * @brief Constructor
         *
         * @param xLoc Horizontal location of left side of Shield
         * @param yLoc Vertical location of top of Shield
         * @param relativeSize size of the longest side
         * @param maxHP Starting HP
         */
        Shield(int xLoc, int yLoc, int relativeSize) :
        	Entity(xLoc, yLoc, relativeSize, 0.75 * relativeSize, 5) {}
    };

}

#endif /* SHIELD_H_ */
