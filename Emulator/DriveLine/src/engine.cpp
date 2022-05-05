#include "engine.hpp"

#include "ui.hpp"

void Engine::GearCalc(const uint8_t& throtle, const uint8_t& user_gear, const uint8_t& ignition) {
  clock_t d[]{2 * CLOCKS_PER_SEC, 10 * CLOCKS_PER_SEC, 15 * CLOCKS_PER_SEC, 25 * CLOCKS_PER_SEC, 35 * CLOCKS_PER_SEC};
  if (ignition == static_cast<uint>(Ignition::kOn)) {
    if (user_gear > static_cast<uint>(Gear::kPark)) {
      for (int i = 0; i < 5; i++) {
        if (gear_ > static_cast<uint>(Gear::kNeutral)) {
          Delay(d[i]);
          ++gear_;
          printf("Gear %d \n ", gear_);
        } else {
          printf("Gear %d \n ", gear_);
        }
      }
    } else {
      rpm_ = 800;
    }
  } else {
    rpm_ = 0;
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
  cout << "Message Show after delay that you entered " << clock() - now << endl;
  int main();
}