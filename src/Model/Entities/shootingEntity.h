/*
 * shootingEntity.h
 *
 *  Created on: Dec 2, 2013
 *      Author: jakob
 */

#ifndef SHOOTINGENTITY_H_
#define SHOOTINGENTITY_H_

#include "mobileEntity.h"
#include "../Factories/concreteEntityFactories.h"



namespace Model {

    class Bullet;


    /**
     * Class representing shooting (==able to create Bullets) entities in the game
     **/
    class ShootingEntity : public MobileEntity {
    public:
        /**
         * @brief Constructor
         *
         * @param xLoc Horizontal location of left side of Entity
         * @param yLoc Vertical location of top of Entity
         * @param xSize Horizontal size of Entity
         * @param ySize Vertical size of Entity
         * @param HP Starting HP
         * @param fact Factory used to create Bullets when shooting
         */
        ShootingEntity(int xLoc, int yLoc, int xSize, int ySize, int HP, Factory::EntityFactory* fact) :
           MobileEntity(xLoc, yLoc, xSize, ySize, HP), bulletFactory_(fact) {}

        /**
         * @brief ShootingEntity fires one Bullet
         *
         * @return pointer to the fired Bullet
         */
        virtual Bullet* shoot() = 0;

        /**
         * @brief Destructor
         */
        virtual ~ShootingEntity() { delete bulletFactory_;}

    protected:
        Factory::EntityFactory* bulletFactory_;
    };

}

#endif /* SHOOTINGENTITY_H_ */
