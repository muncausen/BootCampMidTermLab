#ifndef IO_DATA_HPP_
#define IO_DATA_HPP_

#include <atomic>
#include <mutex>

#include "candb.hpp"

static UserInputCanFrame in_data{};
static DisplayCanFrame out_data{};
static std::mutex in_data_mutex{};
static std::mutex out_data_mutex{};
static std::atomic<bool> tranceiver_run{true};

#endif  // IO_DATA_HPP_
