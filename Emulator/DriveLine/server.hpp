#ifndef SERVER_HPP
#define SERVER_HPP

#include <cstring>
#include <iostream>
#include <ui.hpp>

#include "can_tranceiver.hpp"
#include "engine.hpp"
using namespace std;

class Server {
  // CanFrame can_ui_frame;
  Engine engine_;
  Engine* engine = &engine_;
  CanTranceiver can_tranceiver_;
  CanTranceiver* can_tranceiver = &can_tranceiver_;
  uint8_t auto_gear_;

 public:
  Server() = default;
  bool StartEmulate(const UserInputCanFrame&);
  DisplayCanFrame can_data_to_disp{};
  uint8_t prev_cntr{0};
  uint8_t engine_rpm;

  void PrintEngine(const UserInputCanFrame&);
};

#endif