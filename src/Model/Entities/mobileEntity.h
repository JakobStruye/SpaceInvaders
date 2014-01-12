/*
 * mobileEntity.h
 *
 *  Created on: Dec 2, 2013
 *      Author: Jakob Struye
 */

#ifndef MOBILEENTITY_H_
#define MOBILEENTITY_H_

#include "entity.h"

namespace Model {


    /**
     * Abstract class representing mobile (==with non-fixed position) entities in the game
     */

    class MobileEntity : public Entity {
    public:
        /**
         * @brief Constructor
         *
         * @param xLoc Horizontal location of left side of MobileEntity
         * @param yLoc Vertical location of top of MobileEntity
         * @param xSize Horizontal size of MobileEntity
         * @param ySize Vertical size of MobileEntity
         * @param HP Starting HP
         */
        MobileEntity(int xLoc, int yLoc, int xSize, int ySize, int HP) :
           Entity(xLoc, yLoc, xSize, ySize, HP) {}


        /**
         * @brief Move the MobileEntity
         *
         * @param dir The direction in which the MobileEntity should be moving
         * @param distance The distance the MobileEnity should move
         */
        virtual void move(Direction dir, int distance);
    };
}


#endif /* MOBILEENTITY_H_ */
