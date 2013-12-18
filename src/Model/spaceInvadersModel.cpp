/*
 * spaceInvadersModel.cpp
 *
 *  Created on: 13-dec.-2013
 *      Author: Jakob
 */


#include "spaceInvadersModel.h"
#include "./Factories/concreteEntityFactories.h"

namespace Model {

	SpaceInvadersModel::SpaceInvadersModel(int xSize, int ySize) :
		xSize_(xSize), ySize_(ySize), alienRows_(5), alienColumns_(11), currentLevel_(0),
		modifier_(1), aliensToDescend_(false), currentLives_(maxLives_), score_(0),
		levelOver_(false), winner_(false), respawnCounter_(0), alienDir_(R), bonusDir_(R),
		playerMoveLeft_(false), playerMoveRight_(false), playerShoot_(false),
		playerShootWait_(0), alienMoveWait_(0), alienShootWait_(0), bonusMoveWait_(0),
		bonusSpawnWait_(framesPerBonusSpawn_ / 2) {
		//Note that bonusSpawnWait_ is initially divided by 2.
		//This speeds up the spawn of the first BonusAlien
		generatePlayfield();
	}

	void SpaceInvadersModel::generateRegularAliens() {
		Factory::EntityFactory * factory;

		//Determine how many "pixels" each RegularAlien gets, depending on screen size
		int xPerAlien = xSize_ / 20;
		int xBetweenAliens = xSize_ / 80;
		int yPerAlien = ySize_ / 20;
		int yBetweenAliens = ySize_ / 80;
		double topMarginPercentage = 0.075;   //Leave top 7.5% of screen open for BonusAliens
		int currentY = topMarginPercentage * ySize_;
		int currentX = 0;
		factory = new Factory::RegularAlienTopFactory;
		//Todo: shorten
		for (int j=0; j < alienColumns_; j++) {   //One row of RegularAlienTops
			RegularAlien* newAlien = dynamic_cast<RegularAlien*>(factory->getEntity(currentX, currentY, xPerAlien));
			aliens_.push_back(newAlien);
			currentX += xPerAlien + xBetweenAliens;
		}
		currentX = 0;
		currentY += yPerAlien + yBetweenAliens;
		delete factory;
		factory = new Factory::RegularAlienMidFactory;
		for (int i=0; i < 2; i++) {               //Two rows of RegularAlienMids
			for (int j=0; j < alienColumns_; j++) {
				RegularAlien* newAlien = dynamic_cast<RegularAlien*>(factory->getEntity(currentX, currentY, xPerAlien));
				aliens_.push_back(newAlien);
				currentX += xPerAlien + xBetweenAliens;
			}
			currentX = 0;
			currentY += yPerAlien + yBetweenAliens;
		}
		delete factory;
		factory = new Factory::RegularAlienBotFactory;
		for (int i=0; i < 2; i++) {                   //Two rows of RegularAlienBots
			for (int j=0; j < alienColumns_; j++) {
				RegularAlien* newAlien = dynamic_cast<RegularAlien*>(factory->getEntity(currentX, currentY, xPerAlien));
				aliens_.push_back(newAlien);
				currentX += xPerAlien + xBetweenAliens;
			}
			currentX = 0;
			currentY += yPerAlien + yBetweenAliens;
		}
		delete factory;

	}

	void SpaceInvadersModel::generateShields() {
		 //Determine how many pixels each Shield gets, depending on screen size
		int shieldX = 0.125 * xSize_;
		int xPerShield = 0.1 * xSize_;
		int xBetweenShields = 0.12 * xSize_;
		int shieldY = 0.7 * ySize_;
		Factory::EntityFactory* factory = new Factory::ShieldFactory;
		for (int i = 0; i < 4; i++) {  //Generate four shields
			Shield* newShield = dynamic_cast<Shield*>(factory->getEntity(shieldX, shieldY, xPerShield));
			shields_.push_back(newShield);
			shieldX += xPerShield + xBetweenShields;
		}
		delete factory;
	}

	void SpaceInvadersModel::generatePlayer() {
		//Determine position and size of Player
		int xPerPlayer = 0.07 * xSize_;
		int playerX = (xSize_ / 2.0) - (xPerPlayer / 2.0);
		int playerY = 0.9 * ySize_;
		Factory::EntityFactory* factory = new Factory::PlayerShipFactory;
		player_ = dynamic_cast<PlayerShip*>(factory->getEntity(playerX, playerY, xPerPlayer));
		delete factory;
	}

	void SpaceInvadersModel::generatePlayfield() {
		generateRegularAliens();
		generateShields();
		generatePlayer();
		bonus_ = nullptr;

		//currentLevel starts at 0 and this function is called every time a new level starts
		currentLevel_++;
		modifier_ = 1;
		//Multiply modifier_ with modifierIncrease_ currentLevel_ times
		for (int i=0; i < currentLevel_ - 1; i++)
		    modifier_ *= modifierIncrease_;
		framesPerAlienMove_ /= modifier_;
		framesPerAlienShot_ /= modifier_;
		//The following two variables should be at least 1, to avoid /0
		if (framesPerAlienMove_ == 0)
		    framesPerAlienMove_++;
        if (framesPerAlienShot_ == 0)
            framesPerAlienShot_++;

	}

	std::vector<RegularAlien*>& SpaceInvadersModel::getRegularAliens() {return aliens_; }

    std::vector<Shield*>& SpaceInvadersModel::getShields() {return shields_; }

    std::vector<Bullet*>& SpaceInvadersModel::getBullets() {return bullets_; }

    PlayerShip* SpaceInvadersModel::getPlayer() {return player_; }

    BonusAlien* SpaceInvadersModel::getBonus() {return bonus_; }


	void SpaceInvadersModel::moveRegularAliens(Direction dir, int distance) {
		for (auto i : aliens_)
			if (i)
				i->move(dir, distance);
	}


	void SpaceInvadersModel::randomAlienShoot() {
		//Determine the bottom RegularAlien in every column
		std::vector<RegularAlien*> bottomAliens(11, nullptr);
		//Start at the back of the vector (as RegularAliens where added from top to bottom)
		for (int i = (alienRows_ * alienColumns_) -1; i >= 0; i--) {
			if (bottomAliens[i % alienColumns_] == 0 && aliens_[i]) {  //Currently nullptr for this column?
				bottomAliens[i % alienColumns_] = aliens_[i];		   //then this is the bottom RegularAlien
			}
		}
		//remove rows without aliens
		std::vector<RegularAlien*>::iterator it = bottomAliens.begin();
		while (it != bottomAliens.end()){
			if (!(*it))  //if nullptr
				it = bottomAliens.erase(it);
			else
				it++;
		}
		//stuff for random
		std::default_random_engine e1(rd());
		std::uniform_int_distribution<int> uniform_dist(1, bottomAliens.size());

		int shooter = uniform_dist(e1);  //pick random between 1 and number of nonempty columns
		shooter--;    //subtract one (because it should start at 0)
		bullets_.push_back(bottomAliens[shooter]->shoot());  //Have the picked RegularAlien take a shot
	}

    void SpaceInvadersModel::playerShoot() {
    	bullets_.push_back(player_->shoot());
    }


    void SpaceInvadersModel::detectAllCollisions() {
    	//Create one big vector of all Entities for easier detection
		std::vector<Entity*> entities;
		entities.reserve( bullets_.size() + aliens_.size() +shields_.size() + 1 );
		entities.insert( entities.end(), bullets_.begin(), bullets_.end());
		entities.insert( entities.end(), aliens_.begin(), aliens_.end());
		entities.insert( entities.end(), shields_.begin(), shields_.end());
		if (player_)
			entities.push_back(player_);
		if (bonus_)
			entities.push_back(bonus_);
		std::vector<Entity*>::iterator it = entities.begin();
		while (it != entities.end()) {      //For every Entity
			std::vector<Entity*>::iterator subIt = it;
			while (subIt != entities.end()) {  //Check against all following Entities
				if (*it && *subIt) {    //Both should exist
					//If collision detected, break, as an Entity can only collide with 1 other
					if ((*it)->collidesWith(*subIt))
						break;
				}
				subIt++;
			}
			it++;
		}
    }

    void SpaceInvadersModel::checkForDestroyedRegularAliens() {
		bool alienCollided = false;   //True if a RegularAlien hit something other than a Bullet
		std::vector<RegularAlien*>::iterator alienIt = aliens_.begin();
		while (alienIt != aliens_.end()) {
			if ((*alienIt) && (*alienIt)->getHP() == 0) {  //Check if not yet deleted but destroyed
				if ((*alienIt)->collidedWithSomething())   //Check if it hit something other than a Bullet
					alienCollided = true;
				else
					score_ += (*alienIt)->getScore();   //Add score
				delete *alienIt;
				//Just set to nullptr, don't remove from vector,
				//the position in the vector is used to determine bottom RegularAliens in randomAlienShoot()
				*alienIt = nullptr;
			}
			alienIt++;
		}
		if (alienCollided) {   //RegularAlien collided with something -> level is over and player loses
			levelOver(false);
		}

		if (!areAliensAlive()) //All RegularAliens destroyed -> Player wins this level
		    levelOver(true);
    }

    void SpaceInvadersModel::checkForDestroyedBullets() {
		std::vector<Bullet*>::iterator bulletIt = bullets_.begin();
		while (bulletIt != bullets_.end()) {
			if ((*bulletIt)->getHP() == 0) {
				//Destroyed Bullet found: delete and remove from vector
				delete *bulletIt;
				bulletIt = bullets_.erase(bulletIt);
			}
			//Bullet no longer in range of playfield: delete and remove from vector
			else if ((*bulletIt)->checkOutOfBounds(xSize_, ySize_)) {
				delete *bulletIt;
				bulletIt = bullets_.erase(bulletIt);
			}
			else
				bulletIt++;
		}
    }

    void SpaceInvadersModel::checkForDestroyedShields() {
		std::vector<Shield*>::iterator shieldIt = shields_.begin();
		while (shieldIt != shields_.end()) {
			if ((*shieldIt)->getHP() == 0) {
				//Destroyed shield found: delete and remove from vector
				delete *shieldIt;
				shieldIt = shields_.erase(shieldIt);
			}
			else
				shieldIt++;
		}
    }

    void SpaceInvadersModel::checkForDestroyedPlayer() {
		if (player_ && player_->getHP() == 0) {
			//Player destroyed: delete and remove from vector
			delete player_;
			player_ = nullptr;
			//If lives left: initiate respawn countdown
			if (currentLives_ > 1) {
				currentLives_--;
				respawnCounter_ = framesBeforeRespawn_;
			}
			else
				levelOver(false);  //Else player loses level
		}
    }

    void SpaceInvadersModel::checkForDestroyedBonusAlien() {
    	//BonusAlien destroyed or out of playfield bounds
		if (bonus_ && ((bonus_->getHP() == 0) || bonus_->checkOutOfBounds(xSize_, ySize_))) {
			if (bonus_->getHP() == 0)
				score_ += bonus_->getScore();  //Add score only if destroyed
			delete bonus_;
			bonus_ = nullptr;
			//Reset move and spawn counters
			bonusSpawnWait_ = 0;
			bonusMoveWait_ = 0;
			//Change direction for next BonusAlien
			if (bonusDir_ == L)
				bonusDir_ = R;
			else
				bonusDir_ = L;
		}
    }


	void SpaceInvadersModel::handleAllCollisions() {
		detectAllCollisions();

		checkForDestroyedRegularAliens();
		checkForDestroyedBullets();
		checkForDestroyedShields();
		checkForDestroyedPlayer();
		checkForDestroyedBonusAlien();
	}

	void SpaceInvadersModel::levelOver(bool won) {
		//Check if levelOver was already set
	    if (levelOver_)
	        return;
	    //Delete everything in playfield
		while (!(aliens_.empty())) {
			delete aliens_.back();
			aliens_.pop_back();
		}
		while (!(bullets_.empty())) {
			delete bullets_.back();
			bullets_.pop_back();
		}
		while (!(shields_.empty())) {
			delete shields_.back();
			shields_.pop_back();
		}
		winner_ = won;
		player_ = nullptr;
		//if the player won, the next level should start, so generate new playfield
		if (winner_) {
			generatePlayfield();
		}
		else
			levelOver_ = true;
	}

    int SpaceInvadersModel::getScore() const {return score_; }


    int SpaceInvadersModel::getLives() const {return currentLives_; }


    int SpaceInvadersModel::getLevel() const {return currentLevel_; }


    int SpaceInvadersModel::getFramesPerAlienMove() const {return framesPerAlienMove_; }


	RegularAlien* SpaceInvadersModel::getLeftmostRegularAlien() const {
		//For every column starting from the leftmost, check every row for a living RegularAlien
		for (int i=0; i < alienColumns_; i++) {
			for (int j=0; j < alienRows_; j++) {
				if (aliens_[i + (j * alienColumns_)])  //Return first found living RegularAlien
					return aliens_[i + (j * alienColumns_)];
			}
		}
		return nullptr;
	}


	RegularAlien* SpaceInvadersModel::getRightmostRegularAlien() const {
		//Analogous to getLeftmostRegularAlien()
		for (int i=(alienColumns_ -1); i >= 0; i--) {
			for (int j=0; j < alienRows_; j++) {
				if (aliens_[i + (j * alienColumns_)])
					return aliens_[i + (j * alienColumns_)];
			}
		}
		return nullptr;
	}


	void SpaceInvadersModel::setPlayerMovements(bool moveLeft, bool moveRight, bool shoot) {
		playerMoveLeft_ = moveLeft;
		playerMoveRight_ = moveRight;
		playerShoot_ = shoot;
	}

	bool SpaceInvadersModel::areAliensAlive() {
		for (auto i : aliens_)
			if (i)  //Any RegularAlien alive -> true
				return true;
		return false;
	}


	void SpaceInvadersModel::stepPlayer() {
		//Check if counting down to respawn
		if (respawnCounter_) {
			respawnCounter_--;
			//Check if countdown over
			if (!respawnCounter_) {
				Factory::EntityFactory* factory = new Factory::PlayerShipFactory;
				//Generate new PlayerShip
				int xPerPlayer = 0.07 * xSize_;
				int playerX = (xSize_ / 2.0) - (xPerPlayer / 2.0);
				int playerY = 0.9 * ySize_;
				player_ = dynamic_cast<PlayerShip*>(factory->getEntity(playerX, playerY, xPerPlayer));
				delete factory;
			}
		}
		//Continue shoot cooldown if it's ongoing
		if (playerShootWait_)
			playerShootWait_--;
		//Check if PlayerShip alive
		if (player_) {
			//Perform movements after checking whether there's room for them
			if (playerMoveLeft_)
				if (player_->getXPosition() - playerMoveDistance_ > 0)
					player_->move(L, playerMoveDistance_);
			if (playerMoveRight_)
				if (player_->getXPosition() + player_->getXSize() + playerMoveDistance_ < xSize_)
					player_->move(R, playerMoveDistance_);
			if (playerShoot_) {
				if (!playerShootWait_) {
					playerShoot();
					playerShootWait_ = playerShootCooldown_;
				}
			}
		}
		playerMoveLeft_ = false;
		playerMoveRight_ = false;
		playerShoot_ = false;

	}


	void SpaceInvadersModel::stepRegularAliens() {
		++alienMoveWait_ %= framesPerAlienMove_;
		//Check if RegularAliens should move
		if (!alienMoveWait_) {
			switch (alienDir_) {
			//Check if move in current direction is possible
			//If not change direction and let next move be down
			case L:
				if (getLeftmostRegularAlien()->getXPosition() < xSize_ / (double) alienHorMoveDistanceRelative_) {
					alienDir_ = R;
					aliensToDescend_ = true;
				}
				break;
			case R:
				if ((getRightmostRegularAlien()->getXPosition() + getRightmostRegularAlien()->getXSize()) >
					(((double) (alienHorMoveDistanceRelative_ - 1) / (double) alienHorMoveDistanceRelative_) * xSize_)) {
					alienDir_ = L;
					aliensToDescend_ = true;
				}
				break;
			default:
				break; //shouldn't occur
			}
			//Check if next move should be down
			if (aliensToDescend_) {
				moveRegularAliens(D, ySize_ / (double) alienVertMoveDistanceRelative_);
				aliensToDescend_ = false;
			}
			//else move in normal direction
			else
				moveRegularAliens(alienDir_, xSize_ / (double) alienHorMoveDistanceRelative_);
		}
		++alienShootWait_ %= framesPerAlienShot_;
		//Check if a RegularAlien should shoot
		if (!alienShootWait_ )
			randomAlienShoot();
	}

    void SpaceInvadersModel::stepBonusAlien() {
    	//If there's currently no BonusAlien
        if (bonus_ == nullptr) {
            ++bonusSpawnWait_ %= framesPerBonusSpawn_;
            //Check if one should spawn
            if (!bonusSpawnWait_) {
            	Factory::EntityFactory* factory = new Factory::BonusAlienFactory;
            	//Spawn one in right location according to its direction
                if (bonusDir_ == R) {
                    bonus_ = dynamic_cast<BonusAlien*>(factory->getEntity(0, 10, 50));
                    //if it's spawned on the left, move out of sight
                    bonus_->move(L, bonus_->getXSize());
                }
                else {
                    bonus_ = dynamic_cast<BonusAlien*>(factory->getEntity(xSize_, 10, 50));
                    //If it's spawned on the right it's already out of sight
                }
                delete factory;
            }
        }
        //Else there is a BonusAlien active
        else {
    		++bonusMoveWait_ %= framesPerBonusMove_;
    		//Check if it should move
    		if (!bonusMoveWait_) {
    			bonus_->move(bonusDir_, xSize_ / (double) alienHorMoveDistanceRelative_);
    		}
        }
    }

	void SpaceInvadersModel::step() {

		handleAllCollisions();
		//If the level ended during collision handling, notify observers and end step
		if (levelOver_) {
			notifyObservers();
			return;
		}
		//Perform steps for all MobileEntities
		stepPlayer();
		stepRegularAliens();
		stepBonusAlien();
		//Bullets just move every step, no separate function needed
		for (auto i : bullets_) {
			i->move(bulletMoveDistance_);
		}
		//Notify observers of state of game after step
		notifyObservers();
		winner_ = false; //This needs to be reset after notifying
	}

	std::vector<Observer*>::iterator SpaceInvadersModel::findObserver(Observer* obs) {
		std::vector<Observer*>::iterator it = observers_.begin();
		while (it != observers_.end()) {
			if (*it == obs)  //end search if target found
				break;
			it++;
		}
		//it is either iterator to target or observers_.end() if not found
		return it;
	}

	bool SpaceInvadersModel::registerObserver(Observer* obs) {
		//Check if already registered
		if (findObserver(obs) != observers_.end())
			return false;
		//If not, register
		observers_.push_back(obs);
		return true;
	}

	bool SpaceInvadersModel::unregisterObserver(Observer* obs) {
		//Find observer to unregister
		std::vector<Observer*>::iterator pos = findObserver(obs);
		if (pos == observers_.end())
			return false;
		//Unregister if found
		observers_.erase(pos);
		return true;
	}

	void SpaceInvadersModel::notifyObservers() {
		//Notify observers that state has changed
		//Actions taken by observers depends on whether level is over and whether player has won
		for (auto i : observers_)
			i->notify(levelOver_, winner_);
	}

}

