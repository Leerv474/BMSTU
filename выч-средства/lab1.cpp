#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>

std::string invertBits(std::string &numberString) {
  std::string inverted = numberString;
  for (char &c : inverted) {
    c = (c == '0') ? '1' : '0';
  }
  return inverted;
}

std::string convertToSignedInt(std::string numberString) {
  if (numberString == "") {
    std::cerr << "invalid input";
    return "";
  }
  bool isNegative = false;
  std::string result = "";
  if (numberString[0] == '-') {
    isNegative = true;
    numberString.erase(0, 1);
  }

  int number = std::stoi(numberString);

  while (number > 0) {
    result = std::to_string(number % 2) + result;
    number /= 2;
  }

  if (result.size() > 31) {
    std::cerr << "interger is out of bounds\n";
    return "";
  }
  while (result.size() < 31) {
    result = '0' + result;
  }
  if (isNegative) {
    for (char &c : result) {
      c = (c == '0') ? '1' : '0';
    }

    for (int i = 30; i >= 0; i--) {
      if (result[i] == '0') {
        result[i] = '1';
        break;
      } else {
        result[i] = '0';
      }
    }
    result = '1' + result;
  } else {
    result = '0' + result;
  }
  std::cout << result << '\n';
  return result;
}

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

void convertToDouble(std::string numberString) {
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
    return;
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
    return;
  }
  while (mantissaString.size() < 52) {
    mantissaString += '0';
  }
  std::cout << (isNegative ? '1' : '0') + exponentString + mantissaString
            << '\n';
}
int binaryToDecimal(const std::string &bin) {
  bool isNegative = bin[0] == '1';
  if (!isNegative) {
    return std::stoi(bin, nullptr, 2);
  }

  std::string inverted = bin;
  for (char &c : inverted) {
    c = (c == '0') ? '1' : '0';
  }
  int decimalValue = std::stoi(inverted, nullptr, 2) + 1;
  return -decimalValue;
}

std::string addBinary(const std::string& a, const std::string& b) {
    std::string result;
    int carry = 0;
    int i = a.size() - 1;
    int j = b.size() - 1;

    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if (i >= 0) sum += a[i--] - '0';
        if (j >= 0) sum += b[j--] - '0';

        result += (sum % 2) + '0';
        carry = sum / 2;
    }

    std::reverse(result.begin(), result.end());
    result.erase(0, 1);
    return result;
}

std::string subtractBinary(const std::string &a, const std::string &b) {
  std::string result = "";
  int n1 = a.size();
  int n2 = b.size();

  std::string bin1 = std::string(std::max(0, n2 - n1), '0') + a;
  std::string bin2 = std::string(std::max(0, n1 - n2), '0') + b;

  int borrow = 0;

  for (int i = bin1.size() - 1; i >= 0; i--) {
    int bit1 = bin1[i] - '0';
    int bit2 = bin2[i] - '0';

    bit1 -= borrow;
    if (bit1 < bit2) {
      bit1 += 2;
      borrow = 1;
    } else {
      borrow = 0;
    }

    int diff = bit1 - bit2;
    result = std::to_string(diff) + result;
  }

  size_t pos = result.find_first_not_of('0');
  if (pos == std::string::npos)
    return "0";
  return result.substr(pos);
}

std::string invertBits(const std::string& bin) {
    std::string inverted = bin;
    for (char& c : inverted) {
        c = (c == '0') ? '1' : '0';
    }
    return inverted;
}

std::string twosComplementToPositive(const std::string& bin) {
    std::string inverted = invertBits(bin);
    return addBinary(inverted, "1");
}

std::string multiplyBinary(std::string a, std::string b) {
    std::string result = "0";
    int n = b.size();

    bool isNegative = false;

    if (a[0] == '1') {
        a = invertBits(a);
        a = addBinary(a, "1");
        isNegative = !isNegative;
    }

    if (b[0] == '1') {
        b = invertBits(b);
        b = addBinary(b, "1");
        isNegative = !isNegative;
    }

    for (int i = n - 1; i >= 0; i--) {
        if (b[i] == '1') {
            std::string partial = a;
            partial.append(n - 1 - i, '0');
            result = addBinary(result, partial);
        }
    }

    size_t pos = result.find_first_not_of('0');
    std::string final_result = (pos != std::string::npos) ? result.substr(pos) : "0";

    while (final_result.size() < 32) {
        final_result = '0' + final_result;
    }

    if (isNegative) {
        final_result = invertBits(final_result);
        final_result = addBinary(final_result, "1");
    }

    return final_result;
}
int main(int argc, char *argv[]) {
  std::string num1 = convertToSignedInt(argv[1]);
  std::string num2 = convertToSignedInt(argv[2]);
  /*convertToDouble(argv[1]); */
  std::cout << addBinary(num1, num2) << '\n';
  std::cout << subtractBinary(num1, num2) << '\n';
}
