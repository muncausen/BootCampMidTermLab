#include <iostream>
#include <thread>

#include "display.hpp"
using namespace std;

int main() {
  CanReceiver *can_receiver = nullptr;
  can_receiver = new CanReceiver();

  can_receiver->OpenCan();
  while (true) {
    can_receiver->CanFromServer();
  }

  return 0;
}