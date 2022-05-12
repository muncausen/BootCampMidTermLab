
#ifndef ENGINE_HPP
#define ENGINE_HPP
//#include "ui.hpp"
#include <cstdio>
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;
class Server;
class Engine {
 private:
  int rpm_{0};
  int speed_{0};
  int gear_{0};
  
  public:
    // RPM is a variable of throtle and Gear
    // speed is a variable of Rpm, Gear and if car is in movable mode(gear&ignition)
    // if gear != 0 means ignotion = kOn
    // if Ignition is kOn the:
    // Gear is auto, we assume the load is constant
    // if gear is higer than kPark then will increas constantly in time a max.
    enum class UsageMode{
      kOff,       //Ignition == kOff
      kAvalaible, //Ignition== kOn && Gear == kPark
      kMovable,   //Ignition == kOn && Gear = kNeutral
      kDrive,     //Ignition == kOn && Gear == kDrive
      kRevers     // Ignition == kOn && Gear kReverse
    };
    UsageMode usage_mode{UsageMode::kOff};
    int from_throttle{0};
    int to_rpm{0};
    int from_rpm{750};
    int to_spd{0};
    int from_spd{0};
    const static int MAX_GEAR = 6;
    const static int GEAR_TRANSISSION = 5;
  //  int g = GEAR_TRANSISSION + MAX_GEAR;
    const static int RPM_INDEX= 2;
    const static int SPEED_INDEX= 1;
    const static int SPEED_STEP{5};
    const static int GEAR_STEP{10};
    const static clock_t DELAY_UP = 1;
    const static clock_t DELAY_DOWN = 3;
    void Delay(const clock_t&);
    bool SpeedRPMCalc(int &rpm, const int &rpm_start, const int &rpm_end, const int);
    bool SpeedRPMCalcDec(int &val, const int &val_start, const int &val_end, const int step);
    UsageMode SetUsageMode(const uint8_t, const uint8_t&);
    bool Torquerequest(const uint8_t&, const uint8_t&, const uint8_t&);
    void EngineSimulation(const uint8_t&, const UsageMode&);

    vector<vector<vector<int>>> T{
      /*              0               1               2             3               4               5               6               7               8             9                 10*/
      /*th0%*/  {{0, 0, 750},    {0, 0, 750},   {0, 0, 750},   {0, 0, 750},   {0, 0, 750},    {0, 0, 750},    {0, 0, 750},    {0, 0, 750},    {0, 0, 750},    {0, 0, 750},    {0, 0, 750},    {0, 0, 750}},   //NO_LINT
      /*th10%*/ {{1, 6, 1000},   {1, 6, 620},   {2, 9, 1000},  {2, 9, 620},   {3, 15, 1000},  {3, 15, 1000},  {3, 15, 1000},  {3, 15, 1000},  {3, 15, 1000},  {3, 15, 1000},  {3, 15, 1000},  {3, 15, 1000}}, //NO_LINT
      /*th20%*/ {{1, 13, 1200},  {1, 13, 720},  {2, 18, 1200}, {2, 18, 720},  {3, 26, 1200},  {3, 26, 1200},  {3, 26, 1200},  {3, 26, 1200},  {3, 26, 1200},  {3, 26, 1200},  {3, 26, 1200},  {3, 26, 1200}}, //NO_LINT
      /*th30%*/ {{1, 19, 1500},  {1, 19, 900},  {2, 27, 1500}, {2, 27, 900},  {3, 39, 1500},  {3, 39, 900},   {4, 56, 1500},  {4, 56, 1500},  {4, 56, 1500},  {4, 56, 1500},  {4, 56, 1500},  {4, 56, 1500}}, //NO_LINT
      /*th40%*/ {{1, 25, 2000},  {1, 25, 1400}, {2, 36, 2000}, {2, 36, 1400}, {3, 57, 2000},  {3, 57, 1400},  {4, 75, 2000},  {4, 75, 1400},  {5, 89, 2000},  {5, 89, 2000},  {5, 89, 2000},  {5, 89, 2000}}, //NO_LINT
      /*th50%*/ {{1, 32, 2500},  {1, 32, 1750}, {2, 45, 2500}, {2, 45, 1750}, {3, 66, 2500},  {3, 66, 1750},  {4, 94, 2500},  {4, 94, 1750},  {5, 112, 2500}, {5, 112, 1750}, {5, 112, 2500}, {5, 112, 2500}}, //NO_LINT
      /*th60%*/ {{1, 38, 3000},  {1, 38, 2100}, {2, 54, 3000}, {2, 54, 2100}, {3, 79, 3000},  {3, 79, 2100},  {4, 112, 3000}, {4, 112, 2100}, {5, 134, 3000}, {5, 132, 2100}, {6, 201, 3000}, {6, 201, 3000}},//NO_LINT
      /*th70%*/ {{1, 44, 3500},  {1, 44, 2500}, {2, 63, 3500}, {2, 63, 2500}, {3, 92, 3500},  {3, 92, 2500},  {4, 131, 3500}, {4, 131, 2500}, {5, 156, 3500}, {5, 156, 2500}, {6, 234, 3500}, {6, 234, 3500}},//NO_LINT
      /*th80%*/ {{1, 50, 4000},  {1, 50, 2800}, {2, 72, 4000}, {2, 72, 2800}, {3, 105, 4000}, {3, 105, 2800}, {4, 150, 4000}, {4, 150, 2800}, {5, 178, 4000}, {5, 178, 2800}, {6, 268, 4000}, {6, 268, 4000}},//NO_LINT
      /*th90%*/ {{1, 57, 4500},  {1, 57, 3200}, {2, 81, 4500}, {2, 81, 3200}, {3, 118, 4500}, {3, 118, 3200}, {4, 169, 4500}, {4, 169, 3200}, {5, 201, 4500}, {5, 201, 3200}, {6, 301, 4500}, {6, 301, 4500}},//NO_LINT
      /*th100%*/ {{1, 63, 5000}, {1, 63, 3800}, {2, 91, 5000}, {2, 91, 3800}, {3, 131, 5000}, {3, 131, 3800}, {4, 187, 5000}, {4, 187, 3800}, {5, 223, 5000}, {5, 223, 3800}, {6, 335, 5000}, {6, 335, 5000}}};//NO_LINT
      }; // class ENGINE END 
  const static uint8_t IGNITION_STATE_KON = 1;
  const static uint8_t IGNITION_STATE_KOFF = 0;
  const static uint8_t GEAR_STATE_KPARK = 0;
  const static uint8_t GEAR_STATE_KREVERSE = 1;
  const static uint8_t GEAR_STATE_KNEUTRAL = 2;
  const static uint8_t GEAR_STATE_KDRIVE = 3;
#endif  // #ifndef ENGINE_HPP