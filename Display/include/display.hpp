#include <iostream>

#include "candb.hpp"
#include "socketcan.hpp"
#ifndef DISPLAY_INCLUDE_DISPLAY_HPP_
#define DISPLAY_INCLUDE_DISPLAY_HPP_

using namespace std;

struct CanDisplayData {
  uint8_t frame_cntr;
  uint8_t ignition;
  uint8_t gear;
  uint8_t speed;
  uint8_t rpm;
  uint8_t blinkers;
};

struct CanDisplayFrame {
  uint32_t can_id;
  uint8_t can_dlc;
  CanDisplayData can_data;
};
class CanReceiver {
 public:
  CanReceiver() = default;
  CanDisplayFrame can_frame_display;  
  scpp::SocketCan sockat_can;
  scpp::CanFrame can_fr;
  bool OpenCan();
  bool CanFromServer();
  uint8_t prev_cntr{0};
  DisplayCanFrame getCanFrame();
};

#endif  // DISPLAY_INCLUDE_DISPLAY_HPP_
