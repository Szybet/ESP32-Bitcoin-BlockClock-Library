#ifndef BLOCK_CLOCK_TYPES_H
#define BLOCK_CLOCK_TYPES_H

#include <Arduino.h>
#include <time.h>

struct PriceData {
  String price;
  float change1h;
  float change24h;
  float change7d;
  float change30d;
  bool error;
};

struct RecommendedFees {
  uint16_t high;
  uint16_t medium;
  uint16_t low;
  uint16_t noPriority;
  bool error;
};

#endif