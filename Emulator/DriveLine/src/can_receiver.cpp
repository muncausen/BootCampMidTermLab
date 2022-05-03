#include "can_receiver.hpp"
#include "server.hpp"
#include<mutex>
#include <stdio.h>
#include<cstring>

bool CanTranceiver::OpenCan(){
     if (sockat_can.open("vcan0") != scpp::STATUS_OK) {
        std::cout << "Cannot open vcan0." << std::endl;
        std::cout << "Check whether the vcan0 interface is up!" << std::endl;
        exit (-1);
    } else {cout << "VCAN0 is up'n Running..." << endl;}
}

bool CanTranceiver::CanFromUI(){
    mutex can_mutex;
//    while(true){
        scpp::CanFrame can_from_ui;
        if (sockat_can.read(can_from_ui) == scpp::STATUS_OK) {            
            printf("len %d byte, id: %d, data: %02x %02x %02x %02x  \n", can_from_ui.len, can_from_ui.id, 
            can_from_ui.data[0], can_from_ui.data[1], can_from_ui.data[2], can_from_ui.data[3]);
            {const std::lock_guard<std::mutex> lock(can_mutex);
//            memcpy(&can_frame.can_data, &can_from_ui.data, sizeof(CanInFrame));
            can_frame.can_data.frame_cntr = (can_from_ui.data[0] & 0xf0) >> 4;
            can_frame.can_data.ignition =  (can_from_ui.data[0] & 0x0C) >> 2;
            can_frame.can_data.gear = ((can_from_ui.data[0] & 0x03) << 2) | (can_from_ui.data[1] >>6);
            can_frame.can_data.acceleration_req = ((can_from_ui.data[1] & 0xFF) << 2) | (can_from_ui.data[2] >>6);
            can_frame.can_data.brake_req = ((can_from_ui.data[2] & 0xFF) << 2) | (can_from_ui.data[3] >>6);
            can_frame.can_data.blinkers = (can_from_ui.data[3] & 0x30) >> 4;}
            if (can_frame.can_data.ignition == 0){
                cout << "Car is in Off state!" << endl;
            } else {cout << "Car is in Drivable state!" << endl;}
            // cout << "Received CNTR: " << (static_cast<int>((can_from_ui.data[0]) & 0xf0) >> 4) << endl;
            // cout << "CNTR: " <<  static_cast<int>(can_frame.can_data.frame_cntr) << endl;
            // cout << "IGNITION: " <<  static_cast<int>(can_frame.can_data.ignition) << endl;
            // cout << "GEAR: " <<  static_cast<int>(can_frame.can_data.gear) << endl;
            // cout << "ACCEL: " <<  static_cast<int>(can_frame.can_data.acceleration_req) << endl;
            // cout << "BRAKE: " <<  static_cast<int>(can_frame.can_data.brake_req) << endl;
            // cout << "BLINKs: " <<  static_cast<int>(can_frame.can_data.blinkers) << endl;
        }

    return can_frame.can_data.ignition;
    };
bool CanTranceiver::CanToDisplay(const CanUIData& can_to_disp){

}
CanUIData CanTranceiver::getCanFrame(){
    return can_frame.can_data;
}