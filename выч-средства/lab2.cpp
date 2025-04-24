#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdint>
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

std::string convertToDouble(const std::string &numberString) {
  double number = std::stod(numberString);
  if (number == 0.0)
    return std::string(64, '0'); // Handle zero case

  bool sign = number < 0;
  if (sign)
    number = -number;

  int exp;
  double mant = std::frexp(
      number, &exp); // mant is in range [0.5, 1.0) for normalized values

  int biasedExp = exp + 1023; // Add the IEEE 754 bias to the exponent
  uint64_t mantBits = 0;

  if (exp == 0) {
      mant -= 0.5;
  }

  // Convert mantissa (fractional part) to 52 bits
  for (int i = 0; i < 52; ++i) {
    mant *= 2;
    if (mant >= 1.0) {
      mantBits |=
          (1ULL << (51 - i)); // Set the bit at the corresponding position
      mant -= 1.0;            // Remove the integer part
    }
  }

  // Combine the components into the 64-bit IEEE 754 double representation
  uint64_t ieee =
      ((uint64_t)sign << 63) | ((uint64_t)(biasedExp - 1) << 52) | mantBits;
  return std::bitset<64>(ieee)
      .to_string(); // Return the 64-bit IEEE representation as a string
}

struct BinaryFloat {
  bool sign;
  int exponent;
  std::string mantissa;

  BinaryFloat() {}

  BinaryFloat(std::string binary) {
    sign = binary[0] == '1';
    exponent = std::stoi(binary.substr(1, 11), nullptr, 2) - 1023;
    mantissa = '1' + binary.substr(12, 52); // implicit 1
  }

  std::string toBinary() const {
    int biasedExp = exponent + 1023;
    std::string expBits = std::bitset<11>(biasedExp).to_string();
    std::string manBits = mantissa.substr(1); // Skip the implicit leading 1
    while (manBits.size() < 52) {
      manBits += '0'; // Pad with zeros if necessary
    }
    return (sign ? '1' : '0') + expBits + manBits;
  }
};

BinaryFloat add(const BinaryFloat &a, const BinaryFloat &b) {
  BinaryFloat A = a, B = b;
  if (A.exponent < B.exponent)
    std::swap(A, B);

  int shift = A.exponent - B.exponent;
  std::string bMant = std::string(shift, '0') + B.mantissa;
  std::string aMant = A.mantissa + std::string(shift, '0');

  int carry = 0;
  std::string result;
  for (int i = aMant.size() - 1; i >= 0; --i) {
    int sum =
        (aMant[i] - '0') + (i < bMant.size() ? (bMant[i] - '0') : 0) + carry;
    result = std::to_string(sum % 2) + result;
    carry = sum / 2;
  }
  if (carry) {
    result = '1' + result;
    A.exponent += 1;
  }

  size_t firstOne = result.find('1');
  A.mantissa = result.substr(firstOne, 53);
  A.exponent -= firstOne;

  return A;
}

BinaryFloat multiply(const BinaryFloat &a, const BinaryFloat &b) {
  std::string result(106, '0');
  for (int i = 0; i < 53; ++i) {
    if (b.mantissa[i] == '1') {
      for (int j = 0; j < 53; ++j) {
        if (a.mantissa[j] == '1') {
          int pos = i + j;
          result[pos] += 1;
        }
      }
    }
  }

  for (int i = 105; i > 0; --i) {
    if (result[i] > '1') {
      result[i - 1] += (result[i] - '0') / 2;
      result[i] = ((result[i] - '0') % 2) + '0';
    }
  }

  size_t firstOne = result.find('1');
  BinaryFloat res;
  res.sign = a.sign ^ b.sign;
  res.exponent = a.exponent + b.exponent - firstOne;
  res.mantissa = result.substr(firstOne, 53);
  return res;
}

int main(int argc, char *argv[]) {
  std::string num1 = convertToDouble(argv[1]);
  std::string num2 = convertToDouble(argv[2]);

  std::cout << "num1: " << num1 << '\n';
  std::cout << "num2: " << num2 << '\n';

  std::cout << "sum: " << add(num1, num2).toBinary() << '\n';
  std::cout << "mult: " << multiply(num1, num2).toBinary() << '\n';
}
