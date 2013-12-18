/*
 * regularAlienTypes.h
 *
 *  Created on: 11-dec.-2013
 *      Author: Jakob
 */

#ifndef REGULARALIENTYPES_H_
#define REGULARALIENTYPES_H_

#include "regularAlien.h"

namespace Model {
    /**
     * Class representing aliens in the top row in classic Space Invaders
     */
	class RegularAlienTop : public RegularAlien {
	public:
        /**
        * @brief Constructor
        *
        * @param xLoc Horizontal location of left side of RegularAlienTop
        * @param yLoc Vertical location of top of RegularAlienTop
        * @param relativeSize size of the longest side
        */
  		RegularAlienTop(int xLoc, int yLoc, int relativeSize) :
  			RegularAlien(xLoc, yLoc, relativeSize) {}

        /**
         * @brief Gets the score value of the RegularAlienTop
         *
         * @return 40
         */
		int getScore() { return 40; }
	};

    /**
     * Class representing aliens in the second and third row from the top in classic Space Invaders
     */
	class RegularAlienMid : public RegularAlien {
	public:
        /**
        * @brief Constructor
        *
        * @param xLoc Horizontal location of left side of RegularAlienMid
        * @param yLoc Vertical location of top of RegularAlienMid
        * @param relativeSize size of the longest side
        */
  		RegularAlienMid(int xLoc, int yLoc, int relativeSize) :
  			RegularAlien(xLoc, yLoc, relativeSize) {}

        /**
         * @brief Gets the score value of the RegularAlienMud
         *
         * @return 20
         */
		int getScore() { return 20; }
	};

	/**
	 * Class representing aliens in the two bottom rows in classic Space Invaders
	 */
	class RegularAlienBot : public RegularAlien {
	public:
        /**
        * @brief Constructor
        *
        * @param xLoc Horizontal location of left side of RegularAlienBot
        * @param yLoc Vertical location of top of RegularAlienBot
        * @param relativeSize size of the longest side
        */
  		RegularAlienBot(int xLoc, int yLoc, int relativeSize) :
  			RegularAlien(xLoc, yLoc, relativeSize) {}

        /**
         * @brief Gets the score value of the RegularAlienBot
         *
         * @return 10
         */
		int getScore() { return 10; }
	};

}

#endif /* REGULARALIENTYPES_H_ */
