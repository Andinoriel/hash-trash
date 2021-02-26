#include <bitset>
#include <cmath>
#include <cstdint>
#include <exception>
#include <iomanip>
#include <iostream>
#include <random>
#include <stdexcept>
#include <stdint.h>
#include <string>
#include <vector>

static constexpr size_t ARR_LEN = 10;
static constexpr size_t HASH_BITS = 256;
static constexpr size_t BASE_SIMPLE = 251;
static constexpr size_t UP_POW = 20;

// get random uint64_t in [min, max)
uint64_t rand_in_range(uint64_t min, uint64_t max) {
  std::random_device rd;
  std::mt19937_64 gen(rd());
  std::uniform_int_distribution<uint64_t> ds(min, max);
  return ds(gen);
}

// print hihglight diff between two str
std::string highlight_diff(std::string const &lhs, std::string const &rhs) {
  std::string result;
  for (size_t i = 0; i < std::min(lhs.length(), rhs.length()); ++i) {
    result.append(lhs[i] == rhs[i] ? std::string("") + lhs[i]
                                   : std::string("\033[31m") + lhs[i] +
                                         std::string("\033[0m"));
  }
  return result;
}

// hash through exponential
uint64_t get_hash(uint64_t x) {
  uint64_t powered = 1;
  for (uint64_t i = 0; i < x; ++i) {
    powered *= BASE_SIMPLE;
  }
  return powered % HASH_BITS;
}

int main() {
  // ========================================================================

  std::vector<uint64_t> X, Y;
  for (size_t i = 0; i < ARR_LEN; ++i) {
    X.push_back(rand_in_range(0, static_cast<uint64_t>(pow(2, UP_POW))));
    // Y.push_back(X[i] ^ (uint64_t)1 << rand_in_range(1, ARR_LEN));
    Y.push_back(X[i] ^ (uint64_t)1 << (uint64_t)i);
  }
  // ========================================================================

  // vectors of nums binary representation
  std::vector<std::string> bins_X, bins_Y;

  // vectors of hashes
  std::vector<uint64_t> hash_X, hash_Y;

  for (size_t i = 0; i < ARR_LEN; ++i) {
    bins_X.push_back(std::bitset<UP_POW>(X[i]).to_string());
    bins_Y.push_back(std::bitset<UP_POW>(Y[i]).to_string());

    hash_X.push_back(get_hash(X[i]));
    hash_Y.push_back(get_hash(Y[i]));
  }

  // ========================================================================

  std::cout << "X:\n";
  for (size_t i = 0; i < ARR_LEN; ++i) {
    std::cout << std::setw(20) << X[i] << "\t\t"
              << highlight_diff(bins_X[i], bins_Y[i])
              << "\t\tH(x): " << std::setw(10) << hash_X[i] << "\n";
  }

  // ========================================================================

  std::cout << "Y:\n";
  for (size_t i = 0; i < ARR_LEN; ++i) {
    std::cout << std::setw(20) << Y[i] << "\t\t"
              << highlight_diff(bins_Y[i], bins_X[i])
              << "\t\tH(x): " << std::setw(10) << hash_Y[i] << "\t"
              << std::boolalpha << (hash_Y[i] == hash_X[i]) << "\n";
  }
  // ========================================================================

  return 0;
}