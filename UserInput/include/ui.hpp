
#include <curses.h>
#include "candb.hpp"

#ifndef SRC_UI_UI_HPP
#define SRC_UI_UI_HPP

// Constants for key inputs
namespace key {
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
const int k_b = 98;
const int k_d = 100;
const int k_f = 102;
const int k_n = 110;
const int k_p = 112;
const int k_q = 113;
const int k_r = 114;
}  // namespace key

/*!
 * \brief Enum representation of ignition state.
 *
 */
enum class Ignition
{
  kOff = 0,
  kOn,
};

/*!
 * \brief Enum representation of gear selector position.
 *
 */
enum class Gear {
  kPark = 0,
  kReverse,
  kNeutral,
  kDrive,
};

/*!
 * \brief Enum representation of pedal input in 10% increments.
 *
 */
enum class Pedal {
  kZero = 0,
  kTen = 10,
  kTwenty = 20,
  kThirty = 30,
  kForty = 40,
  kFifty = 50,
  kSixty = 60,
  kSeventy = 70,
  kEighty = 80,
  kNinety = 90,
  kOneHundred = 100,
};

/*!
 * \brief Enum representation of blinker state.
 *
 */
enum class Blinker {
  kOff = 0,
  kRight,
  kLeft,
  kWarning,
};

/*!
 * \brief Class to hold user inputs and the methods to set them.
 *
 */
class UserInput {
 public:
  // Input request variables
  Ignition ignition{};
  Gear gear_selection{};
  Pedal throttle{};
  Pedal brake{};
  Blinker blinker{};

  UserInputCanFrame can_frame_bitfield{};

  // Input char
  int ch{};

  bool Cmd(const int&);
  void UpdateCanFrameBitfield();
  void SetIgnition(const Ignition&);
  void SetGear(const int&);
  void SetThrottle(const Pedal&);
  void SetBrake(const Pedal&);
  void SetBlinker(const Blinker&);
};

void InitNcurses();

#endif  // SRC_UI_UI_HPP
