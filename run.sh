#!/bin/bash

gnome-terminal --title=Display -- ~/BootCampMidTermLab/build/Display/display -c vcan0
# gnome-terminal --title=CANdump -- candump vcan0
gnome-terminal --title=Simulator -- ~/BootCampMidTermLab/build/Emulator/simulator
gnome-terminal --title=Input -- ~/BootCampMidTermLab/build/UserInput/ui
