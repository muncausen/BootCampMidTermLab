#include "can_tranceiver.hpp"

#include <stdio.h>

#include <cstring>
#include <mutex>
#include <thread>

void CanTranceiver::CanReceive(UserInputCanFrame& in_data, std::mutex& in_data_mutex, std::atomic<bool>& run) {
  scpp::SocketCan socket_can;
  scpp::CanFrame in_frame;

  if (socket_can.open("vcan0") != scpp::STATUS_OK) {
    std::cout << "Cannot open vcan0." << std::endl;
    std::cout << "Check whether the vcan0 interface is up!" << std::endl;
    exit(-1);
  }

  while (run) {
    if (socket_can.read(in_frame) == scpp::STATUS_OK) {
      if (in_frame.id == kUserInputCanFrameId) {
        std::lock_guard<std::mutex> lock(in_data_mutex);
        memcpy(&in_data, in_frame.data, sizeof(in_data));
      } else if (in_frame.id == kShutdownCanFrameId) {
        run = false;
      }
    }
  }
};

void CanTranceiver::CanSend(DisplayCanFrame& out_data, std::mutex& out_data_mutex, std::atomic<bool>& run) {
  scpp::SocketCan socket_can;

  if (socket_can.open("vcan0") != scpp::STATUS_OK) {
    std::cout << "Cannot open vcan0." << std::endl;
    std::cout << "Check whether the vcan0 interface is up!" << std::endl;
    exit(-1);
  }

  scpp::SocketCanStatus write_sc_status{};

  while (run) {
    {
      std::lock_guard<std::mutex> lock(out_data_mutex);
      out_data.frame_counter++;
      write_sc_status = socket_can.write(kDisplayCanFrameId, sizeof(out_data), &out_data);
    }

    if (write_sc_status != scpp::STATUS_OK) {
      std::cout << "SocketCAN write error code: " << int32_t(write_sc_status) << "\n";
    }

   std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}
