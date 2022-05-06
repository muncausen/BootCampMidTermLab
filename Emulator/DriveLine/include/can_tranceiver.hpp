
#ifndef CAN_RECEIVER_HPP
#define CAN_RECEIVER_HPP
#include <candb.hpp>
#include <iostream>
#include <memory>

#include "socketcan.hpp"
using namespace std;

// namespace UserInput {
struct CanUIData {
  uint8_t frame_cntr;
  uint8_t ignition;
  uint8_t gear;
  uint8_t acceleration_req;
  uint8_t brake_req;
  uint8_t blinkers;
};
struct CanDispData {
  uint8_t frame_cntr;
  uint8_t ignition;
  uint8_t gear;
  uint8_t speed;
  uint8_t rpm;
  uint8_t blinkers;
};
struct CanUIFrame {
  uint32_t can_id;
  uint8_t can_dlc;
  UserInputCanFrame can_data;
};

class CanTranceiver {
  CanUIFrame can_ui_frame{};

 public:
  CanTranceiver() = default;
  //  CanDispData can_data;  // test using shift and & methode
  scpp::SocketCan sockat_can;
  bool OpenCan();
  bool CanFromUI();
  bool CanToDisplay(const DisplayCanFrame&);
  UserInputCanFrame getCanFrame();
};

//} //namespace CanReceiver

//
#endif