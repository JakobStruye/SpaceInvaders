/*
 * entityFactory.h
 *
 *  Created on: 17-dec.-2013
 *      Author: Jakob Struye
 */

#ifndef ENTITYFACTORY_H_
#define ENTITYFACTORY_H_

#include "../Entities/entity.h"

namespace Factory {
	/**
	 * Abstract Factory for Entities
	 */
	class EntityFactory {
	public:
		/**
		 * @brief Generates an Entity
		 *
		 * @param xLoc Horizontal location of the Entity
		 * @param yLoc Vertical location of the Entity
		 * @param relativeSize Size of the longest side
		 *
		 * @return Pointer to the generated Entity
		 */
		virtual Model::Entity* getEntity(int xLoc, int yLoc, int relativeSize) = 0;


		/**
		 * @brief Destructor
		 */
		virtual ~EntityFactory() {}
	};


}

#endif /* ENTITYFACTORY_H_ */
