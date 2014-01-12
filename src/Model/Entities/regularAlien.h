/*
 * regularAlien.h
 *
 *  Created on: Dec 2, 2013
 *      Author: Jakob Struye
 */

#ifndef REGULARALIEN_H_
#define REGULARALIEN_H_

#include "alien.h"

namespace Model {
    /**
     * Class representing the regular, classic Space Invaders alien
     */
    class RegularAlien : public Alien {
    public:
        /**
  		* @brief Constructor
  		*
  		* @param xLoc Horizontal location of left side of RegularAlien
  		* @param yLoc Vertical location of top of RegularAlien
        * @param relativeSize size of the longest side
  		*/
  		RegularAlien(int xLoc, int yLoc, int relativeSize) :
  		Alien(xLoc, yLoc, relativeSize * 1, relativeSize * 0.75, 1, new Factory::AlienBulletFactory),
  		collidedWithSomething_(false) {}


        /**
         * @brief RegularAlien fires one Bullet
         *
         * @return pointer to the fired Bullet
         */
        virtual Bullet* shoot();

        /**
         * @brief Gets the score value of the RegularAlien
         *
         * @return the score
         */
        virtual int getScore() = 0;


        /**
         * @brief Checks if RegularAlien collides with another Entity
         *
         * Note that intersecting Entities do not necessarily collide
         *
         * @param that The other Entity
         *
         * @return True if RegularAlien and Entity collide
         */
        virtual bool collidesWith(Entity* entity);


        /**
         * @brief: checks if RegularAlien has collided with something other than a Bullet
         *
         * @return True if it did
         */
        virtual bool collidedWithSomething() const;

    protected:
    	bool collidedWithSomething_;
    };


}
#endif /* REGULARALIEN_H_ */
