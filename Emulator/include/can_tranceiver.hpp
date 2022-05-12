
#ifndef CAN_RECEIVER_HPP
#define CAN_RECEIVER_HPP
#include <iostream>
#include <mutex>
#include <atomic>

#include "candb.hpp"
#include "socketcan.hpp"

class CanTranceiver {
 public:
  CanTranceiver() = default;
  void CanReceive(UserInputCanFrame&, std::mutex&, std::atomic<bool>&);
  void CanSend(DisplayCanFrame&, std::mutex&, std::atomic<bool>&);
};

#endif