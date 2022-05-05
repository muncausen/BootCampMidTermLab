#include <gtest/gtest.h>
#include "canSender.hpp"
#include <iostream>
#include "socketcan.hpp"
#include "ui.hpp"

using namespace std;

class TestUi : public ::testing::Test
{
    public:
        TestUi() = default;
        void SetUp() override;
        void TearDown () override;
        scpp::CanFrame cf_to_write{};
        UserInput ui{};
        scpp::SocketCan socket_can{};
        int eq{};
                        
};