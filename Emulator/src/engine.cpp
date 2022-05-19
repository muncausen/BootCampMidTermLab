#include "engine.hpp"
/*
in Neutral throttle = X
Brake = 0
go to Drive, it should speed up to throttle x
but it waits for new throttle!!
*/

/*!
 * \brief Receives Acceleration request from the user on CAN bus
 *
 * \return True if requested values are inside boundaries.
 */
bool Engine::Torquerequest(const UserInputCanFrame &in_data, DisplayCanFrame &out_data) {
  {
    std::lock_guard<std::mutex> lock(in_data_mutex);
    from_ui = in_data;
  }
  unsigned which_smooth = 0;

  cout << " in Torque request..." << from_ui.throttle << endl;
  smooth_map[0] = SmoothDecrease;
  smooth_map[1] = SmoothIncrease;
  smooth_map[2] = SameThrottle;
  if (from_ui.throttle > engine_tune.to_throttle) {
    g = 0;
    bool_gear = true;
    bool_speed = true;
    which_smooth = 1;
  } else if (from_ui.throttle < engine_tune.to_throttle) {
    g = 0;
    bool_gear = true;
    bool_speed = true;
    which_smooth = 0;
  } else {
    which_smooth = 2;
  }
  usage_mode = SetUsageMode(from_ui.ignition, from_ui.gear_select);
  EngineSimulation(from_ui.throttle, usage_mode, out_data, DELAY_UP, smooth_map[which_smooth]);

  {
    std::lock_guard<std::mutex> out_lock(out_data_mutex);
    out_data.frame_counter = from_ui.frame_counter;
    out_data.gear_select = from_ui.gear_select;
    out_data.ignition = from_ui.ignition;
    out_data.turn_indicator = from_ui.turn_indicator;
    out_data.brake = from_ui.brake;
  }
  return true;
}
/*!
 * \brief Vehicle State. based on Ignition and Gear the user entered.
 *
 * \return UsageModes: Park, Available, Reverse, Movable, Drivable and Off
 */
Engine::UsageMode Engine::SetUsageMode(const unsigned &ignition, const unsigned &user_gear) {
  switch (ignition) {
    case IGNITION_STATE_KOFF:  // Ignition::kOff
      usage_mode = UsageMode::kOff;
      break;
    case IGNITION_STATE_KON:
      switch (user_gear) {
        case GEAR_STATE_KPARK:  // kPark
          usage_mode = UsageMode::kAvalaible;
          from_ui.throttle = 0;
          engine_tune.prev_throttle = 0;
          break;
        case GEAR_STATE_KREVERSE:  // kReverse,
          usage_mode = UsageMode::kRevers;
          break;
        case GEAR_STATE_KNEUTRAL:  // kNeutral,
          usage_mode = UsageMode::kMovable;
          break;
        case GEAR_STATE_KDRIVE:  // kDrive,
          usage_mode = UsageMode::kDrive;
          break;
        default:
          usage_mode = UsageMode::kAvalaible;
      }
    default:
      break;
  }
  return usage_mode;
}
/*!
 * \brief Base on Throttle and UsageMode, calculates RPM, Speed and Gear
 *
 * \return Calculated values are stored in private members of Engine class.
 */
void Engine::EngineSimulation(const unsigned &from_ui_throtthe, const UsageMode &usage_mode, DisplayCanFrame &out_data,
                              clock_t DELAY, SmoothingFunctionPointer SmoothFcn) {
  engine_tune.to_throttle = (from_ui_throtthe / 10);  // change % to number(T index)
  int g_t = 0;

  //   for (g_t = 0; g_t < MAX_GEAR + GEAR_TRANSISSION; g_t++) {
  //     if (T[engine_tune.to_throttle][g_t][SPEED_INDEX] >=
  //         T[engine_tune.from_throttle][MAX_GEAR + GEAR_TRANSISSION][SPEED_INDEX]) {
  //       g = g_t;
  //     }
  //   }

  engine_tune.to_spd = T[engine_tune.to_throttle][g][SPEED_INDEX];
  engine_tune.to_rpm = T[engine_tune.to_throttle][g][RPM_INDEX];
  Delay(DELAY);
  bool_gear = SmoothFcn(rpm_, engine_tune.from_rpm, engine_tune.to_rpm, RPM_STEP);
  bool_speed = SmoothFcn(speed_, engine_tune.from_spd, engine_tune.to_spd, SPEED_STEP);
  if ((g < GEAR_TRANSISSION + MAX_GEAR)) {
    if (!bool_gear && !bool_speed) {
      engine_tune.from_spd = T[engine_tune.to_throttle][g][SPEED_INDEX];
      engine_tune.from_rpm = T[engine_tune.to_throttle][g][RPM_INDEX];
      g++;
      gear_ = T[engine_tune.to_throttle][g][0];
    }
  } else {
    engine_tune.prev_throttle = engine_tune.to_throttle;
  }
  printf("ENGINE:: G: %d   Gear  %d  bool_gear %d  bool_speed %d \n", g,  gear_,
         bool_gear, bool_speed);

  // unordered_map<UsageMode, DisplayCanFrame> out_data_map;
  //  out_data_map: {frame_counter, ignition, gear_select, speed, rpm, TI, automatic_gear}
  out_data_map[UsageMode::kDrive] = {
      from_ui.frame_counter, from_ui.ignition, from_ui.gear_select, speed_, rpm_, from_ui.turn_indicator, gear_};
  out_data_map[UsageMode::kMovable] = {
      from_ui.frame_counter, from_ui.ignition, from_ui.gear_select, 0, rpm_, from_ui.turn_indicator, 0};
  out_data_map[UsageMode::kAvalaible] = {
      from_ui.frame_counter, from_ui.ignition, from_ui.gear_select, 0, MINMUM_RPM, from_ui.turn_indicator, 0};
  out_data_map[UsageMode::kRevers] = {
      from_ui.frame_counter, from_ui.ignition, from_ui.gear_select, speed_ / REVERES_SPEED_RATIO, rpm_, 0, gear_};
  out_data_map[UsageMode::kOff] = {from_ui.frame_counter, from_ui.ignition, 0, 0, 0, 0, 0};
  /*                    */
  {
    std::lock_guard<std::mutex> out_lock(out_data_mutex);
    out_data = out_data_map[usage_mode];
  }

  //  } while (bool_gear || bool_speed);
  //}  //(g = g_t; g<MAX_GEAR + GEAR_TRANSISSION+1 ; g++)
}
/*!
 * \brief SmoothIncrease and SmoothSpeedIncrease make it possible to move smoothly between RPMs and speed
 *
 *
 * \return false if rpm/speed reaches to its to value
 */
bool Engine::SmoothIncrease(unsigned &val, const unsigned &val_start, const unsigned &val_end, const unsigned step) {
  int val_out = 0;
  bool val_feedback{false};
  val_out = val + step;
  if (val_end > val_start) {
    if ((val_out < val_end)) {
      val = val_out;
      val_feedback = true;
    } else {
      val = val_end;
      val_feedback = false;
    }
  }
  return val_feedback;
}

/*!
 * \brief SmoothDecrease and SmoothSpeedIncrease make it possible to move smoothly between RPMs and speed
 *
 *
 * \return false if rpm/speed reaches to its to value
 */
bool Engine::SmoothDecrease(unsigned &val, const unsigned &val_start, const unsigned &val_end, const unsigned step) {
  int val_out = 0;
  bool val_feedback{false};
  val_out = val - step;
  if (val_end < val_start) {
    if ((val_out > val_end)) {
      val = val_out;
      val_feedback = true;
    } else {
      val = val_end;
      val_feedback = false;
    }
  }
  return val_feedback;
}

bool Engine::SameThrottle(unsigned &val, const unsigned &val_start, const unsigned &val_end, const unsigned step) {
  bool val_feedback = true;
  ;
  DELAY = DELAY_UP;
  return val_feedback;
}

void Engine::Delay(const clock_t &DELAY) {
  clock_t now = clock();
  while (clock() - now < DELAY * CLOCKS_PER_SEC / 100)
    // while (clock() - now < DELAY * CLOCKS_PER_SEC / 10)
    /// 10 will be removed then DELAY will be * 10 and after each itteration DELAY will inc/decreas ....
    ;
}