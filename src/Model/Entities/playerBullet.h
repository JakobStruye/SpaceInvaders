/*
 * playerBullet.h
 *
 *  Created on: Dec 2, 2013
 *      Author: Jakob Struye
 */

#ifndef PLAYERBULLET_H_
#define PLAYERBULLET_H_

#include "bullet.h"


namespace Model {


    /**
     * Class representing bullet shot by player's ship
     */
    class PlayerBullet : public Bullet {
    public:
        /**
         * @brief Constructor
         *
         * @param xLoc Horizontal location of left side of PlayerBullet
         * @param yLoc Vertical location of top of PlayerBullet
         * @param relativeSize size of the longest side
         */
        PlayerBullet(int xLoc, int yLoc, int relativeSize) :
           Bullet(xLoc, yLoc, 0.2 * relativeSize, relativeSize, 1, U) {}


        /**
         * @brief Checks if PlayerBullet collides with another Entity
         *
         * Note that intersecting Entities do not necessarily collide
         *
         * @param that The other Entity
         *
         * @return True if PlayerBullet and Entity collide
         */
        bool collidesWith(Entity* that);
    };
}



#endif /* PLAYERBULLET_H_ */
