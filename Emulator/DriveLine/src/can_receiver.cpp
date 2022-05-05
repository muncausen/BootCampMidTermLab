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
    //    CanDispData candata;
        scpp::CanFrame can_from_ui;
        if (sockat_can.read(can_from_ui) == scpp::STATUS_OK) {            
            printf("len %d byte, id: %d, data: %02x %02x %02x %02x  \n", can_from_ui.len, can_from_ui.id, 
            can_from_ui.data[0], can_from_ui.data[1], can_from_ui.data[2], can_from_ui.data[3]);
            {const std::lock_guard<std::mutex> lock(can_mutex);
            //******************************************************
            memcpy(&can_ui_frame.can_data, can_from_ui.data, sizeof(UserInputCanFrame));}
            //***********************FOR TEST*********************
            // CanDispData candata;
            // candata.frame_cntr = (can_from_ui.data[0] & 0xf0) >> 4;
            // can_ui_frame.can_data.ignition =  (can_from_ui.data[0] & 0x0C) >> 2;
            // can_ui_frame.can_data.gear_select = ((can_from_ui.data[0] & 0x03) << 2) | (can_from_ui.data[1] >>6);
            // can_ui_frame.can_data.throttle = ((can_from_ui.data[1] & 0xFF) << 2) | (can_from_ui.data[2] >>6);
            // can_ui_frame.can_data.brake = ((can_from_ui.data[2] & 0xFF) << 2) | (can_from_ui.data[3] >>6);
            // can_ui_frame.can_data.blinkers = (can_from_ui.data[3] & 0x30) >> 4;}
            //*********************END FOR TEST********************
            }
            // if (can_ui_frame.can_data.ignition == 0){
            //     cout << "Car is in Off state!" << endl;
            // } else {cout << "Car is in Drivable state!" << endl;}
            // cout << "Received CNTR: " << static_cast<int>((can_from_ui.data[0] & 0xf0) >> 4) << endl;
            // cout << "CNTR: "          <<  static_cast<int>(can_ui_frame.can_data.frame_counter) << endl;
            // cout << "IGNITION: "      <<  static_cast<int>(can_ui_frame.can_data.ignition) << endl;
            // cout << "GEAR: "          <<  static_cast<int>(can_ui_frame.can_data.gear_select) << endl;
            // cout << "ACCEL: "         <<  static_cast<int>(can_ui_frame.can_data.throttle) << endl;
            // cout << "BRAKE: "        <<  static_cast<int>(can_ui_frame.can_data.brake) << endl;
            // cout << "BLINKs: " <<  static_cast<int>(can_ui_frame.can_data.blinkers) << endl;
    return can_ui_frame.can_data.ignition;
    };

bool CanTranceiver::CanToDisplay(const DisplayCanFrame& can_from_server){
    scpp::CanFrame can_frame_to_display;
    can_frame_to_display.id = 123;
    can_frame_to_display.len = 4;
    memcpy(can_frame_to_display.data, &can_from_server, sizeof(can_from_server));
    auto write_sc_status = sockat_can.write(can_frame_to_display);
    if (write_sc_status != scpp::STATUS_OK)
      printf("something went wrong on socket write, error code : %d \n", int32_t(write_sc_status));

//    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}
UserInputCanFrame CanTranceiver::getCanFrame(){
    return can_ui_frame.can_data;
}