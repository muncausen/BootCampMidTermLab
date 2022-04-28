#include "can_receiver.hpp"
#include "server.hpp"

bool CanReceiver::OpenCan(){
     if (sockat_can.open("vcan0") != scpp::STATUS_OK) {
        std::cout << "Cannot open vcan0." << std::endl;
        std::cout << "Check whether the vcan0 interface is up!" << std::endl;
        exit (-1);
    } else {cout << "VCAN0 is up'n Running..." << endl;}
}

bool CanReceiver::ReceiveCan(){
    CanFrame can_frame{};
    scpp::CanFrame can_fr;
    if (sockat_can.read(can_fr) == scpp::STATUS_OK) {            
        printf("len %d byte, id: %d, data: %02x %02x %02x %02x  \n", can_fr.len, can_fr.id, 
        can_fr.data[0], can_fr.data[1], can_fr.data[2], can_fr.data[3]
//        ,can_fr.data[4], can_fr.data[5], can_fr.data[6], can_fr.data[7]
        );
        can_frame.frame_id = can_fr.id;
        can_frame.frame_dlc= can_fr.len;
        can_frame.frame_cntr = can_fr.data[1];
        can_frame.update_bit = can_fr.data[0] & 0x80;
        can_frame.ignition = can_fr.data[0] & 0x08;
        if (can_frame.ignition == false){
            cout << "Car is in Off state!" << endl;
        } else {cout << "Car is in Drivable state!" << endl;}
        can_frame.acceleration_req = can_fr.data[2];
        can_frame.brake_application = can_fr.data[3];
        can_frame.gear = can_fr.data[4];
    }
    Server *server_ = nullptr;
    server_ = new Server;
    if ((can_frame.frame_cntr != prev_cntr) && (can_frame.ignition == true)){
        server_->UpdateCanData(can_frame);
        prev_cntr = can_frame.frame_cntr;
    }

    return can_frame.ignition;
    };
