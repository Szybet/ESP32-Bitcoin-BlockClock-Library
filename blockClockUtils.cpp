#include "blockClockUtils.h"

#include <esp_system.h>

String intWithThousandSeparator(int number) {
  String numberStr = String(number);
  int length = numberStr.length();
  int pos = length % 3;

  String result = "";

  for (int i = 0; i < length; i++) {
    if (i > 0 && i % 3 == pos) {
      result += ".";
    }
    result += numberStr.charAt(i);
  }

  return result;
}

String truncateString(String input) {
  if (input.length() > 10) {
    input.remove(7);
    input.concat("...");
  }
  return input;
}

String replaceCommaWithDot(String str) {
  for (int i = 0; i < str.length(); i++) {
    if (str[i] == ',') {
      str[i] = '.';
    }
  }
  return str;
}