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
  CanDisplayData can_data; //data transfered to display e.g. speed, revs, etc
};
class CanReceiver {
 public:
  CanReceiver() = default;
  CanDisplayFrame can_frame_display;  
  scpp::SocketCan sockat_can;
  bool OpenCan();
  bool CanFromServer();
};

#endif  // DISPLAY_INCLUDE_DISPLAY_HPP_
