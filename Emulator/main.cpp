//#include"server.hpp"
#include <iostream>
#include <thread>
#include <mutex>
#include "io_data.hpp"

#include "can_tranceiver.hpp"

// static UserInputCanFrame in_data{};
// static DisplayCanFrame out_data{};
// static std::mutex in_data_mutex{};
// static std::mutex out_data_mutex{};

int main() {
  CanTranceiver can_tranceiver{};

  std::thread can_receive_thread(&CanTranceiver::CanReceive, &can_tranceiver);
  std::thread can_send_thread(&CanTranceiver::CanSend, &can_tranceiver);

  while (can_tranceiver.tranceiver_run) {
    // call engine calculations.
    std::lock_guard<std::mutex> in_lock(in_data_mutex);
    std::lock_guard<std::mutex> out_lock(out_data_mutex);
    out_data.turn_indicator = in_data.turn_indicator + 1;
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
  }

  can_receive_thread.join();
  can_send_thread.join();
}