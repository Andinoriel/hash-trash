#include <bitset>
#include <cinttypes>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <vector>

static constexpr int ARR_LEN = 10;
static constexpr int HASH_BITS = 256;   // 16384
static constexpr int BASE_SIMPLE = 251; // 16381
static constexpr int UP_POW = 20;

// get random uint64_t in [min, max)
uint64_t rand_in_range(uint64_t min, uint64_t max) {
  std::random_device rd;
  std::mt19937_64 gen(rd());
  std::uniform_int_distribution<uint64_t> ds(min, max);
  return ds(gen);
}

// print hihglight diff between two str
std::string highlight_diff(std::string lhs, std::string rhs) {
  std::string result;
  for (size_t i = 0; i < std::min(lhs.length(), rhs.length()); ++i) {
    result.append(lhs[i] == rhs[i] ? std::string("") + lhs[i]
                                   : std::string("\033[31m") + lhs[i] +
                                         std::string("\033[0m"));
  }
  return result;
}

// randomization
uint64_t *get_random_x(uint64_t len) {
  uint64_t *arr = new uint64_t[len];

  for (int i = 0; i < len; ++i) {
    arr[i] = rand_in_range(0, static_cast<uint64_t>(pow(2, UP_POW)));
  }

  return arr;
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

  uint64_t *X = get_random_x(ARR_LEN);
  uint64_t *Y = new uint64_t[ARR_LEN];

  std::copy(X, X + ARR_LEN, Y);
  for (size_t i = 0; i < ARR_LEN; ++i) {
    // changing bits of nums
    // *(Y + i) = *(X + i) ^ (uint64_t)1 << rand_in_range(1, ARR_LEN);
    *(Y + i) = *(X + i) ^ (uint64_t)1 << (uint64_t)i;
  }

  // ========================================================================

  std::vector<std::string> bins_X;
  std::vector<std::string> bins_Y;

  std::vector<uint64_t> hash_X;
  std::vector<uint64_t> hash_Y;

  for (size_t i = 0; i < ARR_LEN; ++i) {
    bins_X.push_back(std::bitset<UP_POW>(*(X + i)).to_string());
    hash_X.push_back(get_hash(*(X + i)));
  }
  for (size_t i = 0; i < ARR_LEN; ++i) {
    bins_Y.push_back(std::bitset<UP_POW>(*(Y + i)).to_string());
    hash_Y.push_back(get_hash(*(Y + i)));
  }

  // ========================================================================

  std::cout << "X:\n";
  for (size_t i = 0; i < ARR_LEN; ++i) {
    std::cout << std::setw(20) << *(X + i) << "\t\t"
              << highlight_diff(bins_X.at(i), bins_Y.at(i))
              << "\t\tH(x): " << std::setw(10) << hash_X.at(i) << "\n";
  }

  // ========================================================================

  std::cout << "Y:\n";
  for (size_t i = 0; i < ARR_LEN; ++i) {
    std::cout << std::setw(20) << *(Y + i) << "\t\t"
              << highlight_diff(bins_Y.at(i), bins_X.at(i))
              << "\t\tH(x): " << std::setw(10) << hash_Y.at(i) << "\t"
              << std::boolalpha << (hash_Y.at(i) == hash_X.at(i)) << "\n";
  }
  // ========================================================================

  return 0;
}