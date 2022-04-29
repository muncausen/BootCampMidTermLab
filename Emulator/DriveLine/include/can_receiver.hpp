
#ifndef CAN_RECEIVER_HPP
#define CAN_RECEIVER_HPP
#include "socketcan.hpp"

#include <memory>
#include<iostream>
using namespace std;

//namespace UserInput {

    struct CanFrame{
        uint8_t frame_id;
        uint8_t frame_dlc;
        bool update_bit;
        uint8_t frame_cntr;
        bool ignition;
        uint8_t acceleration_req; // positive: accelerate, negative: brake
        uint8_t brake_application;
        uint8_t gear;
    };
    class CanReceiver{
        public:
            CanFrame test_cfr{};
            CanReceiver() = default;
            scpp::SocketCan sockat_can;
            scpp::CanFrame can_fr;
            bool OpenCan();
            bool ReceiveCan(); 
            uint8_t prev_cntr{0};
            CanFrame getCanFrame();
    };

//} //namespace CanReceiver

// 
#endif