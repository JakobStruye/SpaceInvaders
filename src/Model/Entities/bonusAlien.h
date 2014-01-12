/*
 * bonusAlien.h
 *
 *  Created on: 13-dec.-2013
 *      Author: Jakob Struye
 */

#ifndef BONUSALIEN_H_
#define BONUSALIEN_H_

#include "alien.h"

namespace Model {

    /**
     * Class representing the bonus alien appearing periodically at the top of the screen in classic Space Invaders
     */
	class BonusAlien : public Alien {
	public:
        /**
        * @brief Constructor
        *
        * @param xLoc Horizontal location of left side of BonusAlien
        * @param yLoc Vertical location of top of BonusAlien
        * @param relativeSize size of the longest side
        *
        */
		BonusAlien(int xLoc, int yLoc, int relativeSize) :
			Alien(xLoc, yLoc, relativeSize, relativeSize * 0.6, 1, nullptr) {}

		/**
		 * @brief Disables BonusAlien from shooting
		 *
		 * @return nullptr
		 */
        virtual Bullet* shoot();

        /**
         * @brief Gets the score value of BonusAlien
         *
         * @return 100
         */
        virtual int getScore();

        /**
         * @brief Checks if BonusAlien is PARTIALLY within bounds
         *
         * @param xReso Maximum horizontal allowed location (minimum is 0)
         * @param yReso Maximum vertical allowed location (minimum is 0)
         *
         * @return true if not partially within bounds
         */
        virtual bool checkOutOfBounds(int xReso, int yReso);
	};
}



#endif /* BONUSALIEN_H_ */
