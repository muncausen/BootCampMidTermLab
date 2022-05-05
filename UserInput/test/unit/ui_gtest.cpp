#include "ui_gtest.hpp"

#include <cstring>
#include <iostream>

void TestUi::SetUp() {
  if (socket_can.open("vcan0") != scpp::STATUS_OK) {
    std::cout << "Cannot open vcan0." << std::endl;
    std::cout << "Check whether the vcan0 interface is up!" << std::endl;
    exit(-1);
  }
  int eq = memcmp(&ui.can_frame_bitfield, cf_to_write.data, sizeof(ui.can_frame_bitfield));
}

void TestUi::TearDown() {}

TEST_F(TestUi, SetThrottle) {
  ui.Cmd(key::k_0);
  ui.UpdateCanFrameBitfield();
  std::memcpy(cf_to_write.data, &ui.can_frame_bitfield, sizeof(ui.can_frame_bitfield));
  EXPECT_EQ(ui.throttle, Pedal::kZero);
  EXPECT_EQ(0, eq);

  ui.Cmd(key::k_1);
  ui.UpdateCanFrameBitfield();
  std::memcpy(cf_to_write.data, &ui.can_frame_bitfield, sizeof(ui.can_frame_bitfield));
  EXPECT_EQ(ui.throttle, Pedal::kTen);
  EXPECT_EQ(0, eq);

  ui.Cmd(key::k_2);
  ui.UpdateCanFrameBitfield();
  std::memcpy(cf_to_write.data, &ui.can_frame_bitfield, sizeof(ui.can_frame_bitfield));
  EXPECT_EQ(ui.throttle, Pedal::kTwenty);
  EXPECT_EQ(0, eq);

  ui.Cmd(key::k_3);
  ui.UpdateCanFrameBitfield();
  std::memcpy(cf_to_write.data, &ui.can_frame_bitfield, sizeof(ui.can_frame_bitfield));
  EXPECT_EQ(ui.throttle, Pedal::kThirty);
  EXPECT_EQ(0, eq);

  ui.Cmd(key::k_4);
  ui.UpdateCanFrameBitfield();
  std::memcpy(cf_to_write.data, &ui.can_frame_bitfield, sizeof(ui.can_frame_bitfield));
  EXPECT_EQ(ui.throttle, Pedal::kForty);
  EXPECT_EQ(0, eq);

  ui.Cmd(key::k_5);
  ui.UpdateCanFrameBitfield();
  std::memcpy(cf_to_write.data, &ui.can_frame_bitfield, sizeof(ui.can_frame_bitfield));
  EXPECT_EQ(ui.throttle, Pedal::kFifty);
  EXPECT_EQ(0, eq);

  ui.Cmd(key::k_6);
  ui.UpdateCanFrameBitfield();
  std::memcpy(cf_to_write.data, &ui.can_frame_bitfield, sizeof(ui.can_frame_bitfield));
  EXPECT_EQ(ui.throttle, Pedal::kSixty);
  EXPECT_EQ(0, eq);

  ui.Cmd(key::k_7);
  ui.UpdateCanFrameBitfield();
  std::memcpy(cf_to_write.data, &ui.can_frame_bitfield, sizeof(ui.can_frame_bitfield));
  EXPECT_EQ(ui.throttle, Pedal::kSeventy);
  EXPECT_EQ(0, eq);

  ui.Cmd(key::k_8);
  ui.UpdateCanFrameBitfield();
  std::memcpy(cf_to_write.data, &ui.can_frame_bitfield, sizeof(ui.can_frame_bitfield));
  EXPECT_EQ(ui.throttle, Pedal::kEighty);
  EXPECT_EQ(0, eq);

  ui.Cmd(key::k_9);
  ui.UpdateCanFrameBitfield();
  std::memcpy(cf_to_write.data, &ui.can_frame_bitfield, sizeof(ui.can_frame_bitfield));
  EXPECT_EQ(ui.throttle, Pedal::kNinety);
  EXPECT_EQ(0, eq);

  ui.Cmd(key::k_b);
  ui.UpdateCanFrameBitfield();
  std::memcpy(cf_to_write.data, &ui.can_frame_bitfield, sizeof(ui.can_frame_bitfield));
  EXPECT_EQ(ui.throttle, Pedal::kZero);
  EXPECT_EQ(0, eq);

  ui.Cmd(key::k_B);
  ui.UpdateCanFrameBitfield();
  std::memcpy(cf_to_write.data, &ui.can_frame_bitfield, sizeof(ui.can_frame_bitfield));
  EXPECT_EQ(ui.throttle, Pedal::kZero);
  EXPECT_EQ(0, eq);

  ui.Cmd(key::k_f);
  ui.UpdateCanFrameBitfield();
  std::memcpy(cf_to_write.data, &ui.can_frame_bitfield, sizeof(ui.can_frame_bitfield));
  EXPECT_EQ(ui.throttle, Pedal::kOneHundred);
  EXPECT_EQ(0, eq);

  ui.Cmd(key::k_F);
  ui.UpdateCanFrameBitfield();
  std::memcpy(cf_to_write.data, &ui.can_frame_bitfield, sizeof(ui.can_frame_bitfield));
  EXPECT_EQ(ui.throttle, Pedal::kOneHundred);
  EXPECT_EQ(0, eq);
}

TEST_F(TestUi, SetBrake) {
  ui.Cmd(key::k_b);
  ui.UpdateCanFrameBitfield();
  std::memcpy(cf_to_write.data, &ui.can_frame_bitfield, sizeof(ui.can_frame_bitfield));
  EXPECT_EQ(ui.brake, Pedal::kOneHundred);
  EXPECT_EQ(0, eq);

  ui.Cmd(key::k_B);
  ui.UpdateCanFrameBitfield();
  std::memcpy(cf_to_write.data, &ui.can_frame_bitfield, sizeof(ui.can_frame_bitfield));
  EXPECT_EQ(ui.brake, Pedal::kOneHundred);
  EXPECT_EQ(0, eq);
}

TEST_F(TestUi, DISABLED_SetGear) {
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

TEST_F(TestUi, DISABLED_SetBlinker) {}
