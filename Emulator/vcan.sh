#!/bin/bash

if (true)
then
    
    sudo modprobe vcan
    sudo ip link add dev vcan0 type vcan
    sudo ip link set up vcan0
    sudo ip link show vcan0

fi