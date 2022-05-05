#ifndef SERVER_HPP
#define SERVER_HPP

#include<iostream>
#include<cstring>
#include "can_receiver.hpp"
#include "engine.hpp"
#include<ui.hpp>
using namespace std;

class Server{
        // CanFrame can_ui_frame;
         
    public:
        Server() = default;
        bool StartEmulate(const UserInputCanFrame&);
        DisplayCanFrame can_data_to_disp;
        uint8_t prev_cntr{0};
        Engine* engine;
        CanTranceiver* can_tranceiver;
        uint8_t engine_rpm;
};

#endif