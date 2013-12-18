/*
 * staticEntity.h
 *
 *  Created on: Dec 2, 2013
 *      Author: jakob
 */

#ifndef STATICENTITY_H_
#define STATICENTITY_H_

#include "entity.h"


namespace Model {

    /**
     * Abstract class representing all static (==immobile) entities in the game
     */
    class StaticEntity: public Entity {
    public:

        /**
         * @brief Constructor
         *
         * @param xLoc Horizontal location of left side of StaticEntity
         * @param yLoc Vertical location of top of StaticEntity
         * @param xSize Horizontal size of StaticEntity
         * @param ySize Vertical size of StaticEntity
         * @param HP Starting HP
         */
        StaticEntity(int xLoc, int yLoc, int xSize, int ySize, int HP) :
        	Entity(xLoc, yLoc, xSize, ySize, HP) {}
    };
}


#endif /* STATICENTITY_H_ */
