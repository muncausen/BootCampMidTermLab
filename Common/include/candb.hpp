#ifndef CANDB_HPP_
#define CANDB_HPP_

/*!
 * \brief CAN frame structure from user input to emulator module.
 *
 */
struct UserInputCanFrame {
  unsigned frame_counter : 4;
  unsigned ignition : 2;
  unsigned gear_select : 4;
  unsigned throttle : 8;
  unsigned brake : 8;
  unsigned blinkers : 2;
};

/*!
 * \brief CAN frame structure from emulator to display module.
 *
 */
struct DisplayCanFrame {
  unsigned frame_counter : 4;
  unsigned ignition : 2;
  unsigned gear_select : 4;
  unsigned speed : 8;
  unsigned rpm : 8;
  unsigned blinkers : 2;
  unsigned automatic_gear : 3;
};

/*!
 * \brief Enum representation of ignition state.
 *
 */
enum class Ignition {
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
  kNext,
  kPrevious,
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

#endif  // CANDB_HPP_