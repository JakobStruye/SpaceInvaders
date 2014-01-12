/*
 * observer.h
 *
 *  Created on: 13-dec.-2013
 *      Author: Jakob Struye
 */

#ifndef OBSERVER_H_
#define OBSERVER_H_

/**
 * Abstract base class for any class that observes the Space Invaders model
 */
class Observer {
public:

    /**
     * @brief Handles a notification sent by Space Invaders model
     *
     * @param gameOver True if the game is currently over
     * @param winner True if player just won a level
     */
	virtual void notify(bool gameOver, bool winner) = 0;

	/**
	 * @brief Destructor
	 */
	virtual ~Observer() {}
};



#endif /* OBSERVER_H_ */
