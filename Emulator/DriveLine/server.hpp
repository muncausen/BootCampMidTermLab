#ifndef SERVER_HPP
#define SERVER_HPP
#include "engine.hpp"
#include <cstring>
#include <iostream>
#include <ui.hpp>

#include "can_tranceiver.hpp"
using namespace std;
class Server {
  // CanFrame can_ui_frame;
  Engine engine_obj;
  Engine* engine = &engine_obj;
  CanTranceiver can_tranceiver_;
  CanTranceiver* can_tranceiver = &can_tranceiver_;
  uint8_t auto_gear_;
  unsigned int rpm;
  unsigned int speed;
  unsigned int gear; 
 public:
  Server() = default;
  bool StartEmulate(const UserInputCanFrame&);
  DisplayCanFrame can_data_to_disp{};
  uint8_t prev_cntr{0};
  uint8_t prev_throttle{0};
  uint8_t engine_rpm;
  void GetEngineValues(const uint16_t&, const uint16_t&, const uint8_t&);
  void PrintEngine(const UserInputCanFrame&);
};

#endif