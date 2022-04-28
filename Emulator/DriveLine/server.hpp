#ifndef SERVER_HPP
#define SERVER_HPP

#include<iostream>

#include "can_receiver.hpp"

using namespace std;

class Server{
        // CanFrame can_frame;
         
    public:
        Server() = default;
        bool UpdateCanData(CanFrame& can_frame);
        scpp::SocketCan sockat_can;
        scpp::CanFrame can_fr;
        uint8_t prev_cntr{0};
};

#endif