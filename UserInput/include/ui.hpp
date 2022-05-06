#include <curses.h>
#include <mutex>

#include "candb.hpp"

#ifndef SRC_UI_UI_HPP
#define SRC_UI_UI_HPP

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
const int k_N = 78;
const int k_P = 80;
const int k_Q = 81;
const int k_R = 82;
const int k_S = 83;
const int k_b = 98;
const int k_d = 100;
const int k_f = 102;
const int k_n = 110;
const int k_p = 112;
const int k_q = 113;
const int k_r = 114;
const int k_s = 115;
}  // namespace key

/*!
 * \brief Class to hold user inputs and the methods to set them.
 *
 */
class UserInput {
 public:
  UserInputCanFrame can_frame_bitfield{};

  // Input char
  int ch{};

  bool Cmd();
  void UpdateCanFrameBitfield();
  void SetIgnition();
  void SetGear(const Gear&);
  void SetThrottle(const Pedal&);
  void SetBrake(const Pedal&);
  void SetBlinker(const Blinker&);

  /*! \todo Make these private!  */
  // Input request variables
  Ignition ignition{};
  Gear gear_selection{};
  Pedal throttle{};
  Pedal brake{};
  Blinker blinker{};
};

void InitNcurses();
void SendToCan(const bool&, const UserInputCanFrame&, std::mutex&);

}  // namespace ui

#endif  // SRC_UI_UI_HPP
