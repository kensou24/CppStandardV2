//
// Created by king on 2020/12/31.
//

#ifndef CPPSTANDARDV2TESTS_UTIL_H
#define CPPSTANDARDV2TESTS_UTIL_H
#include <chrono>
#include <ctime>
#include <string>
#include <iostream>

inline std::string asString (const std::chrono::system_clock::time_point& tp)
{
  // convert to system time:
  std::time_t t = std::chrono::system_clock::to_time_t(tp);
  std::string ts = std::ctime(&t);    // convert to calendar time
  ts.resize(ts.size()-1);             // skip trailing newline
  return ts;
}

#endif  // CPPSTANDARDV2TESTS_UTIL_H
