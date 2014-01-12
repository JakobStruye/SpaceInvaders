/*
 * specificFactories.h
 *
 *  Created on: 17-dec.-2013
 *      Author: Jakob Struye
 */

#ifndef SPECIFICFACTORIES_H_
#define SPECIFICFACTORIES_H_

#include "abstractEntityFactory.h"


namespace Factory {

	/**
	 * Concrete Factory generating AlienBullets
	 */
	class AlienBulletFactory : public EntityFactory {
	public:
		/**
		 * @brief Generates an AlienBullet
		 *
		 * @param xLoc Horizontal location of the AlienBullet
		 * @param yLoc Vertical location of the AlienBullet
		 * @param relativeSize Size of the longest side
		 *
		 * @return Pointer to the generated AlienBullet
		 */
		virtual Model::Entity* getEntity(int xLoc, int yLoc, int relativeSize);
	};


	/**
	 * Concrete Factory generating BonusAliens
	 */
	class BonusAlienFactory : public EntityFactory {
	public:
		/**
		 * @brief Generates an BonusAlien
		 *
		 * @param xLoc Horizontal location of the BonusAlien
		 * @param yLoc Vertical location of the BonusAlien
		 * @param relativeSize Size of the longest side
		 *
		 * @return Pointer to the generated BonusAlien
		 */
		virtual Model::Entity* getEntity(int xLoc, int yLoc, int relativeSize);
	};


	/**
	 * Concrete Factory generating PlayerBullets
	 */
	class PlayerBulletFactory : public EntityFactory {
	public:
		/**
		 * @brief Generates an PlayerBullet
		 *
		 * @param xLoc Horizontal location of the PlayerBullet
		 * @param yLoc Vertical location of the PlayerBullet
		 * @param relativeSize Size of the longest side
		 *
		 * @return Pointer to the generated PlayerBullet
		 */
		virtual Model::Entity* getEntity(int xLoc, int yLoc, int relativeSize);
	};


	/**
	 * Concrete Factory generating PlayerShips
	 */
	class PlayerShipFactory : public EntityFactory {
	public:
		/**
		 * @brief Generates an PlayerShip
		 *
		 * @param xLoc Horizontal location of the PlayerShip
		 * @param yLoc Vertical location of the PlayerShip
		 * @param relativeSize Size of the longest side
		 *
		 * @return Pointer to the generated PlayerShip
		 */
		virtual Model::Entity* getEntity(int xLoc, int yLoc, int relativeSize);
	};


	/**
	 * Concrete Factory generating RegularAlienBots
	 */
	class RegularAlienBotFactory : public EntityFactory {
	public:
		/**
		 * @brief Generates an RegularAlienBot
		 *
		 * @param xLoc Horizontal location of the RegularAlienBot
		 * @param yLoc Vertical location of the RegularAlienBot
		 * @param relativeSize Size of the longest side
		 *
		 * @return Pointer to the generated RegularAlienBot
		 */
		virtual Model::Entity* getEntity(int xLoc, int yLoc, int relativeSize);
	};


	/**
	 * Concrete Factory generating RegularAlienMids
	 */
	class RegularAlienMidFactory : public EntityFactory {
	public:
		/**
		 * @brief Generates an RegularAlienMid
		 *
		 * @param xLoc Horizontal location of the RegularAlienMid
		 * @param yLoc Vertical location of the RegularAlienMid
		 * @param relativeSize Size of the longest side
		 *
		 * @return Pointer to the generated RegularAlienMid
		 */
		virtual Model::Entity* getEntity(int xLoc, int yLoc, int relativeSize);
	};


	/**
	 * Concrete Factory generating RegularAlienTops
	 */
	class RegularAlienTopFactory : public EntityFactory {
	public:
		/**
		 * @brief Generates an RegularAlienTop
		 *
		 * @param xLoc Horizontal location of the RegularAlienTop
		 * @param yLoc Vertical location of the RegularAlienTop
		 * @param relativeSize Size of the longest side
		 *
		 * @return Pointer to the generated RegularAlienTop
		 */
		virtual Model::Entity* getEntity(int xLoc, int yLoc, int relativeSize);
	};


	/**
	 * Concrete Factory generating Shields
	 */
	class ShieldFactory : public EntityFactory {
	public:
		/**
		 * @brief Generates an Shield
		 *
		 * @param xLoc Horizontal location of the Shield
		 * @param yLoc Vertical location of the Shield
		 * @param relativeSize Size of the longest side
		 *
		 * @return Pointer to the generated Shield
		 */
		virtual Model::Entity* getEntity(int xLoc, int yLoc, int relativeSize);
	};
}



#endif /* SPECIFICFACTORIES_H_ */
