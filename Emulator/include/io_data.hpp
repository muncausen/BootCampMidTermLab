#ifndef IO_DATA_HPP_
#define IO_DATA_HPP_

#include "candb.hpp"
#include <mutex>

static UserInputCanFrame in_data{};
static DisplayCanFrame out_data{};
static std::mutex in_data_mutex{};
static std::mutex out_data_mutex{};

#endif // IO_DATA_HPP_
