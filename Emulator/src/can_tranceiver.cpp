#include "can_tranceiver.hpp"

#include <stdio.h>

#include <cstring>
#include <mutex>
#include <thread>

#include "io_data.hpp"

void CanTranceiver::CanReceive() {
  scpp::SocketCan socket_can;
  scpp::CanFrame in_frame;

  if (socket_can.open("vcan0") != scpp::STATUS_OK) {
    std::cout << "Cannot open vcan0." << std::endl;
    std::cout << "Check whether the vcan0 interface is up!" << std::endl;
    exit(-1);
  } else {
    std::cout << "VCAN0 is up'n Running..." << std::endl;
  }

  while (this->tranceiver_run) {
    if (socket_can.read(in_frame) == scpp::STATUS_OK) {
      if (in_frame.id == kUserInputCanFrameId) {
        std::lock_guard<std::mutex> lock(in_data_mutex);
        memcpy(&in_data, in_frame.data, sizeof(in_data));
      } else if (in_frame.id == kShutdownCanFrameId) {
        this->tranceiver_run = false;
      }
    }
  }
};

void CanTranceiver::CanSend() {
  scpp::SocketCan socket_can;

  if (socket_can.open("vcan0") != scpp::STATUS_OK) {
    std::cout << "Cannot open vcan0." << std::endl;
    std::cout << "Check whether the vcan0 interface is up!" << std::endl;
    exit(-1);
  } else {
    std::cout << "VCAN0 is up'n Running..." << std::endl;
  }

  scpp::SocketCanStatus write_sc_status{};

  while (this->tranceiver_run) {
    {
      std::lock_guard<std::mutex> lock(in_data_mutex);
      write_sc_status = socket_can.write(kDisplayCanFrameId, sizeof(out_data), 0, &out_data);
    }

    if (write_sc_status != scpp::STATUS_OK) {
      std::cout << "SocketCAN write error code: " << int32_t(write_sc_status) << "\n";
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}
