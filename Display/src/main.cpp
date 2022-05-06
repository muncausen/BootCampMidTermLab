#include <iostream>
#include <thread>

#include "display.hpp"
using namespace std;

int main() {
  CanReceiver *can_receiver = nullptr;
  can_receiver = new CanReceiver();

  thread opencan_thread(&CanReceiver::OpenCan, can_receiver);
  opencan_thread.join();
  while (true) {
    thread receive_can_thread(&CanReceiver::CanFromServer, can_receiver);
    receive_can_thread.join();
  }

  return 0;
}