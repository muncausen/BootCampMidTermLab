#include "can_tranceiver.hpp"

#include <stdio.h>

#include <cstring>
#include <mutex>

#include "server.hpp"

bool CanTranceiver::OpenCan() {
  if (sockat_can.open("vcan0") != scpp::STATUS_OK) {
    std::cout << "Cannot open vcan0." << std::endl;
    std::cout << "Check whether the vcan0 interface is up!" << std::endl;
    exit(-1);
  } else {
    cout << "VCAN0 is up'n Running..." << endl;
  }
}

bool CanTranceiver::CanFromUI() {
  mutex can_mutex;
  //    CanDispData candata;
  scpp::CanFrame can_from_ui;
  if (sockat_can.read(can_from_ui) == scpp::STATUS_OK) {
    {
      const std::lock_guard<std::mutex> lock(can_mutex);
      memcpy(&can_ui_frame.can_data, can_from_ui.data, sizeof(UserInputCanFrame));
    }
  }
  return sockat_can.read(can_from_ui) == scpp::STATUS_OK;
};

bool CanTranceiver::CanToDisplay(const DisplayCanFrame& can_from_server) {
  bool write_disp_status{true};
  scpp::CanFrame can_frame_to_display;
  can_frame_to_display.id = 99;
  can_frame_to_display.len = 4;
//  printf("CAN: Auto Gear : %d \n", can_from_server.gear_select);
  memcpy(can_frame_to_display.data, &can_from_server, sizeof(DisplayCanFrame));
  if (sockat_can.open("vcan0") == scpp::STATUS_OK) {
    auto write_sc_status = sockat_can.write(can_frame_to_display);
    if (write_sc_status != scpp::STATUS_OK) {
      printf("something went wrong on socket write, error code : %d \n", int32_t(write_sc_status));
      write_disp_status = false;
    }
  } else {
    std::cout << "///Cannot open vcan0, then Open it!." << std::endl;
    OpenCan();
    sockat_can.write(can_frame_to_display);
  }

  //    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  return write_disp_status;
}
UserInputCanFrame CanTranceiver::getCanFrame() { return can_ui_frame.can_data; }