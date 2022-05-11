
#ifndef CAN_RECEIVER_HPP
#define CAN_RECEIVER_HPP
#include <atomic>
#include <iostream>

#include "candb.hpp"
#include "socketcan.hpp"

class CanTranceiver {
 public:
  CanTranceiver() = default;
  //  CanDispData can_data;  // test using shift and & methode
  bool OpenCan();
  void CanReceive();
  void CanSend();
  std::atomic<bool> tranceiver_run{true};

 private:
};

//} //namespace CanReceiver

//
#endif