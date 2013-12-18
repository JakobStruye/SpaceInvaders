/*
 * entity.cpp
 *
 *  Created on: Dec 15, 2013
 *      Author: jakob
 */

#include "entity.h"

namespace Model {


    int Entity::getXPosition() const { return xLoc_; }


    int Entity::getYPosition() const { return yLoc_; }


    int Entity::getXSize() const { return xSize_; }


    int Entity::getYSize() const { return ySize_; }


    int Entity::getHP() const { return HP_; }



    void Entity::decrementHP() { HP_--; }


    bool Entity::checkOutOfBounds(int xReso, int yReso) {
    	//Whole Entity must be within [0, xReso] horizontally and [0, yReso] vertically
        if (xLoc_ < 0 || (xLoc_ + xSize_) > xReso || yLoc_ < 0 || (yLoc_ + ySize_) > yReso)
            return true;
        return false;
    }


    bool Entity::intersects(const Entity* that) {
    	//Calculate the highest and lowest horizontal and vertical coordinates of both Entities
        int thisTopY = this->getYPosition();
        int thisBotY = thisTopY + this->getYSize();
        int thisLeftX = this->getXPosition();
        int thisRightX = thisLeftX + this->getXSize();
        int thatTopY = that->getYPosition();
        int thatBotY = thatTopY + that->getYSize();
        int thatLeftX = that->getXPosition();
        int thatRightX = thatLeftX + that->getXSize();
        //Check if this completely below that
        if (thisTopY > thatBotY)    //Note that bigger means lower!
            return false;
        //Check if that completely below this
        if (thatTopY > thisBotY)
            return false;
        //Check if this completely to the right of that
        if (thisLeftX > thatRightX)
            return false;
        //Check if that completely to the right of this
        if (thatLeftX > thisRightX)
            return false;
        //If none of the above checks are true, then the Entities must intersect somewhere
        return true;
    }


    bool Entity::collidesWith(Entity* that) {
    	//Both should be alive to be able to collide
        if (that->getHP() == 0 || this->getHP() == 0)
            return false;
        //Entity can't collide with itself
        if (this == that)
            return false;
        bool collides =  intersects(that);
        if (collides) {
            this->decrementHP();
            that->decrementHP();
        }
        return collides;
    }


}
