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
  unsigned high_beam : 2;       //!< High beams state, 2 bit.
  unsigned seatbelt : 2;        //!< Seatbelts state, 2 bit.
  unsigned doors : 2;           //!< Doors state, 2 bit.
};

/*!
 * \brief CAN frame structure from emulator to display module.
 *
 */
struct DisplayCanFrame {
  unsigned frame_counter : 4;   //!< Incremental frame counter, 4 bit.
  unsigned ignition : 2;        //!< Ignition state, 2 bit.
  unsigned gear_select : 4;     //!< Gear selection PRND, 4 bit.
  unsigned speed : 9;           //!< Vehicle speed, 9 bit.
  unsigned rpm : 13;            //!< Engine RPM, 13 bit.
  unsigned turn_indicator : 2;  //!< Turn indicator incl. warning, 2 bit.
  unsigned automatic_gear : 3;  //!< Current gear engaged, 3 bit.
  unsigned brake : 1;           //!< Brake request, 8 bit.
  unsigned high_beam : 2;       //!< High beams state, 2 bit.
  unsigned seatbelt : 2;        //!< Seatbelts state, 2 bit.
  unsigned doors :2;            //!< Doors state, 2 bit.
};

/*!
 * \brief Const CAN frame IDs.
 *
 */
static const uint32_t kUserInputCanFrameId{0x0AA};
static const uint32_t kDisplayCanFrameId{0x0BB};
static const uint32_t kShutdownCanFrameId{0x0CC};

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
  kHazard,
};

/*!
 * \brief Enum representation of high beams state.
 *
 */
enum class HighBeam {
  kOff = 0,
  kOn,
};

/*!
 * \brief Enum representation of seatbelts state.
 *
 */
enum class SeatBealt {
  kFasten = 0,
  kUnfasten,
};

/*!
 * \brief Enum representation of doors state.
 *
 */
enum class Doors {
  kClose = 0,
  kOpen,
};

#endif  // CANDB_HPP_