
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
const int k_F = 70;
const int k_N = 78;
const int k_Q = 81;
const int k_b = 98;
const int k_f = 102;
const int k_n = 110;
const int k_q = 113;
}  // namespace key

enum class gear {
  park = 0,
  reverse,
  neutral,
  drive,
};

namespace pedal {
const int8_t k_zero = 0;
const int8_t k_ten = 10;
const int8_t k_twenty = 20;
const int8_t k_thirty = 30;
const int8_t k_forty = 40;
const int8_t k_fifty = 50;
const int8_t k_sixty = 60;
const int8_t k_seventy = 70;
const int8_t k_eighty = 80;
const int8_t k_ninety = 90;
const int8_t k_one_hundred = 100;
}  // namespace pedal

namespace ignition
{
  const int8_t k_off = 0;
  const int8_t k_on = 1;
} // namespace ignition

class UserInput {
 public:
  // Input request variables
  int8_t ignition{};
  int8_t gear{};
  int8_t throttle{};
  int8_t brake{};
  int8_t blinker{};

  // Input char
  int ch{};

  bool Cmd(const int&);
  void SetIgnition(const int8_t&);
  void SetGear(const int&);
  void SetThrottle(const int8_t&);
  void SetBrake(const int8_t&);
  void SetBlinker(const int8_t&);
};

void InitNcurses();

#endif  // SRC_UI_UI_HPP