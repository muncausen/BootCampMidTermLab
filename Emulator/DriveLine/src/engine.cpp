#include "engine.hpp"

#include "ui.hpp"

void Engine::GearCalc(const uint8_t& throtle, const uint8_t& user_gear, const uint8_t& ignition, const uint8_t& brake) {
  clock_t d[]{2 * CLOCKS_PER_SEC, 15 * CLOCKS_PER_SEC, 8 * CLOCKS_PER_SEC, 5 * CLOCKS_PER_SEC, 2 * CLOCKS_PER_SEC};
  if (true /*ignition == static_cast<uint>(Ignition::kOn)*/
      && (user_gear > static_cast<uint>(Gear::kNeutral))) {
    if (throtle && !brake) {
      if (gear_ < MAX_AUTO_GRARE) {
        for (int i = 0; i < MAX_AUTO_GRARE; i++) {
          Delay(d[i]);
          ++gear_;
          printf("Auto Gear.. %d\n ", gear_);
        }  // for
      }    // if (gear_ < MAX_AUTO_GRARE) {
    } else {
      gear_ = static_cast<uint>(Gear::kPark);
      printf("Auto Gear: %d\n ", gear_);
    }       // if (throtle)
  } else {  // if (true /*ig
    gear_ = static_cast<uint>(Gear::kPark);
    printf("Auto Gear: %d\n ", gear_);
  }
}
void Engine::Rpm(const uint8_t& throtle, const uint8_t& gear) { rpm_ = throtle * 3 / gear; }
void Engine::Speed(const uint8_t& rpm, const uint8_t& gear) { speed_ = rpm / gear; }
uint8_t Engine::getRpm() const { return rpm_; }
uint8_t Engine::getSpeed() const { return speed_; }
uint8_t Engine::getGear() const { return gear_; }

void Delay(const clock_t& delay) {
  clock_t now = clock();
  while (clock() - now < delay / 10)
    ;
}