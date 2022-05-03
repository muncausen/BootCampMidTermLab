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
        bool StartEmulate(const CanUIData&);
        uint8_t prev_cntr{0};
        Engine* engine;
        uint8_t engine_rpm;
};

#endif