#include <iostream>

#include "candb.hpp"
#include "socketcan.hpp"
#ifndef DISPLAY_INCLUDE_DISPLAY_HPP_
#define DISPLAY_INCLUDE_DISPLAY_HPP_

using namespace std;

struct CanDisplayFrame {
  uint32_t can_id;
  uint8_t can_dlc;
  DisplayCanFrame can_data;  // data transfered to display e.g. speed, revs, etc
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
