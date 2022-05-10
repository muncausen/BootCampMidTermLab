

#include <gtest/gtest.h>

#include <iostream>

#include "can_tranceiver.hpp"
#include "engine.hpp"
#include "server.hpp"
using namespace std;

class TestEmulator : public ::testing::Test {
 public:
  TestEmulator() = default;
  void SetUp() override;
  void TearDown() override;
  bool UpdateCanData(UserInputCanFrame& can_ui_frame) {
    UserInputCanFrame test_cfr;
    test_cfr.frame_counter = can_ui_frame.frame_counter;
    cout << "TEST:: Frame_Cntr: " << test_cfr.frame_counter << endl;
  }
  CanTranceiver* can_receiver_ = nullptr;
  Server* server_ = nullptr;
  UserInputCanFrame testcfr;
  Engine* engine = nullptr;
};