/*
 * playerShip.h
 *
 *  Created on: Dec 2, 2013
 *      Author: jakob
 */

#ifndef PLAYERSHIP_H_
#define PLAYERSHIP_H_

#include "shootingEntity.h"
#include "../Factories/concreteEntityFactories.h"

namespace Model {

    /**
     * Class representing the controllable ship at the bottom of the screen in classic Space Invaders
     */
    class PlayerShip : public ShootingEntity {
    public:
        /**
  		* @brief Constructor
  		*
  		* @param xLoc Horizontal location of left side of PlayerShip
  		* @param yLoc Vertical location of top of PlayerShip
        * @param relativeSize size of the longest side
  		* @param HP Starting HP
  		*/
    	PlayerShip(int xLoc, int yLoc, int relativeSize) :
    	ShootingEntity(xLoc, yLoc, relativeSize, relativeSize * 0.5, 1, new Factory::PlayerBulletFactory){}

        /**
         * @brief PlayerShip fires one Bullet
         *
         * @return pointer to the fired Bullet
         */
        Bullet* shoot();
    };
}




#endif /* PLAYERSHIP_H_ */
