/*
 * alienBullet.h
 *
 *  Created on: Dec 2, 2013
 *      Author: jakob
 */

#ifndef ALIENBULLET_H_
#define ALIENBULLET_H_

#include "bullet.h"

namespace Model {

    /**
     * Class representing bullet shot by a RegularAlien
     */
    class AlienBullet : public Bullet {
    public:
        /**
         * @brief Constructor
         *
         * @param xLoc Horizontal location of left side of AlienBullet
         * @param yLoc Vertical location of top of AlienBullet
         * @param relativeSize size of the longest side
         */
        AlienBullet(int xLoc, int yLoc, int relativeSize) :
           Bullet(xLoc, yLoc, 0.2 * relativeSize, relativeSize, 1, D) {}


        /**
         * @brief Checks if AlienBullet collides with another
         *
         * Note that intersecting Entities do not necessarily collide
         *
         * @param that The other Entity
         *
         * @return True if AlienBullet and Entity collide
         */
        bool collidesWith(Entity* that);
    };
}




#endif /* ALIENBULLET_H_ */
