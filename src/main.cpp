/*
 * main.cpp
 *
 *  Created on: 13-dec.-2013
 *      Author: Jakob
 */
#include "./Controller/spaceInvadersController.h"


int main() {
	Controller::SpaceInvadersController SIC;   //Controller takes care of model and view
	SIC.play();
	//std::cout << "DONE" << std::endl;
	return 0;
}
