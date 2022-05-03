
#ifndef CAN_RECEIVER_HPP
#define CAN_RECEIVER_HPP
#include "socketcan.hpp"

#include <memory>
#include<iostream>
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
    struct CanInFrame{
        uint32_t can_id;
        uint8_t can_dlc;
        CanUIData can_data;
    };
    class CanTranceiver{
        public:
            CanTranceiver() = default;
            CanInFrame can_frame{};
            scpp::SocketCan sockat_can;
            scpp::CanFrame can_fr;
            bool OpenCan();
            bool CanFromUI(); 
            bool CanToDisplay(const CanUIData&); 
            uint8_t prev_cntr{0};
            CanUIData getCanFrame();
    };
    
//} //namespace CanReceiver

// 
#endif