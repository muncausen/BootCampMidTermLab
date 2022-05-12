#include "engine.hpp"

clock_t coef;

bool Engine::Torquerequest(const UserInputCanFrame& in_data, DisplayCanFrame& out_data){
    {
    std::lock_guard<std::mutex> lock(in_data_mutex);
    from_ui = in_data;
    }

    usage_mode = SetUsageMode(from_ui.ignition, from_ui.gear_select);
    EngineSimulation(from_ui.throttle, usage_mode, out_data);

    return true;
}
Engine::UsageMode Engine::SetUsageMode(const unsigned& ignition, const unsigned& user_gear){
    switch (ignition) {
        case IGNITION_STATE_KOFF: //Ignition::kOff
            usage_mode = UsageMode::kOff;
            break;
        case IGNITION_STATE_KON:
        switch (user_gear){
            case GEAR_STATE_KPARK: // kPark
                usage_mode = UsageMode::kAvalaible;
                break;
            case GEAR_STATE_KREVERSE: //kReverse,
                usage_mode = UsageMode::kRevers;
                break;
            case GEAR_STATE_KNEUTRAL: //kNeutral,
                usage_mode = UsageMode::kMovable;
                break;
            case GEAR_STATE_KDRIVE: //kDrive,
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
void Engine::EngineSimulation(const unsigned& to_thr, const UsageMode& usage_mode, DisplayCanFrame& out_data) {

    const int to_throttle = (to_thr/10); //change % to number(T index)
    int g_t=0;
    int g = MAX_GEAR + GEAR_TRANSISSION;
    int rpm_{T[from_throttle][g][RPM_INDEX]}; // to start calculating gear and speed from the ongoing state 
    int speed_{T[from_throttle][g][SPEED_INDEX]};
    bool fb_gear{false};
    bool fb_speed{false};
    bool up_down{true};
    if (from_throttle < to_throttle){
        up_down = true;
    } else{up_down = false;}
    for (g_t = 0; g_t < MAX_GEAR + GEAR_TRANSISSION ; g_t++){
        if (T[to_throttle][g_t][SPEED_INDEX] >= T[from_throttle][MAX_GEAR + GEAR_TRANSISSION][SPEED_INDEX]){ // to find speed in to_thr match the final speed in from_throttle to jump to proper culumn of to_thr
            break;
        }}
//    if (from_throttle != to_throttle){
        from_rpm = T[from_throttle][g][RPM_INDEX];
        for (g = g_t; g<MAX_GEAR + GEAR_TRANSISSION+1 ; g++){
            fb_gear = true;
            fb_speed = true;
            gear_ = T[to_throttle][g][0];
            if (from_spd == 0){
                to_spd = T[to_throttle][0][SPEED_INDEX];
                to_rpm = T[to_throttle][0][RPM_INDEX];
            } else {to_rpm = T[to_throttle][g][RPM_INDEX];
                    to_spd = T[to_throttle][g][SPEED_INDEX];
            }
            do{
                Delay(coef);
                if (up_down){
                fb_gear = SpeedRPMCalc(rpm_, from_rpm, to_rpm,RPM_STEP);
                fb_speed = SpeedRPMCalc(speed_, from_spd, to_spd,  SPEED_STEP);
                } else{
                fb_speed = SpeedRPMCalcDec(speed_, from_spd, to_spd,  SPEED_STEP);
                fb_gear = SpeedRPMCalcDec(rpm_, from_rpm, to_rpm,RPM_STEP);
                }
                /*                    */
                {
                std::lock_guard<std::mutex> out_lock(out_data_mutex);
                switch (usage_mode)
                {
                case UsageMode::kDrive:
                cout << "Drive mode \n";
                  out_data.rpm = rpm_;
                  out_data.speed = speed_;
                  out_data.automatic_gear = gear_;
                  out_data.gear_select = in_data.gear_select;
                  out_data.ignition = in_data.ignition;
                  break;
                case UsageMode::kMovable:
                cout << "Movable \n";
                  out_data.rpm = rpm_;
                  out_data.speed = 0;
                  out_data.automatic_gear = 0;
                  out_data.gear_select = in_data.gear_select;
                  out_data.ignition = in_data.ignition;
                  break;
                case UsageMode::kOff:
                cout << "OFF mode \n";
                  out_data.rpm = 0;
                  out_data.speed = 0;
                  out_data.automatic_gear = 0;
                  out_data.gear_select = in_data.gear_select;
                  out_data.ignition = in_data.ignition;
                  break;
                case UsageMode::kRevers:
                cout << "Revers mode \n";
                  out_data.rpm = rpm_;
                  out_data.speed = speed_/10;
                  out_data.automatic_gear = gear_;
                  out_data.gear_select = in_data.gear_select;
                  out_data.ignition = in_data.ignition;
                  break;
                default:
                  out_data.rpm = 0;
                  out_data.speed = 0;
                  out_data.automatic_gear = 0;
                  out_data.gear_select = in_data.gear_select;
                  out_data.ignition = in_data.ignition;
                  break;
                }
                }
                printf("ENGINE:: RPM : %d  Speed %d  GEAR  %d  usage mode %d \n",
                 out_data.rpm, out_data.speed, out_data.automatic_gear, usage_mode);
            } while (fb_gear || fb_speed);
            from_spd = T[to_throttle][g][SPEED_INDEX];
            from_rpm = T[to_throttle][g][RPM_INDEX];
            rpm_ = from_rpm;
            speed_ = from_spd;
        }
//    }
    from_throttle = to_throttle;
}

bool Engine::SpeedRPMCalc(int &val, const int &val_start, const int &val_end, const int step) {
 int val_out= 0;
    bool val_feedback{false};
    val_out = val_end > val_start ? val + step: val - step;
    if (val_start < val_end){ //  got to Higher Throttle
        if ((val_out >= val_end) ){
            val = val_end;
            val_feedback = false;
        } else {
            val = val_out;
            val_feedback = true;
            coef = DELAY_UP;
        }
    } else{      
          val = val_end;
          val_feedback = false;
    }
    return val_feedback;
}

bool Engine::SpeedRPMCalcDec(int &val, const int &val_start, const int &val_end, const int step) {
    int val_out= 0;
    bool val_feedback{false};
    val_out = val_end > val_start ? val + (val_end-val_start)/step: val - /*(val_start-val_end)/*/step;
    if (val_start > val_end){ //  got to Higher Throttle
        if ((val_out <= val_end) ){
            val_feedback = false;
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
    }
    return val_feedback;
}

void Engine::Delay(const clock_t& coef) {
  clock_t now = clock();
  while (clock() - now < coef * CLOCKS_PER_SEC / 10)
    ;
}