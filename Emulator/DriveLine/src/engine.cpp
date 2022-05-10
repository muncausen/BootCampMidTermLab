#include "engine.hpp"

#include "ui.hpp"
clock_t delay = 1 * CLOCKS_PER_SEC;
void Engine::EngineSimulation(const uint8_t& to_thr, const uint8_t& user_gear, const uint8_t& ignition, const uint8_t& brake) {
  int to_throttle = static_cast<int> (to_thr/10);
//  printf(" in ENGIN from server %d , casted to int %i \n", to_thr, to_throttle);
  int g_t=0;
  int rpm_{T[from_throttle][g][GearIndx]}; // to start calculating gear and speed from the ongoing state 
  int speed_{T[from_throttle][g][SpeedIndx]};
  bool fb_gear{false};
  bool fb_speed{false};
  int g = MAX_GEAR + GEAR_TRANSISSION;

  for (g_t=0; g_t < MAX_GEAR + GEAR_TRANSISSION ; g_t++){
      if (T[to_throttle][g_t][SpeedIndx] >= T[from_throttle][MAX_GEAR + GEAR_TRANSISSION][SpeedIndx]){ // to find speed in to_thr match the final speed in from_throttle to jump to proper culumn of to_thr
          break;
      }
  }
  if (from_throttle != to_throttle){
      for (g= g_t; g<11; g++){
        gear_ = T[to_throttle][g][0];
//          cout << "   Gear: " << T[to_throttle][g][0] << endl;
          do{
              Delay(delay);
              fb_gear = GearChange(rpm_, T[from_throttle][g][GearIndx], T[to_throttle][g][GearIndx]);
              fb_speed = SpeedChange(speed_, T[from_throttle][g][SpeedIndx], T[to_throttle][g][SpeedIndx]);
              cout << "RPM: " << rpm_  << "  Speed " <<speed_ << "  Gear: " << gear_<<endl;
          } while (fb_gear || fb_speed);
      }
  }
  from_throttle = to_throttle;
}

uint8_t Engine::getRpm() const { return static_cast<uint> (rpm_); }
uint8_t Engine::getSpeed() const { return static_cast<uint> (speed_); }
uint8_t Engine::getGear() const { return static_cast<uint> (gear_); }

bool Engine::GearChange(int &rpm, const int &rpm_start, const int &rpm_end)
{
    int rpm_out= 0;
    bool rpm_feedback{false};
    rpm_out = rpm_start < rpm_end ? rpm + (rpm_end-rpm_start)/10: rpm - (rpm_start-rpm_end)/10;
    if (rpm_end >= rpm_start){ //  got to Higher Throttle
        if ((rpm_out <= rpm_end) ){
            rpm = rpm_out;
            rpm_feedback = true;
            delay = 1 * CLOCKS_PER_SEC;
        } else {
            rpm = rpm_end;
            rpm_feedback = false;
        }
    } else{ //  go to Lower Throttle
        if (rpm_out >= rpm_end) {
            rpm = rpm_out;
            rpm_feedback = true;
            delay = 10 * CLOCKS_PER_SEC;
        } else  {
            rpm = rpm_end;
            rpm_feedback = false;
        }
    }
    return rpm_feedback;
}

bool Engine::SpeedChange(int &speed, const int &speed_start, const int &speed_end)
{
    int speed_out= 0;
    bool speed_feedback{false};
    speed_out = speed_start < speed_end ? speed + (speed_end-speed_start)/10: speed - (speed_start-speed_end)/10;
     if (speed_end >= speed_start){ //  got to Higher Throttle
        if (speed_out <= speed_end) {
            speed = speed_out;
            speed_feedback = true;
            delay = 1 * CLOCKS_PER_SEC;
        } else {
            speed = speed_end;
            speed_feedback = false;
        }
     } else { // got to Lower Throttle
         if (speed_out >= speed_end) {
            speed = speed_out;
            speed_feedback = true;
            delay = 10 * CLOCKS_PER_SEC;
        } else  {
            speed = speed_end;
            speed_feedback = false;
        }
     }
    return speed_feedback;
}

void Engine::Delay(const clock_t& delay) {
  clock_t now = clock();
  while (clock() - now < delay / 10)
    ;
}