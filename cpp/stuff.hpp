#pragma once
#ifndef __STUFF_HPP__
#define __STUFF_HPP__

#include <cinttypes>
#include <iostream>
#include <random>
#include <string>
#include <tuple>

// get random uint64_t in [min, max)
static inline uint64_t rand_in_range(uint64_t min, uint64_t max) {
  std::random_device rd;
  std::mt19937_64 gen(rd());
  std::uniform_int_distribution<uint64_t> ds(min, max);
  return ds(gen);
}

// print uint64_t num in binary form
static inline std::string bin64(uint64_t n) {
  std::string ret;
  for (uint64_t i = (uint64_t)1 << (uint64_t)63; i > 0; i = i / 2) {
    ret += ((n & i) ? "1" : "0");
  }
  return ret;
}

// print uint32_t num in binary form
static inline std::string bin32(uint32_t n) {
  std::string ret;
  for (uint32_t i = (uint32_t)1 << (uint32_t)31; i > 0; i = i / 2) {
    ret += ((n & i) ? "1" : "0");
  }
  return ret;
}

// print uint16_t num in binary form
static inline std::string bin16(uint16_t n) {
  std::string ret;
  for (uint16_t i = (uint16_t)1 << (uint16_t)15; i > 0; i = i / 2) {
    ret += ((n & i) ? "1" : "0");
  }
  return ret;
}

// print uint8_t num in binary form
static inline std::string bin8(uint8_t n) {
  std::string ret;
  for (uint8_t i = (uint8_t)1 << (uint8_t)7; i > 0; i = i / 2) {
    ret += ((n & i) ? "1" : "0");
  }
  return ret;
}

// print uintx_t num in binary form with specified len
static inline std::string bin(uint64_t num, uint64_t len) {
  if (len > 32 && len <= 64) {
    return bin64(static_cast<uint64_t>(num));
  }
  if (len > 16 && len <= 32) {
    return bin32(static_cast<uint32_t>(num));
  }
  if (len > 8 && len <= 16) {
    return bin16(static_cast<uint16_t>(num));
  }
  if (len <= 8) {
    return bin8(static_cast<uint8_t>(num));
  }
  return std::string();
}

// print hihglight diff between two str
static inline std::string highlight_diff(const std::string &ref,
                                         const std::string &s) {
  std::string res;
  auto it_ref = ref.cbegin();
  auto it = s.cbegin();

  auto GREEN = "\033[31m";
  auto RESET = "\033[0m";

  while (it_ref != ref.cend() && it != s.cend()) {
    auto p = std::mismatch(it_ref, ref.cend(), it, s.end());
    res.insert(res.end(), it_ref, p.first);
    std::tie(it_ref, it) = p;
    p = std::mismatch(it_ref, ref.cend(), it, s.end(), std::not_equal_to<>{});
    if (p.first != it_ref) {
      res += GREEN;
      res.insert(res.end(), it_ref, p.first);
      res += RESET;
    }
    std::tie(it_ref, it) = p;
  }
  if (it != s.end()) {
    res += GREEN;
    res.insert(res.end(), it, s.end());
    res += RESET;
  }
  return res;
}

#endif // !__STUFF_HPP__
