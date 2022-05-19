
cd build
cmake -DGENERATE_DOCS=ON -DCMAKE_BUILD_TYPE=DEBUG .. 

if (make)
then 
    echo "-------------Build succeeded-----------"
    sudo ip link set down vcan0
    echo ""
    echo "--------------Set Down VCAN0--------------"
    sudo ip link show vcan0
    sudo modprobe vcan
    sudo ip link add dev vcan0 type vcan
    echo ""
    echo "--------------Set UP VCAN0--------------"
    sudo ip link set up vcan0
    sudo ip link show vcan0

    cd Emulator/
    gnome-terminal -- ./simulator
    cd ../UserInput
    gnome-terminal -- ./ui
    cd ../Display
    gnome-terminal -- ./display -c vcan0
fi
