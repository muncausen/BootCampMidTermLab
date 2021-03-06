#include "ui.hpp"

#include <chrono>
#include <cstring>
#include <iostream>
#include <thread>

#include "socketcan.hpp"

namespace ui {

/*!
 * \brief Initiates required setup for ncurses.
 */
void InitNcurses() {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
}

/*!
 * \brief Command handling function.
 *
 * \return true so long as the application is supposed to run.
 * \return false when the application should stop and terminate.
 */
bool UserInput::Cmd() {
  bool run = true;

  std::cout << "\rKey value: " << this->ch << ":\t";

  switch (this->ch) {
    case key::k_Q:
    case key::k_q:
      std::cout << "Exiting \n\r";
      this->SendShutdown();
      run = false;
      break;

    case key::k_S:
    case key::k_s:
      this->SetIgnition();
      break;

    case key::k_0:
      this->SetThrottle(Pedal::kZero);
      break;

    case key::k_1:
      this->SetThrottle(Pedal::kTen);
      break;

    case key::k_2:
      this->SetThrottle(Pedal::kTwenty);
      break;

    case key::k_3:
      this->SetThrottle(Pedal::kThirty);
      break;

    case key::k_4:
      this->SetThrottle(Pedal::kForty);
      break;

    case key::k_5:
      this->SetThrottle(Pedal::kFifty);
      break;

    case key::k_6:
      this->SetThrottle(Pedal::kSixty);
      break;

    case key::k_7:
      this->SetThrottle(Pedal::kSeventy);
      break;

    case key::k_8:
      this->SetThrottle(Pedal::kEighty);
      break;

    case key::k_9:
      this->SetThrottle(Pedal::kNinety);
      break;

    case key::k_comma:
      this->SetHandbrake(Handbrake::kOff);
      this->SetBrake(Pedal::kZero);
      break;

    case key::k_period:
    case key::k_B:
    case key::k_b:
      this->SetThrottle(Pedal::kZero);  // Abort cruise control.
      this->SetBrake(Pedal::kOneHundred);
      this->SetHandbrake(Handbrake::kOn);
      break;

    case key::k_D:
    case key::k_d:
      this->SetGear(Gear::kDrive);
      break;

    case key::k_N:
    case key::k_n:
      this->SetGear(Gear::kNeutral);
      break;

    case key::k_F:
    case key::k_f:
      this->SetThrottle(Pedal::kOneHundred);  // Full speed ahead!
      break;

    case key::k_P:
    case key::k_p:
      this->SetGear(Gear::kPark);
      break;

    case key::k_R:
    case key::k_r:
      this->SetGear(Gear::kReverse);
      break;

    case KEY_DOWN:
      this->SetGear(Gear::kNext);
      break;

    case KEY_UP:
      this->SetGear(Gear::kPrevious);
      break;

    case key::k_J:
    case key::k_j:
      this->SetTurnIndicator(TurnIndicator::kLeft);
      break;

    case key::k_K:
    case key::k_k:
      this->SetTurnIndicator(TurnIndicator::kHazard);
      break;

    case key::k_L:
    case key::k_l:
      this->SetTurnIndicator(TurnIndicator::kRight);
      break;

    case key::k_I:
    case key::k_i:
      this->SetTurnIndicator(TurnIndicator::kOff);
      break;

    case key::k_t:
    case key::k_T:
      this->SetSeatbelts();
      break;

    case key::k_y:
    case key::k_Y:
      this->SetDoors();
      break;

    case key::k_u:
    case key::k_U:
      this->SetHighBeam();
      break;

    default:
      std::cout << "Unknown command! \n\r";
      break;
  }

  return run;
}

/*!
 * \brief Increment frame counter and updates the bitfield data from the private variables.
 */
void UserInput::UpdateCanFrameBitfield() {
  std::lock_guard<std::mutex> lk(this->mx);
  this->can_frame_bitfield.ignition = static_cast<uint>(this->ignition);
  this->can_frame_bitfield.gear_select = static_cast<uint>(this->gear_selection);
  this->can_frame_bitfield.throttle = static_cast<uint>(this->throttle);
  this->can_frame_bitfield.brake = static_cast<uint>(this->brake);
  this->can_frame_bitfield.turn_indicator = static_cast<uint>(this->turn_indicator);
  this->can_frame_bitfield.high_beam = static_cast<uint>(this->high_beam);
  this->can_frame_bitfield.seatbelt = static_cast<uint>(this->seatbealt);
  this->can_frame_bitfield.doors = static_cast<uint>(this->doors);
  this->can_frame_bitfield.handbrake = static_cast<uint>(this->handbrake);
}

/*!
 * \brief Sets the value of ignition state.
 *
 */
void UserInput::SetIgnition() {
  switch (this->ignition) {
    case Ignition::kOff:
      this->ignition = Ignition::kOn;
      std::cout << "Ignition on. \n\r";
      break;

    case Ignition::kOn:
      this->SetThrottle(Pedal::kZero);  // Abort cruise control.
      this->SetGear(Gear::kPark);
      this->ignition = Ignition::kOff;
      std::cout << "Ignition off. \n\r";
      break;

    default:
      std::cout << "Ignition error! Unknown ignition state. \n\r";
      break;
  }
}

/*!
 * \brief Sets gear value.
 *
 * \param gr Gear value based on user input.
 */
void UserInput::SetGear(const Gear& gr) {
  std::string curr_gear{};

  switch (gr) {
    case Gear::kPark:
      this->gear_selection = Gear::kPark;
      std::cout << "Gear lever in Park. \n\r";
      break;

    case Gear::kReverse:
      this->gear_selection = Gear::kReverse;
      std::cout << "Gear lever in Reverse. \n\r";
      break;

    case Gear::kNeutral:
      this->gear_selection = Gear::kNeutral;
      std::cout << "Gear lever in Neutral. \n\r";
      break;

    case Gear::kDrive:
      this->gear_selection = Gear::kDrive;
      std::cout << "Gear lever in Drive. \n\r";
      break;

    case Gear::kNext:
      if (Gear::kPark == this->gear_selection) {
        this->gear_selection = Gear::kReverse;
        std::cout << "Gear lever in Reverse. \n\r";
      } else if (Gear::kReverse == this->gear_selection) {
        this->gear_selection = Gear::kNeutral;
        std::cout << "Gear lever in Neutral. \n\r";
      } else if (Gear::kNeutral == this->gear_selection) {
        this->gear_selection = Gear::kDrive;
        std::cout << "Gear lever in Drive. \n\r";
      } else {
        std::cout << "Gear lever no change. \n\r";
        break;
      }
      break;

    case Gear::kPrevious:
      if (Gear::kDrive == this->gear_selection) {
        this->gear_selection = Gear::kNeutral;
        std::cout << "Gear lever in Neutral. \n\r";
      } else if (Gear::kNeutral == this->gear_selection) {
        this->gear_selection = Gear::kReverse;
        std::cout << "Gear lever in Reverse. \n\r";
      } else if (Gear::kReverse == this->gear_selection) {
        this->gear_selection = Gear::kPark;
        std::cout << "Gear lever in Park. \n\r";
      } else {
        std::cout << "Gear lever no change. \n\r";
        break;
      }
      break;

    default:
      std::cout << "Gear error! Really weird gear request. This should not be possible. \n\r";
      break;
  }
}

/*!
 * \brief Sets throttle value with sanity check.
 *
 * \param ped Throttle value from user input.
 */
void UserInput::SetThrottle(const Pedal& ped) {
  if (Pedal::kZero <= ped && ped <= Pedal::kOneHundred) {
    this->throttle = ped;
    std::cout << "Throttle: " << static_cast<int>(this->throttle) << " % \n\r";
  }
}

/*!
 * \brief Sets brake value with sanity check.
 *
 * \param ped Brake value based on user input.
 */
void UserInput::SetBrake(const Pedal& ped) {
  if (Pedal::kZero <= ped && ped <= Pedal::kOneHundred) {
    this->brake = ped;
    std::cout << "Brake: " << static_cast<int>(this->brake) << " % \n\r";
  }
}

/*!
 * \brief Set state of turn indicator.
 *
 * \param ti Turn indicator value based on user input.
 * \todo Implement this input.
 */
void UserInput::SetTurnIndicator(const TurnIndicator& ti) {
  switch (ti) {
    case TurnIndicator::kLeft:
      this->turn_indicator = TurnIndicator::kLeft;
      std::cout << "Turning Left! \n\r";
      break;

    case TurnIndicator::kRight:
      this->turn_indicator = TurnIndicator::kRight;
      std::cout << "Turning Right! \n\r";
      break;

    case TurnIndicator::kHazard:
      this->turn_indicator = TurnIndicator::kHazard;
      std::cout << "Hazard Lights Are ON! \n\r";
      break;

    case TurnIndicator::kOff:
      this->turn_indicator = TurnIndicator::kOff;
      std::cout << "Blinkers Are OFF! \n\r";
      break;

    default:
      std::cout << "Wrong Blinker! \n\r";
      break;
  }
}

/*!
 * \brief Sets the value of high beams state.
 *
 */
void UserInput::SetHighBeam() {
  switch (this->high_beam) {
    case HighBeam::kOn:
      this->high_beam = HighBeam::kOff;
      std::cout << "High Beams off. \n\r";
      break;

    case HighBeam::kOff:
      this->high_beam = HighBeam::kOn;
      std::cout << "High Beams on. \n\r";
      break;

    default:
      break;
  }
}

/*!
 * \brief Sets the value of seat belts state.
 *
 */
void UserInput::SetSeatbelts() {
  switch (this->seatbealt) {
    case SeatBealt::kFasten:
      this->seatbealt = SeatBealt::kUnfasten;
      std::cout << "Fasten Your Seat Belt! \n\r";
      break;

    case SeatBealt::kUnfasten:
      this->seatbealt = SeatBealt::kFasten;
      std::cout << "Seat Belts Fastened. \n\r";
      break;

    default:
      break;
  }
}

/*!
 * \brief Sets the value of doors state.
 *
 */
void UserInput::SetDoors() {
  switch (this->doors) {
    case Doors::kClose:
      this->doors = Doors::kOpen;
      std::cout << "Doors Open! \n\r";
      break;

    case Doors::kOpen:
      this->doors = Doors::kClose;
      std::cout << "Doors Closed!. \n\r";
      break;

    default:
      break;
  }
}
/*!
 * \brief Set state of handbrake.
 *
 * \param hb Handbrake value based on user input.
 */
void UserInput::SetHandbrake(const Handbrake& hb) {
  switch (hb) {
    case Handbrake::kOn:
      this->handbrake = Handbrake::kOn;
      std::cout << "TOKYO DRIFT LET'S GO! \n\r";
      break;

    case Handbrake::kOff:
      this->handbrake = Handbrake::kOff;
      std::cout << "Handbrake released. \n\r";
      break;

    default:
      break;
  }
}

/*!
 * \brief Starts the CanSender() thread and detaches it.
 *
 */
void UserInput::StartCanSenderThread() {
  this->can_sender_run = true;
  std::thread can_thread(&ui::UserInput::CanSend, this);
  can_thread.detach();
}

/*!
 * \brief Stops the CanSender() thread.
 *
 */
void UserInput::StopCanSenderThread() { this->can_sender_run = false; }

/*!
 * \brief Populates a can frame and sends it on the CAN bus. Intended to run in own thread.
 *
 */
void UserInput::CanSend() {
  scpp::SocketCan socket_can;

  if (socket_can.open("vcan0") != scpp::STATUS_OK) {
    std::cout << "Cannot open vcan0." << std::endl;
    std::cout << "Check whether the vcan0 interface is up!" << std::endl;
    return;
  }

  scpp::SocketCanStatus write_status{};

  while (this->can_sender_run) {
    {  // Lock mutex and update.
      std::lock_guard<std::mutex> lk(this->mx);
      this->can_frame_bitfield.frame_counter++;
      write_status =
          socket_can.write(kUserInputCanFrameId, sizeof(this->can_frame_bitfield), &this->can_frame_bitfield);
    }  // Realese at end of scope.

    if (write_status != scpp::STATUS_OK) std::cout << "SocketCAN write error code: " << int32_t(write_status) << "\n";

    // Send CAN frame periodically.
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}
/*!
 * \brief Sends a shutdown frame id to the Emulator and Display module.
 *
 */
void UserInput::SendShutdown() {
  scpp::SocketCan socket_can_shutdown;
  scpp::SocketCanStatus write_status{};
  char c = 'd';  // Empty data

  if (socket_can_shutdown.open("vcan0") != scpp::STATUS_OK) {
    std::cout << "Cannot open vcan0." << std::endl;
    std::cout << "Check whether the vcan0 interface is up!" << std::endl;
    return;
  }

  // Sending 10 frames with dummy data with a shutdown ID
  for (size_t i = 0; i < 10; i++) {
    write_status = socket_can_shutdown.write(kShutdownCanFrameId, sizeof(c), &c);
    if (write_status != scpp::STATUS_OK) std::cout << "SocketCAN write error code: " << int32_t(write_status) << "\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
}

}  // namespace ui
