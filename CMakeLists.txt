# This file is a part of the RNA Stem Loop Visualizer software.
#
# Copyright (C) 2013
# 
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along
# with this program; if not, write to the Free Software Foundation, Inc.,
# 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
#
# Last modified: 27 November 2013
# By: Stijn Wouters
cmake_minimum_required(VERSION 2.6)
project("RNA Stem Loop Visualizer")

# Some OS X changes
IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
   # Mac OS X specific code
   SET(OperatingSystem "Mac OS X")
   SET (CMAKE_CXX_COMPILER "/usr/bin/clang++")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")


# Define DATADIR, used to find textures and font
add_definitions(-DDATADIR="${CMAKE_SOURCE_DIR}/data/")


# Lists all sourcefiles (no testfiles and no main)
set(SRC
    src/Controller/spaceInvadersController.cpp
    src/Model/spaceInvadersModel.cpp
    src/Model/Entities/alienBullet.cpp
    src/Model/Entities/bonusAlien.cpp
    src/Model/Entities/entity.cpp
    src/Model/Entities/mobileEntity.cpp
    src/Model/Entities/playerBullet.cpp
    src/Model/Entities/playerShip.cpp
    src/Model/Entities/regularAlien.cpp
    src/Model/Factories/concreteEntityFactories.cpp
    src/View/spaceInvadersView.cpp)


# Set flags
set(CMAKE_CXX_FLAGS "-pedantic -Wall -Wextra -std=c++11")


# Detect and add SFML
find_package(SFML 2 REQUIRED COMPONENTS graphics window system)
include_directories(${SFML_INCLUDE_DIR})


# Target to build the main program
add_executable(SpaceInvaders src/main.cpp ${SRC})


# Link executable with SFML
target_link_libraries(SpaceInvaders ${SFML_LIBRARIES})


# Install all executables into the bin directory.
install(TARGETS SpaceInvaders DESTINATION ${PROJECT_SOURCE_DIR}/bin)
