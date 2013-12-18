/*
 * alien.h
 *
 *  Created on: Dec 2, 2013
 *      Author: jakob
 */

#ifndef ALIEN_H_
#define ALIEN_H_

#include "shootingEntity.h"


namespace Model {

    /**
     * Abstract class representing any alien
     */
    class Alien : public ShootingEntity {
    public:
        /**
		* @brief Constructor
		*
		* @param xLoc Horizontal location of left side of Alien
		* @param yLoc Vertical location of top of Alien
		* @param xSize Horizontal size of Alien
		* @param ySize Vertical size of Alien
		* @param HP Starting HP
		* @param fact Factory used to create Bullets when shooting
		*
		*/
		Alien(int xLoc, int yLoc, int xSize, int ySize, int HP, Factory::EntityFactory* fact) :
		ShootingEntity(xLoc, yLoc, xSize, ySize, HP, fact) {}

		/**
		 * @brief Gets the score value of the Alien
		 *
		 * @return the score
		 */
        virtual int getScore() = 0;
    };


}


#endif /* ALIEN_H_ */
