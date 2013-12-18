/*
 * entity.h
 *
 *  Created on: Dec 2, 2013
 *      Author: jakob
 */

#ifndef ENTITY_H_
#define ENTITY_H_

#include "../../Other/common.h"

namespace Model {

    /**
    * Abstract base class representing all entities in the game
    */
    class Entity {
    public:

        /**
         * @brief Constructor
         *
         * @param xLoc Horizontal location of left side of Entity
         * @param yLoc Vertical location of top of Entity
         * @param xSize Horizontal size of Entity
         * @param ySize Vertical size of Entity
         * @param HP Starting HP
         */
        Entity(int xLoc, int yLoc, int xSize, int ySize, int HP) :
            xLoc_(xLoc), yLoc_(yLoc), xSize_(xSize), ySize_(ySize), HP_(HP) {}


        /**
         * @brief Gets horizontal position
         *
         * @return Horizontal position
         */
        int getXPosition() const;


        /**
         * @brief Gets vertical position
         *
         * @return Vertical position
         */
        int getYPosition() const;

        /**
         * @brief Gets horizontal size
         *
         * @return Horizontal size
         */
        int getXSize() const;

        /**
         * @brief Gets vertical size
         *
         * @return Vertical size
         */
        int getYSize() const;

        /**
         * @brief Gets current HP
         *
         * @return Current HP
         */
        int getHP() const;


        /**
         * @brief Decrements HP by one
         *
         * Note that this assumes HP is >0!
         */
        void decrementHP();

        /**
         * @brief Checks if the Entity is still FULLY within the provided bounds
         *
         * @param xReso Maximum horizontal allowed location (minimum is 0)
         * @param yReso Maximum vertical allowed location (minimum is 0)
         *
         * @return true if not fully within bounds
         */
        virtual bool checkOutOfBounds(int xReso, int yReso);

        /**
         * @brief Checks if this Entity intersects with another
         *
         * @param that The other Entity
         *
         * @return True if they intersect
         */
        bool intersects(const Entity* that);


        /**
         * @brief Checks if Entity collides with another
         *
         * Note that intersecting Entities do not necessarily collide
         *
         * @param that The other Entity
         *
         * @return True if Entities collide
         */
        virtual bool collidesWith(Entity* that);


        /**
         * @brief Destructor
         */
        virtual ~Entity() {}
    protected:
        /**
         * Position of Entity is stored with these four (unitless) values
         * xLoc_ and yLoc_ are coordinates of the top left corner
         * xSize_ and ySize_ are the horizontal and vertical sizes
         * Note that this means every Entity is rectangular
         */
        int xLoc_;    //smaller to bigger: left to right
        int yLoc_;    //smaller to bigger: top to bottom
        int xSize_;
        int ySize_;
        /**
         * Entity should be considered destroyed with 0HP,
         * though this class does not enforce this
         */
        int HP_;

    };
}

#endif /* ENTITY_H_ */
