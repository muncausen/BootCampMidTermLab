#!/bin/bash

gnome-terminal --title="UI frames" -- sh -c 'candump vcan0 | grep 0AA'
gnome-terminal --title="Display frames" -- sh -c 'candump vcan0 | grep 0BB'
