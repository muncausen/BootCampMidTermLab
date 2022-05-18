#ifndef SRC_UI_UI_HPP
#define SRC_UI_UI_HPP

#include <curses.h>

#include <atomic>
#include <mutex>

#include "candb.hpp"

// Hack to access private members in unit tests
#ifdef BUILD_TESTS
#define private public
#endif  // BUILD_TESTS

namespace ui {

// Constants for key inputs
namespace key {
const int k_comma = 44;
const int k_period = 46;
const int k_0 = 48;
const int k_1 = 49;
const int k_2 = 50;
const int k_3 = 51;
const int k_4 = 52;
const int k_5 = 53;
const int k_6 = 54;
const int k_7 = 55;
const int k_8 = 56;
const int k_9 = 57;
const int k_B = 66;
const int k_D = 68;
const int k_F = 70;
const int k_I = 73;
const int k_J = 74;
const int k_K = 75;
const int k_L = 76;
const int k_N = 78;
const int k_P = 80;
const int k_Q = 81;
const int k_R = 82;
const int k_S = 83;
const int k_T = 84;
const int k_U = 85;
const int k_Y = 89;
const int k_b = 98;
const int k_d = 100;
const int k_f = 102;
const int k_i = 105;
const int k_j = 106;
const int k_k = 107;
const int k_l = 108;
const int k_n = 110;
const int k_p = 112;
const int k_q = 113;
const int k_r = 114;
const int k_s = 115;
const int k_t = 116;
const int k_u = 117;
const int k_y = 121;

}  // namespace key

/*!
 * \brief Class to hold user inputs and the methods to set them.
 *
 */
class UserInput {
 public:
  int ch{};  //!< Input char value.

  UserInput() = default;
  bool Cmd();
  void UpdateCanFrameBitfield();
  void SetIgnition();
  void SetGear(const Gear&);
  void SetThrottle(const Pedal&);
  void SetBrake(const Pedal&);
  void SetTurnIndicator(const TurnIndicator&);
  void SetSeatbelts();
  void SetDoors();
  void SetHighBeam();
  void SetHandbrake(const Handbrake&);
  void StartCanSenderThread();
  void StopCanSenderThread();
  void SendShutdown();

 private:
  UserInputCanFrame can_frame_bitfield{};
  Ignition ignition{};
  Gear gear_selection{};
  Pedal throttle{};
  Pedal brake{};
  TurnIndicator turn_indicator{};
  HighBeam high_beam{};
  SeatBealt seatbealt{};
  Doors doors{};
  Handbrake handbrake{};
  std::atomic<bool> can_sender_run{};
  std::mutex mx{};

  void CanSend();
};

void InitNcurses();

}  // namespace ui

#endif  // SRC_UI_UI_HPP
