#ifndef BLOCK_CLOCK_CLIENT_H
#define BLOCK_CLOCK_CLIENT_H

#include <HTTPClient.h>

#include "blockClockTypes.h"

class BlockClockClient {
 public:
  explicit BlockClockClient(const String& apiKey);

  String getBlockHeight();
  RecommendedFees getRecommendedFees();
  PriceData getBitcoinPrice();

 private:
  String coinlibApiKey;
  HTTPClient http;
};

#endif