#ifndef SERVER_HPP
#define SERVER_HPP

#include<iostream>

#include "can_receiver.hpp"
#include "engine.hpp"
using namespace std;

class Server{
        // CanFrame can_frame;
         
    public:
        Server() = default;
        bool StartEmulate(CanFrame& can_frame);
        scpp::SocketCan sockat_can;
        scpp::CanFrame can_fr;
        uint8_t prev_cntr{0};
        Engine* engine;
        uint8_t engine_rpm;
};

#endif