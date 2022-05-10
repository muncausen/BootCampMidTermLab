#include "engine.hpp"
#include "server.hpp"

Server server_obj;
Server* server = &server_obj;
const static clock_t delay_up = 1;
const static clock_t delay_down = 5;
clock_t coef;
void Engine::EngineSimulation(const uint8_t& to_thr, unsigned int& rpm, unsigned int& speed, unsigned int& gear) {
  int to_throttle = static_cast<int> (to_thr/10); //change % to number(T index)
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
              Delay(coef);
              fb_gear = GearChange(rpm_, T[from_throttle][g][GearIndx], T[to_throttle][g][GearIndx]);
              fb_speed = GearChange(speed_, T[from_throttle][g][SpeedIndx], T[to_throttle][g][SpeedIndx]);
              printf("ENGINE:: RPM : %d  Speed %d  GEAR  %d  \n", rpm_, speed_, gear_);
              server_obj.GetEngineValues(rpm_, speed_, gear_);
              speed = this->speed_;
              rpm = this->rpm_;
              gear = this->gear_;
//              cout << "RPM: " << rpm_  << "  Speed " <<speed_ << "  Gear: " << gear_<<endl;
          } while (fb_gear || fb_speed);
      }
  }
  from_throttle = to_throttle;
}

bool Engine::GearChange(int &val, const int &val_start, const int &val_end)
{
    int val_out= 0;
    bool val_feedback{false};
    val_out = val_start < val_end ? val + (val_end-val_start)/10: val - (val_start-val_end)/30;
    if (val_end > val_start){ //  got to Higher Throttle
        if ((val_out >= val_end) ){
            val = val_end;
            val_feedback = false;
        } else {
            val = val_out;
            val_feedback = true;
            coef = delay_up;
        }
    } else{ //  go to Lower Throttle
        if (val_out > val_end) {
            val = val_out;
            val_feedback = true;
            coef = delay_down;
        } else  {
            val = val_end;
            val_feedback = false;
        }
    }
    return val_feedback;
}



void Engine::Delay(const clock_t& coef) {
  clock_t now = clock();
  while (clock() - now < coef * CLOCKS_PER_SEC / 10)
    ;
}