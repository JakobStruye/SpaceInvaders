/*
 * spaceInvaders.h
 *
 *  Created on: 4-dec.-2013
 *      Author: Jakob Struye
 */

#ifndef SPACEINVADERSMODEL_H_
#define SPACEINVADERSMODEL_H_

#include <vector>
#include <random>
#include "Entities/regularAlienTypes.h"
#include "Entities/playerShip.h"
#include "Entities/shield.h"
#include "Entities/alienBullet.h"
#include "Entities/playerBullet.h"
#include "Entities/bonusAlien.h"
#include "../Other/observer.h"


namespace Model {

	/**
	 * Class representing the full SpaceInvaders model
	 */
	class SpaceInvadersModel {
	public:
	    /**
	     * @brief Constructor
	     *
	     * @param xSize Horizontal size of the playfield
	     * @param ySize Vertical size of the playfield
	     */
		SpaceInvadersModel(int xSize, int ySize);


		/**
		 * @brief Generates a fresh playfield for when a next level is started
		 */
		void generatePlayfield();


		/**
		 * @brief gets vector containing pointers to all RegularAliens
		 *
		 * @return vector of all RegularAlien pointers
		 */
		std::vector<RegularAlien*>& getRegularAliens();


        /**
         * @brief gets vector containing pointers to all Shields
         *
         * @return vector of all Shield pointers
         */
        std::vector<Shield*>& getShields();


        /**
         * @brief gets vector containing pointers to all Bullets
         *
         * @return vector of all Bullet pointers
         */
        std::vector<Bullet*>& getBullets();


        /**
         * @brief gets pointer to PlayerShip
         *
         * @return pointer to PlayerShip
         */
        PlayerShip* getPlayer();


        /**
         * @brief gets pointer to BonusAlien
         *
         * @return pointer to BonusAlien
         */
        BonusAlien* getBonus();


        /**
         * @brief Moves all of the RegularAliens
         *
         * @param dir Current direction of the RegularAliens
         * @param distance The distance they should be moved over
         */
        void moveRegularAliens(Direction dir, int distance);


        /**
         * @brief Makes one random RegularAlien (bottom RegularAlien in his column) shoot one AlienBullet
         */
        void randomAlienShoot();


        /**
         * @brief makes the PlayerShip shoot one PlayerBullet
         */
        void playerShoot();


        /**
         * @brief Checks if any Entities collided with each other
         */
        void handleAllCollisions();


        /**
         * @brief Tears down the current playfield and sets up a new one if necessary
         *
         * @param won Incidates whether the player won this level. If true, a new playfield will be generated
         */
        void levelOver(bool won);


        /**
         * @brief Gets the current score
         *
         * @return The current score
         */
        int getScore() const;


        /**
         * @brief Gets the current remaining extra lives
         *
         * @return The current remaining extra lives
         */
        int getLives() const;


        /**
         * @brief Gets the current level
         *
         * @return The current level
         */
        int getLevel() const;


        /**
         * @brief Gets how many frames it takes for Aliens to move once
         *
         * @brief Frames it takes for aliens to move once
         */
        int getFramesPerAlienMove() const;


        /**
         * @brief Determines (one of) the RegularAlien(s) that is in the leftmost column
         *
         * @return Pointer to leftmost RegularAlien
         */
        RegularAlien* getLeftmostRegularAlien() const;


        /**
         * @brief Determines (one of) the RegularAlien(s) that is in the rightmost column
         *
         * @return Pointer to rightmost RegularAlien
         */
        RegularAlien* getRightmostRegularAlien() const;


        /**
         * @brief Sets what the PlayerShip should to in the next step
         *
         * @param moveLeft True if PlayerShip should move left
         * @param moveRight True if PlayerShip should move right
         * @param shoot True if player should fire one PlayerBullet
         */
        void setPlayerMovements(bool moveLeft, bool moveRight, bool shoot);


        /**
         * @brief Checks whether there are any living RegularAliens left
         *
         * @return True if any RegularAlien alive
         */
        bool areAliensAlive() const;


        /**
         * @brief Handles all PlayerShip-specific actions in one step of the game
         */
        void stepPlayer();


        /**
         * @brief Handles all RegularAlien-specific actions in one step of the game
         */
        void stepRegularAliens();


        /**
         * @brief Handles of all BonusAlien actions (generating, destroying, moving)
         */
        void stepBonusAlien();


        /**
         * @brief Performs one step of the ongoing game
         */
        void step();


        /**
         * @brief Searches for given Observer in vector of Observers
         *
         * @param obs Observer* to look for
         *
         * @return iterator to given Observer* if found, iterator to end of Observer vector if not found
         */
        std::vector<Observer*>::iterator findObserver(Observer* obs);


        /**
         * @brief Add an observer to the vector of observers
         *
         * @return True if added, otherwise false
         */
        bool registerObserver(Observer* obs);


        /**
         * @Removes an observer from the vector of observers
         *
         * @return True if added, otherwise false
         */
        bool unregisterObserver(Observer* obs);


        /**
         * @brief Notifies all observers if something changed
         */
        void notifyObservers();


	private:
        //Different Entity types in different containers
		std::vector<RegularAlien*> aliens_;
		std::vector<Bullet*> bullets_;
		std::vector<Shield*> shields_;
		PlayerShip* player_;
		BonusAlien* bonus_;

		//Size of playfield
		int xSize_;
		int ySize_;

		//These variables can be tweaked to slightly change the game
	    int framesPerAlienMove_ = 20;
	    int framesPerAlienShot_ = 65;
	    int alienHorMoveDistanceRelative_ = 32; //Aliens will move 1/*th of xSize
	    int alienVertMoveDistanceRelative_ = 24; //Aliens will move 1/*th of ySize
	    int framesPerBonusSpawn_ = 150;    //BonusAlien will spawn after ~ frames without BonusAlien
	    int framesPerBonusMove_ = 10;
	    int playerMoveDistance_ = 10;
	    const int playerShootCooldown_ = 15;   //PlayerShip can shoot only once per ~ frames
	    int bulletMoveDistance_ = 15;
	    int maxLives_ = 5;
	    int framesBeforeRespawn_ = 45;   //PlayerShip respawns after ~ frames if maxLives_ > 0
	    double modifierIncrease_ = 1.2;    //RegularAliens become ~ times faster every level

	    //These values should not be modified
		int alienRows_;
		int alienColumns_;
	    int currentLevel_;
        double modifier_;
	    bool aliensToDescend_;   //True if RegularAliens' next move should be down
	    int currentLives_;
	    int score_;
		bool levelOver_;
		bool winner_;          //True if player just won a level
		int respawnCounter_;   //Counts down until respawn
	    Direction alienDir_;   //Current Direction of RegularAliens (L/R)
	    Direction bonusDir_;   //Current Direction of BonusAlien (L/R)
	    bool playerMoveLeft_;  //True if PlayerShip should move Left
	    bool playerMoveRight_;
	    bool playerShoot_;
	    int playerShootWait_;  //Counts down until next possible shot from PlayerShip
	    int alienMoveWait_;    //Counts down until next move for RegularAliens
	    int alienShootWait_;   //Counts down until next random shot from RegularAliens
	    int bonusMoveWait_;    //Counts down until next move for BonusAlien
	    int bonusSpawnWait_;   //Counts down until next BonusAlien spawns

	    std::vector<Observer*> observers_;
		std::random_device rd;   //Used to pick a random RegularAlien to shoot

		void generateRegularAliens();
		void generateShields();
		void generatePlayer();
		void detectAllCollisions();
		void checkForDestroyedRegularAliens();
		void checkForDestroyedBullets();
		void checkForDestroyedShields();
		void checkForDestroyedPlayer();
		void checkForDestroyedBonusAlien();


	};
}



#endif /* SPACEINVADERSMODEL_H_ */
