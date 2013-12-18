/*
 * SpaceInvadersView.h
 *
 *  Created on: 7-dec.-2013
 *      Author: Jakob
 */

#ifndef SPACEINVADERSVIEW_H_
#define SPACEINVADERSVIEW_H_


#include <SFML/Graphics.hpp>
#include "../Model/spaceInvadersModel.h"
#include "textures.h"
#include "../Other/observer.h"

//#define DATADIR "/home/jakob/Dropbox/UA/workspace/SpaceInvaders/data/"
//#define DATADIR "C:/Users/Jakob/Dropbox/UA/workspace/SpaceInvaders/data/"
//#define DATADIR ""


namespace View {

    /**
     * Class taking care of the visual representation of a Space Invaders game through the SFML library
     */
	class SpaceInvadersSFML : public Observer {
	public:


	    /**
	     * @brief Constructor
	     *
	     * @param xReso Horizontal resolution of the playfield
	     * @param yReso Vertical resolution of the playfield
	     * @param SI Pointer to the Model of the game being represented
	     */
		SpaceInvadersSFML(int xReso, int yReso, Model::SpaceInvadersModel* SI);

		/**
		 * @brief Generates the HUD for the current state of the game
		 */

		void generateHUD();

		/**
		 * @brief Draws the current state of the game
		 *
		 * @return True if window still open
		 */
		bool draw();

		/**
		 * @brief Draws the current state of a game currently not in progress
		 *
		 * @return True if window still open
		 */
		bool drawGameOver();


		/**
		 * @brief Draws the current state of a game currently paused (but in progress)
		 *
		 * @return True if window still open
		 */
		bool drawPaused();

		/**
		 * @brief Loads all textures
		 */
		void setTextures();

		/**
		 * @brief Sets the Sprite for the PlayerShip
		 */
		void setPlayer();

		/**
		 * @brief Sets the Sprites for the RegularAliens
		 */
		void setAliens();

		/**
		 * @brief Sets the Sprites for the Bullets
		 */
		void setBullets();

		/**
		 * @brief Sets the Sprites for the Shields
		 */
		void setShields();

		/**
		 * @brief Sets the Sprite for the BonusAlien
		 */
		void setBonus();

		/**
		 * @brief: Generates a square shape of the given Entity
		 * Should only be used in case of missing Texture
		 *
		 * @param entity Pointer to the Entity of which shape should be generated
		 */
		void generateShape(Model::Entity* entity);

		/**
		 * @brief Sets new Model pointer
		 */
		void setModel(Model::SpaceInvadersModel* SI);

		/**
		 * @brief Closes the window
		 */
		void closeWindow();


		/**
		 * @brief Checks if the View (in this View: the SFML window) is currently open
		 *
		 * @return True if window is open
		 */
		bool isViewOpen();


		/**
		 * @brief Handles notifications sent by observee (the Model)
		 *
		 * @param gameOver True if game is currently over
		 * @param winner True if player just won a level
		 */
		virtual void notify(bool gameOver, bool winner);


	private:
		int xReso_;
		int yReso_;
		int HUDoffset_ = 30;  //Hudoffset_ pixels are added for the HUD at the top of the window
		sf::RenderWindow window_;
		Model::SpaceInvadersModel* SI_;
		bool altTextures_;   //True if alternative Textures for RegularAliens should be used
		int framesPerAlienMove_;   //Needed by altTextures
		int alienMoveCounter_;
		std::vector<sf::Sprite> sprites_;   //Contains all Sprites to be drawn
		std::vector<sf::RectangleShape> shapes_;    //Only used in case of missing Textures
        Textures tex_;      //Contains all Textures
        sf::Font font_;     //The basic font for text
        bool allTexturesFound_;
        bool gameOver_;
	};
}


#endif /* SPACEINVADERSVIEW_H_ */
