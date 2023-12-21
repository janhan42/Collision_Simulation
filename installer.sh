#!/bin/bash

git clone https://github.com/janhan42/Collision_Simulation.git
cd Collision_Simulation
bash -c "$(curl -fsSL https://raw.githubusercontent.com/janhan42/SFML-installer/master/installer.sh)"
mkdir .OBJ
make
./Collision_Simulation
