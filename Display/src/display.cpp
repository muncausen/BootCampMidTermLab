#include "display.hpp"

#include <stdio.h>

#include <cstring>
#include <mutex>

bool CanReceiver::OpenCan() {
  if (sockat_can.open("vcan0") != scpp::STATUS_OK) {
    std::cout << "Cannot open vcan0." << std::endl;
    std::cout << "Check whether the vcan0 interface is up!" << std::endl;
    exit(-1);
  } else {
    cout << "VCAN0 is up'n Running..." << endl;
  }
}

bool CanReceiver::CanFromServer() {
  // mutex can_mutex;
  scpp::CanFrame can_from_server;
  if (sockat_can.read(can_from_server) == scpp::STATUS_OK) {
    // const std::lock_guard<std::mutex> lock(can_mutex);
    memcpy(&can_frame_display.can_data, can_from_server.data, sizeof(can_frame_display.can_data));
  }
}