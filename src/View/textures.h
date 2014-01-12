/*
 * textures.h
 *
 *  Created on: 7-dec.-2013
 *      Author: Jakob Struye
 */

#ifndef TEXTURES_H_
#define TEXTURES_H_

#include <SFML/Graphics.hpp>

namespace View {
    /**
     * Holds all of the Textures used by the SFML view
     */
	struct Textures {
		sf::Texture playerTex_;
        sf::Texture alienBotTex_;
        sf::Texture alienBotAltTex_;
        sf::Texture alienMidTex_;
        sf::Texture alienMidAltTex_;
        sf::Texture alienTopTex_;
        sf::Texture alienTopAltTex_;
        sf::Texture shieldTex_;
        sf::Texture shieldLightDmgTex_;
        sf::Texture shieldMedDmgTex_;
        sf::Texture shieldHighDmgTex_;
        sf::Texture shieldVeryHighDmgTex_;
        sf::Texture bulletTex_;
        sf::Texture bonusTex_;
        sf::Texture emptyTex_;
	};

}


#endif /* TEXTURES_H_ */
