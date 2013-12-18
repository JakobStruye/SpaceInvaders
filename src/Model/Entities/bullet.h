/*
 * Bullet.h
 *
 *  Created on: Dec 2, 2013
 *      Author: jakob
 */

#ifndef BULLET_H_
#define BULLET_H_


#include "mobileEntity.h"

namespace Model {

    /**
     * Class representing any kind of bullet in Space Invaders
     */
    class Bullet : public MobileEntity {
    public:
        /**
         * @brief Constructor
         *
         * @param xLoc Horizontal location of left side of Bullet
         * @param yLoc Vertical location of top of Bullet
         * @param xSize Horizontal size of Bullet
         * @param ySize Vertical size of Bullet;
         * @param HP Starting HP
         * @param dir Direction in which the Bullet is to travel
         */
        Bullet(int xLoc, int yLoc, int xSize, int ySize, int HP, Direction dir) :
           MobileEntity(xLoc, yLoc, xSize, ySize, HP), dir_(dir) {}

        /**
         * @brief Move the Bullet in its direction
         *
         * @param dist The distance the Bullet should move
         */
        void move(int dist) { MobileEntity::move(dir_, dist); }


        protected:
            Direction dir_;
    };
}


#endif /* BULLET_H_ */
