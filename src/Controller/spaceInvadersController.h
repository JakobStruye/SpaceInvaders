/* SpaceInvadersView.h
 *
 *  Created on: 7-dec.-2013
 *      Author: Jakob
 */

#ifndef SPACEINVADERSCONTROLLER_H_
#define SPACEINVADERSCONTROLLER_H_


#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include "../Model/spaceInvadersModel.h"
#include "../View/spaceInvadersView.h"
#include "../Other/observer.h"



namespace Controller {

    /**
     * Class responsible for controlling both the Model and View of a Space Invaders game
     */
    class SpaceInvadersController : public Observer {
    public:
        /**
         * @brief Constructor
         */
        SpaceInvadersController();

        /**
         * @brief Performs one step of the game
         *
         * @return True if game is still running
         */
        bool step();

        /**
         * @brief Performs one step of the game while game is over
         *
         * @return True if game is still running
         */
        bool stepGameOver();

        /**
         * @brief Performs one step of the game while game is paused
         *
         * @return True if game is still running
         */
        bool stepPaused();

        /**
         * @brief Generates a new Model when game is about to restart
         */
        void resetModel();

        /**
         * @brief Play the game
         */
        void play();

        /**
         * @brief Handles notifications sent by observee (the Model)
         *
         * @param gameOver True if game is currently over
         * @param winner True if player just won a level
         */
        void notify(bool gameOver, bool winner);
    private:

        sf::Clock clock_; //Takes care of frame time
        //Note that changing the resolution to something other than 800*600
        //means generateHUD() will have to be changed if the standard View is used
        int xReso_ = 800;
        int yReso_ = 600;
        int FPS_ = 30;    //Frames per second
        double SPF_ = 1.0 / (double) FPS_;   //Seconds per frame

        bool gameOver_;
        bool paused_;
        Model::SpaceInvadersModel* SIModel_;
        View::SpaceInvadersSFML SIView_;
    };
}

#endif /*SPACEINVADERSCONTROLLER_H_ */
