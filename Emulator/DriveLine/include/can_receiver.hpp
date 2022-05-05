
#ifndef CAN_RECEIVER_HPP
#define CAN_RECEIVER_HPP
#include "socketcan.hpp"

#include <memory>
#include<iostream>
#include<candb.hpp>
using namespace std;

//namespace UserInput {
    struct CanUIData {
        uint8_t frame_cntr;
        uint8_t ignition;
        uint8_t gear;
        uint8_t acceleration_req;
        uint8_t brake_req;
        uint8_t blinkers;
    };
    struct CanDispData {
        uint8_t frame_cntr;
        uint8_t ignition;
        uint8_t gear;
        uint8_t speed;
        uint8_t rpm;
        uint8_t blinkers;
    };
    struct CanUIFrame{
        uint32_t can_id;
        uint8_t can_dlc;
        UserInputCanFrame can_data;
    };
    struct CandispFrame{
        uint32_t can_id;
        uint8_t can_dlc;
        CanDispData can_data;
    };
    class CanTranceiver{
        public:
            CanTranceiver() = default;
            CanUIFrame can_ui_frame{};
            CanDispData can_data; // test using shift and & methode
            scpp::SocketCan sockat_can;
            scpp::CanFrame can_fr;
            bool OpenCan();
            bool CanFromUI(); 
            bool CanToDisplay(const DisplayCanFrame&); 
            uint8_t prev_cntr{0};
            UserInputCanFrame getCanFrame();
    };
    
//} //namespace CanReceiver

// 
#endif