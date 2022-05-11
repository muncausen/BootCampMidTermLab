#include "engine.hpp"
#include "server.hpp"

Server server_obj;
Server* server = &server_obj;

clock_t coef;

bool Engine::Torquerequest(const uint8_t& requested_throttle, const uint8_t& ignition, const uint8_t& user_gear){
    uint8_t IGNITION = 1;
    cout << " is usage mode OFF? : " << (this->usage_mode == UsageMode::kOff) <<  endl;
    bool is_ok{false};
    if (IGNITION){
        SetUsageMode(IGNITION, user_gear); // sets public variable: usage_mode
        if ((requested_throttle < 100) && (requested_throttle > 0)){
            if (this->usage_mode != UsageMode::kOff)
                EngineSimulation(requested_throttle, this->usage_mode);
            is_ok = true;
        } else{
            is_ok = false;
        }
    } else { 
        is_ok = false;
        cout << "Vehicle is in OFF state";}
    return is_ok;
}
void Engine::SetUsageMode(const uint8_t& ignition, const uint8_t& user_gear){
    cout << "Set up Usage mode..." << endl;
    cout << "GEAR : " << static_cast<int>(user_gear) << "  ignition " <<static_cast<int>(ignition) << endl;
    switch (ignition) {
        case IGNITION_STATE_KOFF: //Ignition::kOff
            this->usage_mode = UsageMode::kOff;
            cout << "0: GEAR : " << static_cast<int>(user_gear) << "  ignition " <<static_cast<int>(ignition) << endl;
            break;
        case IGNITION_STATE_KON:
        cout << "1: GEAR : " << static_cast<int>(user_gear) << "  ignition " <<static_cast<int>(ignition) << endl;
        switch (user_gear){
            case GEAR_STATE_KPARK: // kPark
                this->usage_mode = UsageMode::kAvalaible;
                cout << "2: GEAR : " << static_cast<int>(user_gear) << "  ignition " <<static_cast<int>(ignition) << endl;
                break;
            case GEAR_STATE_KREVERSE: //kReverse,
                this->usage_mode = UsageMode::kRevers;
                cout << "3 : GEAR : " << static_cast<int>(user_gear) << "  ignition " <<static_cast<int>(ignition) << endl;
                break;
            case GEAR_STATE_KNEUTRAL: //kNeutral,
                this->usage_mode = UsageMode::kMovable;
                cout << "4 : GEAR : " << static_cast<int>(user_gear) << "  ignition " <<static_cast<int>(ignition) << endl;
                break;
            case GEAR_STATE_KDRIVE: //kDrive,
                this->usage_mode = UsageMode::kDrive;
                cout << "5 : GEAR : " << static_cast<int>(user_gear) << "  ignition " <<static_cast<int>(ignition) << endl;
                break;
            default:
                this->usage_mode = UsageMode::kAvalaible;
        }
        default:
        this->usage_mode = UsageMode::kOff;
    }
}
void Engine::EngineSimulation(const uint8_t& to_thr, const UsageMode& usage_mode) {
  int to_throttle = static_cast<int> (to_thr/10); //change % to number(T index)
  int g_t=0;
  int rpm_{T[from_throttle][g][GEAR_INDEX]}; // to start calculating gear and speed from the ongoing state 
  int speed_{T[from_throttle][g][SPEED_INDEX]};
  bool fb_gear{false};
  bool fb_speed{false};
  int g = MAX_GEAR + GEAR_TRANSISSION;

  for (g_t = 0; g_t < MAX_GEAR + GEAR_TRANSISSION ; g_t++){
      if (T[to_throttle][g_t][SPEED_INDEX] >= T[from_throttle][MAX_GEAR + GEAR_TRANSISSION][SPEED_INDEX]){ // to find speed in to_thr match the final speed in from_throttle to jump to proper culumn of to_thr
          break;
      }
  }
  if (from_throttle != to_throttle){
      for (g= g_t; g<11; g++){
        gear_ = T[to_throttle][g][0];
          do{
              Delay(coef);
              fb_gear = SpeedRPMCalc(rpm_, T[from_throttle][g][GEAR_INDEX], T[to_throttle][g][GEAR_INDEX],GEAR_STEP);
              fb_speed = SpeedRPMCalc(speed_, T[from_throttle][g][SPEED_INDEX], T[to_throttle][g][SPEED_INDEX],  SPEED_STEP);
    //          printf("ENGINE:: RPM : %d  Speed %d  GEAR  %d  \n", rpm_, speed_, gear_);
              if (usage_mode == UsageMode::kAvalaible){
                  speed_ = 0;
                  rpm_ =  750;
                  gear_ = 0;
              }
              if (usage_mode == UsageMode::kMovable){
                  speed_ = 0;
                  gear_ = 0;
              }
              server_obj.GetEngineValues(rpm_, speed_, gear_);
          } while (fb_gear || fb_speed);
      }
  }
  from_throttle = to_throttle;
}

bool Engine::SpeedRPMCalc(int &val, const int &val_start, const int &val_end, const int& step) {
    int val_out= 0;
    bool val_feedback{false};
    val_out = val_start < val_end ? val + (val_end-val_start)/10: val - /*(val_start-val_end)/*/step;
    if (val_end > val_start){ //  got to Higher Throttle
        if ((val_out >= val_end) ){
            val = val_end;
            val_feedback = false;
        } else {
            val = val_out;
            val_feedback = true;
            coef = DELAY_UP;
        }
    } else{ //  go to Lower Throttle
        if (val_out > val_end) {
            val = val_out;
            val_feedback = true;
            coef = DELAY_DOWN;
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