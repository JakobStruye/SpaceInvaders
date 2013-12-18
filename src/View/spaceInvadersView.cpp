/*
 * SpaceInvadersView.cpp
 *
 *  Created on: 7-dec.-2013
 *      Author: Jakob
 */

#include "spaceInvadersView.h"
#include <sstream>
#include <iostream>
#include <exception>
#include <stdexcept>

namespace View {


    SpaceInvadersSFML::SpaceInvadersSFML(int xReso, int yReso, Model::SpaceInvadersModel* SI) : xReso_(xReso), yReso_(yReso),
            window_(sf::VideoMode(xReso, yReso + HUDoffset_), "Space Invaders"),SI_(SI), altTextures_(false),
            framesPerAlienMove_(SI->getFramesPerAlienMove()), alienMoveCounter_(0), gameOver_(false) {
    	try {
    		setTextures();
    		allTexturesFound_ = true;
    	}
    	catch(std::runtime_error& e) {
    		std::string error(e.what());
    		if (error == "Texture not found")
    			allTexturesFound_ = false;
    		if (error == "Font not found") {
    			std::string dataDirString = DATADIR;
    			std::cout << "arial.ttf not found in " << dataDirString << std::endl;
    			std::cout << "No text will be printed" << std::endl;
    			allTexturesFound_ = true;
    		}
    	}
    }


	void SpaceInvadersSFML::setTextures() {
        //First load the default font before we start loading textures
		std::string fileName = "arial.ttf";
        if (!font_.loadFromFile(DATADIR + fileName))
			throw std::runtime_error("Font not found");
		//Load all Textures. Doing this only once saves a LOT of calculations
		fileName = "PlayerShip1.png";
		if (!(tex_.playerTex_.loadFromFile(DATADIR + fileName)))
			throw std::runtime_error("Texture not found");
		fileName = "AlienBot1.png";
		if(!(tex_.alienBotTex_.loadFromFile(DATADIR + fileName)))
			throw std::runtime_error("Texture not found");
		fileName = "AlienBotAlt1.png";
		if (!(tex_.alienBotAltTex_.loadFromFile(DATADIR + fileName)))
			throw std::runtime_error("Texture not found");
		fileName = "AlienMid1.png";
		if (!(tex_.alienMidTex_.loadFromFile(DATADIR + fileName)))
			throw std::runtime_error("Texture not found");
		fileName = "AlienMidAlt1.png";
		if (!(tex_.alienMidAltTex_.loadFromFile(DATADIR + fileName)))
			throw std::runtime_error("Texture not found");
		fileName = "AlienTop1.png";
		if (!(tex_.alienTopTex_.loadFromFile(DATADIR + fileName)))
			throw std::runtime_error("Texture not found");
		fileName = "AlienTopAlt1.png";
		if (!(tex_.alienTopAltTex_.loadFromFile(DATADIR + fileName)))
			throw std::runtime_error("Texture not found");
        fileName = "Shield1.png";
        if (!(tex_.shieldTex_.loadFromFile(DATADIR + fileName)))
        	throw std::runtime_error("Texture not found");
        fileName = "Shield1LightDmg.png";
        if (!(tex_.shieldLightDmgTex_.loadFromFile(DATADIR + fileName)))
        	throw std::runtime_error("Texture not found");
        fileName = "Shield1MedDmg.png";
        if (!(tex_.shieldMedDmgTex_.loadFromFile(DATADIR + fileName)))
        	throw std::runtime_error("Texture not found");
        fileName = "Shield1HighDmg.png";
        if (!(tex_.shieldHighDmgTex_.loadFromFile(DATADIR + fileName)))
        	throw std::runtime_error("Texture not found");
        fileName = "Shield1VeryHighDmg.png";
        if (!(tex_.shieldVeryHighDmgTex_.loadFromFile(DATADIR + fileName)))
        	throw std::runtime_error("Texture not found");
        fileName = "Bullet2.png";
        if (!(tex_.bulletTex_.loadFromFile(DATADIR + fileName)))
        	throw std::runtime_error("Texture not found");
        fileName = "Powerup1.png";
        if (!(tex_.bonusTex_.loadFromFile(DATADIR + fileName)))
        	throw std::runtime_error("Texture not found");
	}


	void SpaceInvadersSFML::setPlayer() {
		Model::PlayerShip* player = SI_->getPlayer();
		if (player) {
			sf::Vector2u playerTexSize = tex_.playerTex_.getSize();
			//Make sure the Sprite is scaled to have the same size as the Entity
			float scalePlayerTex = ((double) player->getXSize() / playerTexSize.x);
			sprites_.push_back(sf::Sprite());
			sprites_.back().setTexture(tex_.playerTex_);
			sprites_.back().setScale(scalePlayerTex, scalePlayerTex);
			sprites_.back().setPosition(player->getXPosition(), player->getYPosition());
			if (!allTexturesFound_)
				generateShape(player);
		}

	}

	void SpaceInvadersSFML::setAliens() {
		//This calculates which Textures should be used for the RegularAliens
		//Has to be done in the View as to not violate MVC pattern
		++alienMoveCounter_ %= framesPerAlienMove_;
		//Every time the counter resets to 0, change the used Textures
		if (!alienMoveCounter_)
			altTextures_ = !altTextures_;

		//All RegularAlien Textures should have the same size
		//so scale should be the same for all of them
		sf::Vector2u alienTexSize = tex_.alienBotTex_.getSize();
		float scaleAlien = 0;
		bool scalesSet = false;
		//Note that destroyed RegularAliens are not completely erased,
		//but rather replaced by a nullptr
		for (auto i : SI_->getRegularAliens()) {
			//Check if not nullptr
			if (i) {
				if (allTexturesFound_) {   //Check if all Textures are present
					//Check if the scale has already been calculated, if not, calculate
					if (!scalesSet) {
						scaleAlien = ((double) i->getXSize() / alienTexSize.x);
						scalesSet = true;
					}
					//Generate the Sprite first, modify it afterwards
					sprites_.push_back(sf::Sprite());
					if (!altTextures_) {
						//Check which type of RegularAlien it is, pick Texture accordingly
						if (dynamic_cast<Model::RegularAlienTop*>(i)) {
							sprites_.back().setTexture(tex_.alienTopTex_);
							sprites_.back().scale(scaleAlien, scaleAlien);
						}
						else if (dynamic_cast<Model::RegularAlienMid*>(i)) {
							sprites_.back().setTexture(tex_.alienMidTex_);
							sprites_.back().scale(scaleAlien, scaleAlien);
						}
						else if (dynamic_cast<Model::RegularAlienBot*>(i)) {
							sprites_.back().setTexture(tex_.alienBotTex_);
							sprites_.back().scale(scaleAlien, scaleAlien);
						}
					}
					else {
						if (dynamic_cast<Model::RegularAlienTop*>(i)) {
							sprites_.back().setTexture(tex_.alienTopAltTex_);
							sprites_.back().scale(scaleAlien, scaleAlien);
						}
						else if (dynamic_cast<Model::RegularAlienMid*>(i)) {
							sprites_.back().setTexture(tex_.alienMidAltTex_);
							sprites_.back().scale(scaleAlien, scaleAlien);
						}
						else if (dynamic_cast<Model::RegularAlienBot*>(i)) {
							sprites_.back().setTexture(tex_.alienBotAltTex_);
							sprites_.back().scale(scaleAlien, scaleAlien);
						}
					}
					sprites_.back().setPosition(i->getXPosition(), i->getYPosition());
				}
				else   //Use shapes if not all Textures available
					generateShape(i);
			}
		}
	}


	void SpaceInvadersSFML::setShields() {
		sf::Vector2u shieldTexSize = tex_.shieldTex_.getSize();
		//Destroyed shields are erased from vector,
		//so getShields should only return valid pointers.
		//Always using the first one for scale calculation should be fine
		float scaleShieldTex = ((double) SI_->getShields()[0]->getXSize() / shieldTexSize.x);
		for (auto i : SI_->getShields()) {
			if (allTexturesFound_) {
				sprites_.push_back(sf::Sprite());
				//Pick Texture depending on current HP
				switch (i->getHP()) {
				case 1:
					sprites_.back().setTexture(tex_.shieldVeryHighDmgTex_);
					break;
				case 2:
					sprites_.back().setTexture(tex_.shieldHighDmgTex_);
					break;
				case 3:
					sprites_.back().setTexture(tex_.shieldMedDmgTex_);
					break;
				case 4:
					sprites_.back().setTexture(tex_.shieldLightDmgTex_);
					break;
				case 5:
					sprites_.back().setTexture(tex_.shieldTex_);
					break;
				}
				sprites_.back().scale(scaleShieldTex, scaleShieldTex);
				sprites_.back().setPosition(i->getXPosition(), i->getYPosition());
			}
			else
				generateShape(i);
		}

	}

	void SpaceInvadersSFML::setBullets() {
		sf::Vector2u bulletTexSize = tex_.bulletTex_.getSize();
		//Set scales to impossible value -1
		//This way it's easy to check if they have been set properly
		float scalePlayerBulletTex = -1;
		float scaleAlienBulletTex = -1;
		for (auto i : SI_->getBullets()) {
			if (allTexturesFound_) {
				sprites_.push_back(sf::Sprite());
				sprites_.back().setTexture(tex_.bulletTex_);
				if (dynamic_cast<Model::AlienBullet*>(i)) {
					if (scaleAlienBulletTex == -1)   //check if scale was set already
						scaleAlienBulletTex = (double) i->getXSize() / bulletTexSize.x;
					sprites_.back().scale(scaleAlienBulletTex, scaleAlienBulletTex);
				}
				else if (dynamic_cast<Model::PlayerBullet*>(i)) {
					if (scalePlayerBulletTex == -1)
						scalePlayerBulletTex = (double) i->getXSize() / bulletTexSize.x;
					sprites_.back().scale(scalePlayerBulletTex, scalePlayerBulletTex);
				}
				sprites_.back().setPosition(i->getXPosition(), i->getYPosition());
			}
			else
				generateShape(i);
		}


	}

	void SpaceInvadersSFML::setBonus() {
		Model::BonusAlien* bonus = SI_->getBonus();
		if (bonus) {
			if (allTexturesFound_) {
				sf::Vector2u bonusTexSize = tex_.bonusTex_.getSize();
				float scaleBonusTex = ((double) bonus->getXSize() / bonusTexSize.x);
				sprites_.push_back(sf::Sprite());
				sprites_.back().setTexture(tex_.bonusTex_);
				sprites_.back().setScale(scaleBonusTex, scaleBonusTex);
				sprites_.back().setPosition(bonus->getXPosition(), bonus->getYPosition());
			}
			else
				generateShape(bonus);
		}
	}

	void SpaceInvadersSFML::generateShape(Model::Entity* entity) {
		shapes_.push_back(sf::RectangleShape(
				sf::Vector2f(entity->getXSize(), entity->getYSize())));
		shapes_.back().move(entity->getXPosition(), entity->getYPosition());
	}

	void SpaceInvadersSFML::generateHUD() {
		//Display the current score
        sf::Text text;
        text.setFont(font_);
        int score = SI_->getScore();
        std::stringstream scoreStream;
        scoreStream << score;
        std::string scoreStr = "Score: " + scoreStream.str();
        text.setString(scoreStr);
        text.setCharacterSize(18);
        text.setPosition(15, 15);
        window_.draw(text);
        //Display the current level
        std::stringstream levelStream;
        levelStream << SI_->getLevel();
        std::string levelStr = "Level " + levelStream.str();
        text.setString(levelStr);
        text.setCharacterSize(18);
        text.setPosition(700, 15);
        window_.draw(text);
        //Display the current lives left
        std::string lives = "Lives: ";
        text.setString(lives);
        text.setCharacterSize(19);
        text.setPosition(300, 15);
        window_.draw(text);
        int lifePos = 360;
        for (int i = 0; i < SI_->getLives(); i++) {
        	if (allTexturesFound_) {
    			sf::Sprite lifeSprite;
				lifeSprite.setTexture(tex_.playerTex_);
				double scaleLife = 30.0 / (double) tex_.playerTex_.getSize().x;
				//std::cout << scaleLife << std::endl;
				lifeSprite.setScale(scaleLife, scaleLife);
				lifeSprite.setPosition(lifePos, 18);
				window_.draw(lifeSprite);
        	}
        	else {
    			sf::RectangleShape lifeShape;
        		lifeShape = sf::RectangleShape(sf::Vector2f(30, 15));
        		lifeShape.move(lifePos, 18);
    			window_.draw(lifeShape);
        	}
			//Next life 35 pixels to the right
			lifePos += 35;
        }
	}

	bool SpaceInvadersSFML::draw() {

		//Get rid of all Sprites from previous frame
		sprites_.clear();
		shapes_.clear();
		//Set all new Sprites
		setPlayer();
		setAliens();
		setShields();
		setBullets();
		setBonus();
        sf::Event event;
        while (window_.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window_.close();
        }

        window_.clear();

        if (gameOver_)
        	return drawGameOver();

        //Draw all Sprites of Entities
		if (allTexturesFound_) {    //Use sprites if all Textures were found
			for (auto& i : sprites_) {
				i.move(0, HUDoffset_);
				window_.draw(i);
			}
		}
		else {						//Use shapes if not all Textures were found
			for (auto& i : shapes_) {
				i.move(0, HUDoffset_);
				window_.draw(i);
			}
		}
        generateHUD();

        window_.display();
        return window_.isOpen();

	}


	bool SpaceInvadersSFML::drawGameOver() {
        sf::Event event;
        while (window_.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window_.close();
        }
        window_.clear();

        //Set "Game Over!"
        sf::Text text;
        text.setFont(font_);
        text.setString("Game Over!");
        text.setCharacterSize(60);
        text.setPosition(225, 225);
        window_.draw(text);

        //Set "You are dead!"
        text.setString("You are dead!");
        text.setCharacterSize(30);
        text.setPosition(295, 300);
        window_.draw(text);

        //Set "Reached level xx"
        std::stringstream levelStream;
        levelStream << SI_->getLevel();
        std::string levelStr = "Reached level " + levelStream.str();
        text.setString(levelStr);
        text.setCharacterSize(20);
        text.setPosition(315, 360);
        window_.draw(text);

        //Set "Final Score: xxxx"
        int score = SI_->getScore();
        std::stringstream scoreStream;
        scoreStream << score;
        std::string scoreStr = "Final score: " + scoreStream.str();
        text.setString(scoreStr);
        text.setCharacterSize(20);
        text.setPosition(322, 400);
        window_.draw(text);

        //Set restart and quit messages
        text.setString("Press enter to play again");
        text.setCharacterSize(20);
        text.setPosition(540, 500);
        window_.draw(text);
        text.setString("Press escape to quit game");
        text.setCharacterSize(20);
        text.setPosition(540, 540);
        window_.draw(text);

        window_.display();
        return window_.isOpen();

	}

	bool SpaceInvadersSFML::drawPaused() {
        sf::Event event;
        while (window_.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window_.close();
        }
        window_.clear();

        //Set the pause screen messages
        sf::Text text;
        text.setFont(font_);
        text.setString("Game Paused");
        text.setCharacterSize(60);
        text.setPosition(215, 225);
        window_.draw(text);
        text.setString("Press enter to continue");
        text.setCharacterSize(30);
        text.setPosition(255, 300);
        window_.draw(text);

        window_.display();
        return window_.isOpen();
	}

	void SpaceInvadersSFML::setModel(Model::SpaceInvadersModel* SI) {
		SI_ = SI;
		//Also reset these two values
		framesPerAlienMove_ = SI_->getFramesPerAlienMove();
		alienMoveCounter_ = 0;
	}

	bool SpaceInvadersSFML::isViewOpen() {
		return window_.isOpen();
	}
	void SpaceInvadersSFML::closeWindow() {
		window_.close();
	}



	void SpaceInvadersSFML::notify(bool gameOver, bool winner) {
		//Game is only really over if player didn't win the level!
		gameOver_ = (gameOver && !winner);
		//winner==true means player goes to next level,
		//so the framesPerAlienMove may have changed
		if (winner)
			framesPerAlienMove_ = SI_->getFramesPerAlienMove();
			//Do NOT reset the alienMoveCounter_ here,
			//doesn't happen on going to next level in Model either
		draw();
	}



}
