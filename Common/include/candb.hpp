#ifndef CANDB_HPP_
#define CANDB_HPP_

#include <cinttypes>

/*!
 * \brief CAN frame structure from user input to emulator module.
 *
 */
struct UserInputCanFrame {
  unsigned frame_counter : 4;   //!< Incremental frame counter, 4 bit.
  unsigned ignition : 2;        //!< Ignition state, 2 bit.
  unsigned gear_select : 4;     //!< Gear selection PRND, 4 bit.
  unsigned throttle : 8;        //!< Throttle request, 8 bit.
  unsigned brake : 8;           //!< Brake request, 8 bit.
  unsigned turn_indicator : 2;  //!< Turn indicator incl. warning, 2 bit.
};

/*!
 * \brief CAN frame structure from emulator to display module.
 *
 */
struct DisplayCanFrame {
  unsigned frame_counter : 4;   //!< Incremental frame counter, 4 bit.
  unsigned ignition : 2;        //!< Ignition state, 2 bit.
  unsigned gear_select : 4;     //!< Gear selection PRND, 4 bit.
  unsigned speed : 8;           //!< Vehicle speed, 8 bit.
  unsigned rpm : 8;             //!< Engine RPM, 8 bit.
  unsigned turn_indicator : 2;  //!< Turn indicator incl. warning, 2 bit.
  unsigned automatic_gear : 3;  //!< Current gear engaged, 3 bit.
};


/*!
 * \brief Const CAN frame IDs.
 *
 */
static const uint32_t kUserInputCanFrameId{0x0AA};
static const uint32_t kDisplayCanFrameId{0x0BB};

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
 * \brief Enum representation of turn indicator state.
 *
 */
enum class TurnIndicator {
  kOff = 0,
  kRight,
  kLeft,
  kWarning,
};

#endif  // CANDB_HPP_