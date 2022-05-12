//#include"server.hpp"
#include <iostream>
#include <thread>

#include "can_tranceiver.hpp"
#include "server.hpp"
using namespace std;

int main() {
  CanTranceiver *can_tranceiver_ = nullptr;
  can_tranceiver_ = new CanTranceiver();
  Server *server_ = nullptr;
  server_ = new Server;
  cout << "MAIN is runing..." << endl;
  can_tranceiver_->OpenCan();
//  thread opencan_thread(&CanTranceiver::OpenCan, can_tranceiver_);
//  opencan_thread.join();
  while (true) {
    can_tranceiver_->CanFromUI();
    server_->StartEmulate(can_tranceiver_->getCanFrame());
  }
}