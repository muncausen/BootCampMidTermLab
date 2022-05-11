//#include <chrono>
#include "your_stuff.hpp"

#include <cstring>
#include <iostream>
#include <thread>

#include "can_common.hpp"
#include "candb.hpp"

void yourStuff::YouHaveJustRecievedACANFrame(const canfd_frame *const _frame) {
  DisplayCanFrame display_can_frame;
  switch (_frame->can_id) {
    case 0x123: {  // change to can_id
      //memcpy of bitfields
      memcpy(&display_can_frame, _frame->data, sizeof(DisplayCanFrame));
      this->InstrumentCluster.ignite(display_can_frame.ignition);
      this->InstrumentCluster.setRPM(display_can_frame.rpm);
      this->InstrumentCluster.setSpeed(display_can_frame.speed);
      this->InstrumentCluster.setGearPindle_int(display_can_frame.automatic_gear);
      this->InstrumentCluster.setGear(display_can_frame.gear_select);
      this->InstrumentCluster.setTXT("Engine is ON");
      

    } break;
    default:
      break;
  }
}

/******************************* ANYTHING BELOW THIS LINE IS JUST BORING STUFF *******************************/

yourStuff::yourStuff(const std::string &_ifName, QObject *_vs) {
  if (!(this->CANReader.open(_ifName))) exit(-1);  // emit die();

  this->InstrumentCluster.init(_vs);

  this->startTimer(1);
}

bool yourStuff::run() {
  bool ret = true;
  CANOpener::ReadStatus status = CANOpener::ReadStatus::OK;
  canfd_frame frame;
  this->CANReader.read(&frame);
  /*while*/ if (status == CANOpener::ReadStatus::OK) { this->YouHaveJustRecievedACANFrame(&frame); }
  if (status == CANOpener::ReadStatus::ERROR)
    ret = false;
  else if (status == CANOpener::ReadStatus::NAVAL || status == CANOpener::ReadStatus::ENDOF)
    this->Counter++;
  else
    this->Counter = 0;
  // if (this->Counter > 200) ret = false;
  return ret;
}

void yourStuff::timerEvent(QTimerEvent *) {
  if (this->run())
    ;
  else {
    //    emit this->die();
    exit(-1);
  }
}
