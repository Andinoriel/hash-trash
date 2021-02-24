#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARR_LEN 10
#define HASH_N 256
#define SIMPLE 251
#define UP_POW 20

// print size_t num in binary form
void bin(size_t n) {
  size_t i;
  for (i = 1ull << 63ull; i > 0; i = i / 2)
    (n & i) ? printf("1") : printf("0");
}

// hash through exponential
size_t get_hash(size_t x, size_t n, size_t a) {
  size_t powered = 1;
  for (size_t i = 0; i < x; ++i) {
    powered *= a;
  }
  return powered % n;
}

// randomization
size_t *get_random_x(size_t len) {
  size_t *arr = (size_t *)malloc(sizeof(size_t) * len);

  for (int i = 0; i < len; ++i) {
    arr[i] = rand() % (size_t)pow(2, UP_POW);
  }

  return arr;
}

void print_arr(size_t *arr, size_t len) {
  for (int i = 0; i < len; ++i) {
    printf("%zu ", *(arr + i));
  }
  printf("\n");
}

int main() {
  srand(time(NULL));

  // ===========================================================

  size_t *X = get_random_x(ARR_LEN);

  printf("X: ");
  print_arr(X, ARR_LEN);

  printf("X_: ");
  for (int i = 0; i < ARR_LEN; ++i) {
    printf("%zu ", get_hash(*(X + i), HASH_N, SIMPLE));
  }
  printf("\n");

  // ===========================================================

  // changing bits of nums
  size_t *Y = (size_t *)malloc(sizeof(size_t) * ARR_LEN);
  for (int i = 0; i < ARR_LEN; ++i) {
    *(Y + i) = *(X + i) ^ 1ull << (size_t)i;
  }

  printf("Y: ");
  print_arr(Y, ARR_LEN);

  printf("Y_: ");
  for (int i = 0; i < ARR_LEN; ++i) {
    printf("%zu ", get_hash(*(Y + i), HASH_N, SIMPLE));
  }
  printf("\n");

  // ===========================================================

  return 0;
}