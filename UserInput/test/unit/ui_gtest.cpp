#include "ui_gtest.hpp"

#include <iostream>

using namespace std;

void TestUi::SetUp() {}

void TestUi::TearDown() {}

TEST_F(TestUi, SetThrottle) {
  UserInput ui{};

  ui.Cmd(key::k_0);
  EXPECT_EQ(ui.throttle, Pedal::kZero);

  ui.Cmd(key::k_1);
  EXPECT_EQ(ui.throttle, Pedal::kTen);

  ui.Cmd(key::k_2);
  EXPECT_EQ(ui.throttle, Pedal::kTwenty);

  ui.Cmd(key::k_3);
  EXPECT_EQ(ui.throttle, Pedal::kThirty);

  ui.Cmd(key::k_4);
  EXPECT_EQ(ui.throttle, Pedal::kForty);

  ui.Cmd(key::k_5);
  EXPECT_EQ(ui.throttle, Pedal::kFifty);

  ui.Cmd(key::k_6);
  EXPECT_EQ(ui.throttle, Pedal::kSixty);

  ui.Cmd(key::k_7);
  EXPECT_EQ(ui.throttle, Pedal::kSeventy);

  ui.Cmd(key::k_8);
  EXPECT_EQ(ui.throttle, Pedal::kEighty);

  ui.Cmd(key::k_9);
  EXPECT_EQ(ui.throttle, Pedal::kNinety);

  ui.Cmd(key::k_b);
  EXPECT_EQ(ui.throttle, Pedal::kZero);

  ui.Cmd(key::k_B);
  EXPECT_EQ(ui.throttle, Pedal::kZero);

  ui.Cmd(key::k_f);
  EXPECT_EQ(ui.throttle, Pedal::kOneHundred);

  ui.Cmd(key::k_F);
  EXPECT_EQ(ui.throttle, Pedal::kOneHundred);
}

TEST_F(TestUi, SetBrake) {
  UserInput ui{};

  ui.Cmd(key::k_b);
  EXPECT_EQ(ui.brake, Pedal::kOneHundred);

  ui.Cmd(key::k_B);
  EXPECT_EQ(ui.brake, Pedal::kOneHundred);
}

TEST_F(TestUi, DISABLED_SetGear) {
  UserInput ui{};

  ui.Cmd(key::k_r);
  EXPECT_EQ(ui.gear_selection, Gear::kReverse);

  ui.Cmd(key::k_R);
  EXPECT_EQ(ui.gear_selection, Gear::kReverse);

  ui.Cmd(key::k_d);
  EXPECT_EQ(ui.gear_selection, Gear::kDrive);

  ui.Cmd(key::k_D);
  EXPECT_EQ(ui.gear_selection, Gear::kDrive);

  ui.Cmd(key::k_n);
  EXPECT_EQ(ui.gear_selection, Gear::kNeutral);

  ui.Cmd(key::k_N);
  EXPECT_EQ(ui.gear_selection, Gear::kNeutral);

  ui.Cmd(key::k_p);
  EXPECT_EQ(ui.gear_selection, Gear::kPark);

  ui.Cmd(key::k_P);
  EXPECT_EQ(ui.gear_selection, Gear::kPark);
}

TEST_F(TestUi, DISABLED_SetIgnition) {
  UserInput ui{};
  
  ui.Cmd(0);
  EXPECT_EQ(ui.ignition, Ignition::kOff);

  ui.Cmd(1);
  EXPECT_EQ(ui.ignition, Ignition::kOn);
}

TEST_F(TestUi, SetBlinker) {}
