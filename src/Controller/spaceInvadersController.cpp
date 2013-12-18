/*
 * spaceInvadersController.cpp
 *
 *  Created on: 13-dec.-2013
 *      Author: Jakob
 */

#include "spaceInvadersController.h"

namespace Controller {

    SpaceInvadersController::SpaceInvadersController() : gameOver_(false),paused_(false),  SIModel_(new Model::SpaceInvadersModel(xReso_, yReso_)),
        SIView_(xReso_, yReso_, SIModel_) {
    	//Controller creates the Model and View
        SIModel_->registerObserver(this);
        SIModel_->registerObserver(&SIView_);
    }


    bool SpaceInvadersController::step() {
        //double timeStart = clock_.getElapsedTime().asSeconds();

        if (gameOver_)
            return stepGameOver();
        if (paused_)
            return stepPaused();
        //Won't be reached if game is over or paused
        //input processing below
        bool playerMoveLeft = false;
        bool playerMoveRight = false;
        bool playerShoot = false;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            playerMoveLeft = true;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            playerMoveRight = true;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            playerShoot = true;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
               paused_ = true;
        //Push the input to the model
        SIModel_->setPlayerMovements(playerMoveLeft, playerMoveRight, playerShoot);
        //Perform one step in the model
        SIModel_->step();

        //Note that the Model will notify the View of this step

        //double timeEnd = clock_.getElapsedTime().asSeconds();
        //std::cout << 100 * (1.0 - ((timeEnd - timeStart) / SPF_)) << "% of frame time unused." << std::endl;

        //Wait until frame time is reached
        while(clock_.getElapsedTime().asSeconds() < SPF_);

        clock_.restart();

        //Check if View is still open
        return SIView_.isViewOpen();

    }

    bool SpaceInvadersController::stepGameOver() {
    	//Escape ends the game
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            SIView_.closeWindow();
            return false;
        }
        //Return starts a new game
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
            resetModel();
        }
        //Check if View is still open
        return SIView_.isViewOpen();
    }

    bool SpaceInvadersController::stepPaused() {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
            paused_ = false;
        return SIView_.drawPaused();
    }

    void SpaceInvadersController::resetModel() {
        delete SIModel_;
        //Create a new model and set observers
        SIModel_ = new Model::SpaceInvadersModel(xReso_, yReso_);
        SIView_.setModel(SIModel_);
        SIModel_->registerObserver(this);
        SIModel_->registerObserver(&SIView_);
        gameOver_ = false;
    }

    void SpaceInvadersController::play() {
    	//Perform steps until one returns false
    	while (step());
    }

    void SpaceInvadersController::notify(bool gameOver, bool winner) {
        if (gameOver && !winner) {
            gameOver_ = true;
        }
        //Other notifications have no effect on the Controller
        return;
    }

}
