#include "ui_gtest.hpp"
#include "candb.hpp"

#include <cstring>
#include <iostream>

void TestUi::SetUp() {
  if (socket_can.open("vcan0") != scpp::STATUS_OK) {
    std::cout << "Cannot open vcan0." << std::endl;
    std::cout << "Check whether the vcan0 interface is up!" << std::endl;
    exit(-1);
  }
}

void TestUi::TearDown() {}

TEST_F(TestUi, SetThrottle) {
  ui.ch = ui::key::k_0;
  ui.Cmd();
  ui.UpdateCanFrameBitfield();
  std::memcpy(cf_to_write.data, &ui.can_frame_bitfield, sizeof(ui.can_frame_bitfield));
  EXPECT_EQ(ui.throttle, Pedal::kZero);
  EXPECT_EQ(0, memcmp(&ui.can_frame_bitfield, cf_to_write.data, sizeof(ui.can_frame_bitfield)));

  ui.ch = ui::key::k_1;
  ui.Cmd();
  ui.UpdateCanFrameBitfield();
  std::memcpy(cf_to_write.data, &ui.can_frame_bitfield, sizeof(ui.can_frame_bitfield));
  EXPECT_EQ(ui.throttle, Pedal::kTen);
  EXPECT_EQ(0, memcmp(&ui.can_frame_bitfield, cf_to_write.data, sizeof(ui.can_frame_bitfield)));

  ui.ch = ui::key::k_2;
  ui.Cmd();
  ui.UpdateCanFrameBitfield();
  std::memcpy(cf_to_write.data, &ui.can_frame_bitfield, sizeof(ui.can_frame_bitfield));
  EXPECT_EQ(ui.throttle, Pedal::kTwenty);
  EXPECT_EQ(0, memcmp(&ui.can_frame_bitfield, cf_to_write.data, sizeof(ui.can_frame_bitfield)));

  ui.ch = ui::key::k_3;
  ui.Cmd();
  ui.UpdateCanFrameBitfield();
  std::memcpy(cf_to_write.data, &ui.can_frame_bitfield, sizeof(ui.can_frame_bitfield));
  EXPECT_EQ(ui.throttle, Pedal::kThirty);
  EXPECT_EQ(0, memcmp(&ui.can_frame_bitfield, cf_to_write.data, sizeof(ui.can_frame_bitfield)));

  ui.ch = ui::key::k_4;
  ui.Cmd();
  ui.UpdateCanFrameBitfield();
  std::memcpy(cf_to_write.data, &ui.can_frame_bitfield, sizeof(ui.can_frame_bitfield));
  EXPECT_EQ(ui.throttle, Pedal::kForty);
  EXPECT_EQ(0, memcmp(&ui.can_frame_bitfield, cf_to_write.data, sizeof(ui.can_frame_bitfield)));

  ui.ch = ui::key::k_5;
  ui.Cmd();
  ui.UpdateCanFrameBitfield();
  std::memcpy(cf_to_write.data, &ui.can_frame_bitfield, sizeof(ui.can_frame_bitfield));
  EXPECT_EQ(ui.throttle, Pedal::kFifty);
  EXPECT_EQ(0, memcmp(&ui.can_frame_bitfield, cf_to_write.data, sizeof(ui.can_frame_bitfield)));

  ui.ch = ui::key::k_6;
  ui.Cmd();
  ui.UpdateCanFrameBitfield();
  std::memcpy(cf_to_write.data, &ui.can_frame_bitfield, sizeof(ui.can_frame_bitfield));
  EXPECT_EQ(ui.throttle, Pedal::kSixty);
  EXPECT_EQ(0, memcmp(&ui.can_frame_bitfield, cf_to_write.data, sizeof(ui.can_frame_bitfield)));

  ui.ch = ui::key::k_7;
  ui.Cmd();
  ui.UpdateCanFrameBitfield();
  std::memcpy(cf_to_write.data, &ui.can_frame_bitfield, sizeof(ui.can_frame_bitfield));
  EXPECT_EQ(ui.throttle, Pedal::kSeventy);
  EXPECT_EQ(0, memcmp(&ui.can_frame_bitfield, cf_to_write.data, sizeof(ui.can_frame_bitfield)));

  ui.ch = ui::key::k_8;
  ui.Cmd();
  ui.UpdateCanFrameBitfield();
  std::memcpy(cf_to_write.data, &ui.can_frame_bitfield, sizeof(ui.can_frame_bitfield));
  EXPECT_EQ(ui.throttle, Pedal::kEighty);
  EXPECT_EQ(0, memcmp(&ui.can_frame_bitfield, cf_to_write.data, sizeof(ui.can_frame_bitfield)));

  ui.ch = ui::key::k_9;
  ui.Cmd();
  ui.UpdateCanFrameBitfield();
  std::memcpy(cf_to_write.data, &ui.can_frame_bitfield, sizeof(ui.can_frame_bitfield));
  EXPECT_EQ(ui.throttle, Pedal::kNinety);
  EXPECT_EQ(0, memcmp(&ui.can_frame_bitfield, cf_to_write.data, sizeof(ui.can_frame_bitfield)));

  ui.ch = ui::key::k_b;
  ui.Cmd();
  ui.UpdateCanFrameBitfield();
  std::memcpy(cf_to_write.data, &ui.can_frame_bitfield, sizeof(ui.can_frame_bitfield));
  EXPECT_EQ(ui.throttle, Pedal::kZero);
  EXPECT_EQ(0, memcmp(&ui.can_frame_bitfield, cf_to_write.data, sizeof(ui.can_frame_bitfield)));

  ui.ch = ui::key::k_B;
  ui.Cmd();
  ui.UpdateCanFrameBitfield();
  std::memcpy(cf_to_write.data, &ui.can_frame_bitfield, sizeof(ui.can_frame_bitfield));
  EXPECT_EQ(ui.throttle, Pedal::kZero);
  EXPECT_EQ(0, memcmp(&ui.can_frame_bitfield, cf_to_write.data, sizeof(ui.can_frame_bitfield)));

  ui.ch = ui::key::k_f;
  ui.Cmd();
  ui.UpdateCanFrameBitfield();
  std::memcpy(cf_to_write.data, &ui.can_frame_bitfield, sizeof(ui.can_frame_bitfield));
  EXPECT_EQ(ui.throttle, Pedal::kOneHundred);
  EXPECT_EQ(0, memcmp(&ui.can_frame_bitfield, cf_to_write.data, sizeof(ui.can_frame_bitfield)));

  ui.ch = ui::key::k_F;
  ui.Cmd();
  ui.UpdateCanFrameBitfield();
  std::memcpy(cf_to_write.data, &ui.can_frame_bitfield, sizeof(ui.can_frame_bitfield));
  EXPECT_EQ(ui.throttle, Pedal::kOneHundred);
  EXPECT_EQ(0, memcmp(&ui.can_frame_bitfield, cf_to_write.data, sizeof(ui.can_frame_bitfield)));
}

TEST_F(TestUi, SetBrake) {
  ui.ch = ui::key::k_b;
  ui.Cmd();
  ui.UpdateCanFrameBitfield();
  std::memcpy(cf_to_write.data, &ui.can_frame_bitfield, sizeof(ui.can_frame_bitfield));
  EXPECT_EQ(ui.brake, Pedal::kOneHundred);
  EXPECT_EQ(0, memcmp(&ui.can_frame_bitfield, cf_to_write.data, sizeof(ui.can_frame_bitfield)));

  ui.ch = ui::key::k_B;
  ui.Cmd();
  ui.UpdateCanFrameBitfield();
  std::memcpy(cf_to_write.data, &ui.can_frame_bitfield, sizeof(ui.can_frame_bitfield));
  EXPECT_EQ(ui.brake, Pedal::kOneHundred);
  EXPECT_EQ(0, memcmp(&ui.can_frame_bitfield, cf_to_write.data, sizeof(ui.can_frame_bitfield)));
}

TEST_F(TestUi, SetGear) {
  ui.ch = ui::key::k_r;
  ui.Cmd();
  EXPECT_EQ(ui.gear_selection, Gear::kReverse);

  ui.ch = ui::key::k_R;
  ui.Cmd();
  EXPECT_EQ(ui.gear_selection, Gear::kReverse);

  ui.ch = ui::key::k_d;
  ui.Cmd();
  EXPECT_EQ(ui.gear_selection, Gear::kDrive);

  ui.ch = ui::key::k_D;
  ui.Cmd();
  EXPECT_EQ(ui.gear_selection, Gear::kDrive);

  ui.ch = ui::key::k_n;
  ui.Cmd();
  EXPECT_EQ(ui.gear_selection, Gear::kNeutral);

  ui.ch = ui::key::k_N;
  ui.Cmd();
  EXPECT_EQ(ui.gear_selection, Gear::kNeutral);

  ui.ch = ui::key::k_p;
  ui.Cmd();
  EXPECT_EQ(ui.gear_selection, Gear::kPark);

  ui.ch = ui::key::k_P;
  ui.Cmd();
  EXPECT_EQ(ui.gear_selection, Gear::kPark);
}

TEST_F(TestUi, SetIgnition) {
  // Store ignition initial state.
  Ignition ig_temp = ui.ignition;

  // Create CAN frame bitfield for checking can data.
  UserInputCanFrame bf{};

  // Send command to toggle ignition. Expect current state to be different from inital state.
  ui.ch = ui::key::k_s;
  ui.Cmd();
  EXPECT_NE(ui.ignition, ig_temp);

  // Send command to toggle ignition again. Expect current state to have changed back to the inital state.
  ui.ch = ui::key::k_s;
  ui.Cmd();
  EXPECT_EQ(ui.ignition, ig_temp);

  // Repeat the test with capital 'S' input command.
  ui.ch = ui::key::k_S;
  ui.Cmd();
  EXPECT_NE(ui.ignition, ig_temp);

  ui.ch = ui::key::k_S;
  ui.Cmd();
  EXPECT_EQ(ui.ignition, ig_temp);

}

TEST_F(TestUi, DISABLED_SetBlinker) {}
