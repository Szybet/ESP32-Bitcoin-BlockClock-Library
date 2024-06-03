#include "blockClockClient.h"

#include <ArduinoJson.h>
#include <HTTPClient.h>
#include "blockClockUtils.h"

const String MEMPOOL_BASEURL = "https://mempool.space/api";
const String COINLIB_BASEURL = "https://coinlib.io/api/v1";

BlockClockClient::BlockClockClient(const String &apiKey) : coinlibApiKey(apiKey) {}

String BlockClockClient::getBlockHeight()
{
  http.begin(MEMPOOL_BASEURL + "/blocks/tip/height");
  int httpCode = http.GET();
  if (httpCode == HTTP_CODE_OK)
  {
    String height = http.getString();
    http.end();
    return height;
  }
  http.end();
  return String("ERR ") + String(httpCode);
}

RecommendedFees BlockClockClient::getRecommendedFees()
{
  RecommendedFees recommendedFees;

  http.begin(MEMPOOL_BASEURL + "/v1/fees/recommended");

  int httpCode = http.GET();

  if (httpCode == HTTP_CODE_OK)
  {
    StaticJsonDocument<192> httpResponseJson;
    String httpResponseBody = http.getString();

    deserializeJson(httpResponseJson, httpResponseBody);

    recommendedFees.high = httpResponseJson["fastestFee"];
    recommendedFees.medium = httpResponseJson["halfHourFee"];
    recommendedFees.low = httpResponseJson["hourFee"];
    recommendedFees.noPriority = httpResponseJson["economyFee"];
    recommendedFees.error = false;
    http.end();
    return recommendedFees;
  }

  recommendedFees.high = 0;
  recommendedFees.medium = 0;
  recommendedFees.low = 0;
  recommendedFees.noPriority = 0;
  recommendedFees.error = true;
  http.end();
  return recommendedFees;
}

PriceData BlockClockClient::getBitcoinPrice()
{
  String currency = "USD";

  DynamicJsonDocument doc(4096);

  const String url = COINLIB_BASEURL + "/coin?key=" + coinlibApiKey +
                     "&pref=" + currency + "&symbol=BTC";

  http.begin(url);

  int httpCode = http.GET();

  PriceData priceData;

  if (httpCode == HTTP_CODE_OK)
  {
    String httpResponseBody = http.getString();
    deserializeJson(doc, httpResponseBody);

    String delta1h = replaceCommaWithDot(doc["delta_1h"]);
    String delta24h = replaceCommaWithDot(doc["delta_24h"]);
    String delta7d = replaceCommaWithDot(doc["delta_7d"]);
    String delta30d = replaceCommaWithDot(doc["delta_30d"]);

    priceData.price = intWithThousandSeparator((int)doc["price"]);
    priceData.change1h = delta1h.toFloat();
    priceData.change24h = delta24h.toFloat();
    priceData.change7d = delta7d.toFloat();
    priceData.change30d = delta30d.toFloat();
    priceData.error = false;
    http.end();
    return priceData;
  }

  priceData.price = "ERR " + String(httpCode);
  priceData.change1h = (float)0;
  priceData.change24h = (float)0;
  priceData.change7d = (float)0;
  priceData.change30d = (float)0;
  priceData.error = true;
  http.end();
  return priceData;
}
