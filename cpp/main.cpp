#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <random>
#include <set>
#include <string>
#include <vector>

static constexpr size_t ARR_LEN = 10;
static constexpr size_t HASH_BITS = 63; // max 63 until overflow
static constexpr size_t BASE_SIMPLE = 99991;
static constexpr size_t UP_POW = 63; // max 63 until overflow

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

// exp uint64_t recursive
uint64_t exp_rec(uint64_t x, uint64_t n) {
  if (n == 0) {
    return 1;
  }
  if (n == 1) {
    return x;
  }
  if (!(n % 2)) {
    return exp_rec(x * x, n / 2);
  }
  return x * exp_rec(x * x, (n - 1) / 2);
}

// hash through exponential
uint64_t get_hash(uint64_t x) {
  return exp_rec(BASE_SIMPLE, x) % (exp_rec(2, HASH_BITS));
}

double get_correlatio_coeff(std::vector<uint64_t> const &lhs,
                            std::vector<uint64_t> const &rhs) {
  size_t length = std::min(lhs.size(), rhs.size());
  double avg_x = .0, avg_y = .0, avg_x2 = .0, avg_y2 = .0;

  for (size_t i = 0; i < length; ++i) {
    avg_x += lhs[i];
    avg_y += rhs[i];
    avg_x2 += lhs[i] * lhs[i];
    avg_y2 += rhs[i] * rhs[i];
  }

  avg_x /= length;
  avg_y /= length;
  avg_x2 /= length;
  avg_y2 /= length;

  double delta_x2 = avg_x2 - avg_x * avg_x;
  double delta_y2 = avg_y2 - avg_y * avg_y;
  double delta_x = std::sqrt(delta_x2);
  double delta_y = std::sqrt(delta_y2);
  double numerator = .0;

  for (size_t i = 0; i < length; ++i) {
    numerator += (lhs[i] - avg_x) * (rhs[i] - avg_y);
  }

  double denominator = length * delta_x * delta_y;

  return numerator / denominator;
}

double get_percent_of_collision(std::vector<uint64_t> vec) {
  std::set<uint64_t> set;
  for (auto &&elem : vec) {
    set.insert(elem);
  }
  return 1. - set.size() * 1. / vec.size();
}

int main() {
  // ========================================================================

  std::vector<uint64_t> X, Y;
  for (size_t i = 0; i < ARR_LEN; ++i) {
    X.push_back(rand_in_range(0, static_cast<uint64_t>(pow(2, UP_POW))));
    Y.push_back(X[i] ^ (uint64_t)1 << rand_in_range(1, UP_POW - 1));
    // Y.push_back(X[i] ^ (uint64_t)1 << (uint64_t)i);
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
              << "\t\tH(y): " << std::setw(10) << hash_Y[i]
              << "\tH(X) = H(Y): " << std::boolalpha << (hash_Y[i] == hash_X[i])
              << "\n";
  }
  // ========================================================================

  std::cout << "Correlation coefficient (X, H(X)):\t"
            << get_correlatio_coeff(X, hash_X) << "\n";
  std::cout << "Correlation coefficient (Y, H(Y)):\t"
            << get_correlatio_coeff(Y, hash_Y) << "\n";
  std::cout << "Correlation coefficient (H(X), H(Y)):\t"
            << get_correlatio_coeff(hash_X, hash_Y) << "\n";
  std::cout << "Correlation coefficient (X, Y):\t\t"
            << get_correlatio_coeff(X, Y) << "\n";

  // ========================================================================

  // std::cout << "H(X)\\:\t" << get_percent_of_collision(hash_X) << "\n";
  // std::cout << "H(Y)\\:\t" << get_percent_of_collision(hash_Y) << "\n";

  // ========================================================================

  return 0;
}