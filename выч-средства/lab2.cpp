#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>

std::string convertWholeToBinary(unsigned int number) {
  std::string result = "";
  while (number > 0) {
    result = std::to_string(number % 2) + result;
    number /= 2;
  }
  return result;
}

std::string convertFloatToBinary(double number) {
  std::string result = "";
  int wholePart = 0;
  while (number != 0) {
    number *= 2;
    wholePart = std::floor(number);
    result += std::to_string(wholePart);
    number -= wholePart;
  }
  return result;
}

std::string convertToDouble(std::string numberString) {
  bool isNegative = false;
  if (numberString[0] == '-') {
    isNegative = true;
    numberString.erase(0, 1);
  }
  double number = std::stod(numberString);
  unsigned int wholePart = std::floor(number);
  double floatPart = number - wholePart;
  std::string bWholePart = convertWholeToBinary(wholePart);
  std::string bFloatPart = convertFloatToBinary(floatPart);

  int wholePartSize = bWholePart.size();
  int floatPartSize = bFloatPart.size();
  bool exponentIsNegative = false;
  int exponent = 0;
  if (wholePartSize > floatPartSize) {
    exponent = wholePartSize - floatPartSize - 1;
    exponentIsNegative = true;
  } else {
    exponent = floatPartSize - wholePartSize - 1;
  }
  std::string exponentString = "";

  exponentString =
      convertWholeToBinary(exponentIsNegative ? 1023 + exponent : exponent);
  if (exponentString.size() > 11) {
    std::cerr << "invalid number\n";
    return "";
  }
  while (exponentString.size() < 11) {
    exponentString = '0' + exponentString;
  }
  std::string mantissaString = "";
  if (wholePart > 0) {
    exponent = bWholePart.size() - 1;
    mantissaString = (bWholePart + bFloatPart).substr(1);
  } else {
    size_t firstOne = bFloatPart.find('1');
    if (firstOne == std::string::npos)
      firstOne = 0;
    exponent = -(firstOne + 1);
    mantissaString = bFloatPart.substr(firstOne + 1);
  }
  if (mantissaString.size() > 52) {
    std::cerr << "invalid number\n";
    return "";
  }
  while (mantissaString.size() < 52) {
    mantissaString += '0';
  }
  return (isNegative ? '1' : '0') + exponentString + mantissaString;
}


int main(int argc, char *argv[]) {
    std::cout << convertToDouble(argv[1]) << '\n';
}
