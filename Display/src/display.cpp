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
  scpp::CanFrame can_from_server;
  if (sockat_can.read(can_from_server) == scpp::STATUS_OK) {
    memcpy(&can_frame_display.can_data, can_from_server.data, sizeof(can_frame_display.can_data));
    printf("len %d byte, id: %d, data: %02x %02x %02x %02x  \n", can_from_server.len, can_from_server.id,
           can_from_server.data[0], can_from_server.data[1], can_from_server.data[2], can_from_server.data[3]);
  }
  //***********************FOR TEST*********************

  cout << "Received CNTR: " << static_cast<int>((can_from_server.data[0] & 0xf0) >> 4) << endl;
  cout << "CNTR: " << static_cast<int>(can_frame_display.can_data.frame_counter) << endl;
  cout << "IGNITION: " << static_cast<int>(can_frame_display.can_data.ignition) << endl;
  cout << "GEAR: " << static_cast<int>(can_frame_display.can_data.gear_select) << endl;
  cout << "ACCEL: " << static_cast<int>(can_frame_display.can_data.speed) << endl;
  cout << "BRAKE: " << static_cast<int>(can_frame_display.can_data.rpm) << endl;
  cout << "BLINKs: " << static_cast<int>(can_frame_display.can_data.blinkers) << endl;
}
//*********************END FOR TEST********************
