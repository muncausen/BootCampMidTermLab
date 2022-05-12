#include <iostream>
#include <mutex>
#include <thread>

#include "can_tranceiver.hpp"
#include "io_data.hpp"

int main() {
  // Create a CAN receiver/sender and spawn its threads.
  CanTranceiver can_tranceiver{};
  std::thread can_receive_thread(&CanTranceiver::CanReceive, std::ref(can_tranceiver), std::ref(in_data),
                                 std::ref(in_data_mutex), std::ref(tranceiver_run));
  std::thread can_send_thread(&CanTranceiver::CanSend, std::ref(can_tranceiver), std::ref(out_data),
                              std::ref(out_data_mutex), std::ref(tranceiver_run));

  while (tranceiver_run) {
    // Need to call engine calculations.

    // Some dummy operation to prove data transfere.
    {
      std::lock_guard<std::mutex> in_lock(in_data_mutex);
      std::lock_guard<std::mutex> out_lock(out_data_mutex);
      out_data.speed = in_data.throttle * 2;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
  }

  can_receive_thread.join();
  can_send_thread.join();
}