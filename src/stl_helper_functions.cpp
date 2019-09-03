#include "stl_helper_functions.hpp"

using namespace std;

namespace stl::helper {

int stoi(const u16string& str,
         size_t* pos,
         int base,
         bool ignore_leading_white_space_characters) {
  int number_value{};

  auto temp_str{str};

  if (ignore_leading_white_space_characters)
    temp_str = ltrim(str);

  auto found_invalid_character{false};

  if ((base == 2) && ((temp_str[0] == u'b') || (temp_str[0] == u'B'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 2) && ((temp_str.substr(0, 2) == u"0b") ||
                           (temp_str.substr(0, 2) == u"0B"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 8) && ((temp_str[0] == u'0') || (temp_str[0] == u'o') ||
                           (temp_str[0] == u'O'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 8) && ((temp_str.substr(0, 2) == u"0o") ||
                           (temp_str.substr(0, 2) == u"0O"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 16) && ((temp_str[0] == u'x') || (temp_str[0] == u'X'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 16) && ((temp_str.substr(0, 2) == u"0x") ||
                            (temp_str.substr(0, 2) == u"0X"))) {
    temp_str.assign(temp_str.substr(2));
  }

  u16string::size_type i{0u};

  for (; (!found_invalid_character && (i < temp_str.size())); i++) {
    switch (base) {
      case 2:
        if ((temp_str[i] < u'0') || (temp_str[i] > u'1'))
          found_invalid_character = true;

        number_value *= 2;

        number_value += static_cast<int>(temp_str[i] - u'0');

        break;

      case 8:
        if ((temp_str[i] < u'0') || (temp_str[i] > u'7'))
          found_invalid_character = true;

        number_value *= 8;

        number_value += static_cast<int>(temp_str[i] - u'0');

        break;

      case 10:
        if ((temp_str[i] < u'0') || (temp_str[i] > u'9'))
          found_invalid_character = true;

        number_value *= 10;

        number_value += static_cast<int>(temp_str[i] - u'0');

        break;

      case 16:
        if (((temp_str[i] >= u'0') && (temp_str[i] <= u'9')) ||
            ((temp_str[i] >= u'A') && (temp_str[i] <= u'F'))

            || ((temp_str[i] >= u'a') && (temp_str[i] <= u'f'))) {
          number_value *= 16;

          if ((temp_str[i] >= u'0') && (temp_str[i] <= u'9'))
            number_value += static_cast<int>(temp_str[i] - u'0');

          else if ((temp_str[i] >= u'A') && (temp_str[i] <= u'F'))
            number_value += static_cast<int>(10 + (temp_str[i] - u'A'));

          else if ((temp_str[i] >= u'a') && (temp_str[i] <= u'f'))
            number_value += static_cast<int>(10 + (temp_str[i] - u'a'));
        } else {
          found_invalid_character = true;
        }

        break;

      default:
        if ((temp_str[i] < u'0') || (temp_str[i] > u'9'))
          found_invalid_character = true;

        number_value *= 10;

        number_value += static_cast<int>(temp_str[i] - u'0');

        break;
    }
  }

  if (pos)
    *pos = i;

  return number_value;
}

long stol(const u16string& str,
          size_t* pos,
          int base,
          bool ignore_leading_white_space_characters) {
  long number_value{};

  auto temp_str{str};

  if (ignore_leading_white_space_characters)
    temp_str = ltrim(str);

  auto found_invalid_character{false};

  if ((base == 2) && ((temp_str[0] == u'b') || (temp_str[0] == u'B'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 2) && ((temp_str.substr(0, 2) == u"0b") ||
                           (temp_str.substr(0, 2) == u"0B"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 8) && ((temp_str[0] == u'0') || (temp_str[0] == u'o') ||
                           (temp_str[0] == u'O'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 8) && ((temp_str.substr(0, 2) == u"0o") ||
                           (temp_str.substr(0, 2) == u"0O"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 16) && ((temp_str[0] == u'x') || (temp_str[0] == u'X'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 16) && ((temp_str.substr(0, 2) == u"0x") ||
                            (temp_str.substr(0, 2) == u"0X"))) {
    temp_str.assign(temp_str.substr(2));
  }

  u16string::size_type i{0u};

  for (; (!found_invalid_character && (i < temp_str.size())); i++) {
    switch (base) {
      case 2:
        if ((temp_str[i] < u'0') || (temp_str[i] > u'1'))
          found_invalid_character = true;

        number_value *= 2;

        number_value += static_cast<long>(temp_str[i] - u'0');

        break;

      case 8:
        if ((temp_str[i] < u'0') || (temp_str[i] > u'7'))
          found_invalid_character = true;

        number_value *= 8;

        number_value += static_cast<long>(temp_str[i] - u'0');

        break;

      case 10:
        if ((temp_str[i] < u'0') || (temp_str[i] > u'9'))
          found_invalid_character = true;

        number_value *= 10;

        number_value += static_cast<long>(temp_str[i] - u'0');

        break;

      case 16:
        if (((temp_str[i] >= u'0') && (temp_str[i] <= u'9')) ||
            ((temp_str[i] >= u'A') && (temp_str[i] <= u'F'))

            || ((temp_str[i] >= u'a') && (temp_str[i] <= u'f'))) {
          number_value *= 16;

          if ((temp_str[i] >= u'0') && (temp_str[i] <= u'9'))
            number_value += static_cast<long>(temp_str[i] - u'0');

          else if ((temp_str[i] >= u'A') && (temp_str[i] <= u'F'))
            number_value += static_cast<long>(10 + (temp_str[i] - u'A'));

          else if ((temp_str[i] >= u'a') && (temp_str[i] <= u'f'))
            number_value += static_cast<long>(10 + (temp_str[i] - u'a'));
        } else {
          found_invalid_character = true;
        }

        break;

      default:
        if ((temp_str[i] < u'0') || (temp_str[i] > u'9'))
          found_invalid_character = true;

        number_value *= 10;

        number_value += static_cast<long>(temp_str[i] - u'0');

        break;
    }
  }

  if (pos)
    *pos = i;

  return number_value;
}

unsigned long stoul(const u16string& str,
                    size_t* pos,
                    int base,
                    bool ignore_leading_white_space_characters) {
  unsigned long number_value{};

  auto temp_str{str};

  if (ignore_leading_white_space_characters)
    temp_str = ltrim(str);

  auto found_invalid_character{false};

  if ((base == 2) && ((temp_str[0] == u'b') || (temp_str[0] == u'B'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 2) && ((temp_str.substr(0, 2) == u"0b") ||
                           (temp_str.substr(0, 2) == u"0B"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 8) && ((temp_str[0] == u'0') || (temp_str[0] == u'o') ||
                           (temp_str[0] == u'O'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 8) && ((temp_str.substr(0, 2) == u"0o") ||
                           (temp_str.substr(0, 2) == u"0O"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 16) && ((temp_str[0] == u'x') || (temp_str[0] == u'X'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 16) && ((temp_str.substr(0, 2) == u"0x") ||
                            (temp_str.substr(0, 2) == u"0X"))) {
    temp_str.assign(temp_str.substr(2));
  }

  u16string::size_type i{0u};

  for (; (!found_invalid_character && (i < temp_str.size())); i++) {
    switch (base) {
      case 2:
        if ((temp_str[i] < u'0') || (temp_str[i] > u'1'))
          found_invalid_character = true;

        number_value *= 2;

        number_value += static_cast<unsigned long>(temp_str[i] - u'0');

        break;

      case 8:
        if ((temp_str[i] < u'0') || (temp_str[i] > u'7'))
          found_invalid_character = true;

        number_value *= 8;

        number_value += static_cast<unsigned long>(temp_str[i] - u'0');

        break;

      case 10:
        if ((temp_str[i] < u'0') || (temp_str[i] > u'9'))
          found_invalid_character = true;

        number_value *= 10;

        number_value += static_cast<unsigned long>(temp_str[i] - u'0');

        break;

      case 16:
        if (((temp_str[i] >= u'0') && (temp_str[i] <= u'9')) ||
            ((temp_str[i] >= u'A') && (temp_str[i] <= u'F'))

            || ((temp_str[i] >= u'a') && (temp_str[i] <= u'f'))) {
          number_value *= 16;

          if ((temp_str[i] >= u'0') && (temp_str[i] <= u'9'))
            number_value += static_cast<unsigned long>(temp_str[i] - u'0');

          else if ((temp_str[i] >= u'A') && (temp_str[i] <= u'F'))
            number_value +=
                static_cast<unsigned long>(10 + (temp_str[i] - u'A'));

          else if ((temp_str[i] >= u'a') && (temp_str[i] <= u'f'))
            number_value +=
                static_cast<unsigned long>(10 + (temp_str[i] - u'a'));
        } else {
          found_invalid_character = true;
        }

        break;

      default:
        if ((temp_str[i] < u'0') || (temp_str[i] > u'9'))
          found_invalid_character = true;

        number_value *= 10;

        number_value += static_cast<unsigned long>(temp_str[i] - u'0');

        break;
    }
  }

  if (pos)
    *pos = i;

  return number_value;
}

long long stoll(const u16string& str,
                size_t* pos,
                int base,
                bool ignore_leading_white_space_characters) {
  long long number_value{};

  auto temp_str{str};

  if (ignore_leading_white_space_characters)
    temp_str = ltrim(str);

  auto found_invalid_character{false};

  if ((base == 2) && ((temp_str[0] == u'b') || (temp_str[0] == u'B'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 2) && ((temp_str.substr(0, 2) == u"0b") ||
                           (temp_str.substr(0, 2) == u"0B"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 8) && ((temp_str[0] == u'0') || (temp_str[0] == u'o') ||
                           (temp_str[0] == u'O'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 8) && ((temp_str.substr(0, 2) == u"0o") ||
                           (temp_str.substr(0, 2) == u"0O"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 16) && ((temp_str[0] == u'x') || (temp_str[0] == u'X'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 16) && ((temp_str.substr(0, 2) == u"0x") ||
                            (temp_str.substr(0, 2) == u"0X"))) {
    temp_str.assign(temp_str.substr(2));
  }

  u16string::size_type i{0u};

  for (; (!found_invalid_character && (i < temp_str.size())); i++) {
    switch (base) {
      case 2:
        if ((temp_str[i] < u'0') || (temp_str[i] > u'1'))
          found_invalid_character = true;

        number_value *= 2;

        number_value += static_cast<long long>(temp_str[i] - u'0');

        break;

      case 8:
        if ((temp_str[i] < u'0') || (temp_str[i] > u'7'))
          found_invalid_character = true;

        number_value *= 8;

        number_value += static_cast<long long>(temp_str[i] - u'0');

        break;

      case 10:
        if ((temp_str[i] < u'0') || (temp_str[i] > u'9'))
          found_invalid_character = true;

        number_value *= 10;

        number_value += static_cast<long long>(temp_str[i] - u'0');

        break;

      case 16:
        if (((temp_str[i] >= u'0') && (temp_str[i] <= u'9')) ||
            ((temp_str[i] >= u'A') && (temp_str[i] <= u'F'))

            || ((temp_str[i] >= u'a') && (temp_str[i] <= u'f'))) {
          number_value *= 16;

          if ((temp_str[i] >= u'0') && (temp_str[i] <= u'9'))
            number_value += static_cast<long long>(temp_str[i] - u'0');

          else if ((temp_str[i] >= u'A') && (temp_str[i] <= u'F'))
            number_value += static_cast<long long>(10 + (temp_str[i] - u'A'));

          else if ((temp_str[i] >= u'a') && (temp_str[i] <= u'f'))
            number_value += static_cast<long long>(10 + (temp_str[i] - u'a'));
        } else {
          found_invalid_character = true;
        }

        break;

      default:
        if ((temp_str[i] < u'0') || (temp_str[i] > u'9'))
          found_invalid_character = true;

        number_value *= 10;

        number_value += static_cast<long long>(temp_str[i] - u'0');

        break;
    }
  }

  if (pos)
    *pos = i;

  return number_value;
}

unsigned long long stoull(const u16string& str,
                          size_t* pos,
                          int base,
                          bool ignore_leading_white_space_characters) {
  unsigned long long number_value{};

  auto temp_str{str};

  if (ignore_leading_white_space_characters)
    temp_str = ltrim(str);

  auto found_invalid_character{false};

  if ((base == 2) && ((temp_str[0] == u'b') || (temp_str[0] == u'B'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 2) && ((temp_str.substr(0, 2) == u"0b") ||
                           (temp_str.substr(0, 2) == u"0B"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 8) && ((temp_str[0] == u'0') || (temp_str[0] == u'o') ||
                           (temp_str[0] == u'O'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 8) && ((temp_str.substr(0, 2) == u"0o") ||
                           (temp_str.substr(0, 2) == u"0O"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 16) && ((temp_str[0] == u'x') || (temp_str[0] == u'X'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 16) && ((temp_str.substr(0, 2) == u"0x") ||
                            (temp_str.substr(0, 2) == u"0X"))) {
    temp_str.assign(temp_str.substr(2));
  }

  u16string::size_type i{0u};

  for (; (!found_invalid_character && (i < temp_str.size())); i++) {
    switch (base) {
      case 2:
        if ((temp_str[i] < u'0') || (temp_str[i] > u'1'))
          found_invalid_character = true;

        number_value *= 2;

        number_value += static_cast<unsigned long long>(temp_str[i] - u'0');

        break;

      case 8:
        if ((temp_str[i] < u'0') || (temp_str[i] > u'7'))
          found_invalid_character = true;

        number_value *= 8;

        number_value += static_cast<unsigned long long>(temp_str[i] - u'0');

        break;

      case 10:
        if ((temp_str[i] < u'0') || (temp_str[i] > u'9'))
          found_invalid_character = true;

        number_value *= 10;

        number_value += static_cast<unsigned long long>(temp_str[i] - u'0');

        break;

      case 16:
        if (((temp_str[i] >= u'0') && (temp_str[i] <= u'9')) ||
            ((temp_str[i] >= u'A') && (temp_str[i] <= u'F'))

            || ((temp_str[i] >= u'a') && (temp_str[i] <= u'f'))) {
          number_value *= 16;

          if ((temp_str[i] >= u'0') && (temp_str[i] <= u'9'))
            number_value += static_cast<unsigned long long>(temp_str[i] - u'0');

          else if ((temp_str[i] >= u'A') && (temp_str[i] <= u'F'))
            number_value +=
                static_cast<unsigned long long>(10 + (temp_str[i] - u'A'));

          else if ((temp_str[i] >= u'a') && (temp_str[i] <= u'f'))
            number_value +=
                static_cast<unsigned long long>(10 + (temp_str[i] - u'a'));
        } else {
          found_invalid_character = true;
        }

        break;

      default:
        if ((temp_str[i] < u'0') || (temp_str[i] > u'9'))
          found_invalid_character = true;

        number_value *= 10;

        number_value += static_cast<unsigned long long>(temp_str[i] - u'0');

        break;
    }
  }

  if (pos)
    *pos = i;

  return number_value;
}

float stof(const u16string& str,
           size_t* pos,
           int base,
           bool ignore_leading_white_space_characters) {
  float number_value{};

  auto negative_sign_found{false};
  float fractional_part_value{};
  auto fractional_part_found{false};
  int fractional_part_position_index{-1};

  auto exponential_sign_found{false};
  auto negative_exponent_sign_found{false};
  auto exponent_leading_zero_values{true};
  int exponential_part_value{};

  auto found_invalid_character{false};

  auto temp_str{str};

  if (ignore_leading_white_space_characters)
    temp_str = ltrim(str);

  if (temp_str[0] == u'+') {
    temp_str.erase(cbegin(temp_str));
  }

  else if (temp_str[0] == u'-') {
    negative_sign_found = true;
    temp_str.erase(cbegin(temp_str));
  }

  if ((base == 2) &&
      ((temp_str.substr(0, 2) == u"0b") || (temp_str.substr(0, 2) == u"0B"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 2) && ((temp_str[0] == u'b') || (temp_str[0] == u'B'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 8) && ((temp_str.substr(0, 2) == u"0o") ||
                           (temp_str.substr(0, 2) == u"0O"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 8) && ((temp_str[0] == u'0') || (temp_str[0] == u'o') ||
                           (temp_str[0] == u'O'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 16) && ((temp_str.substr(0, 2) == u"0x") ||
                            (temp_str.substr(0, 2) == u"0X"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 16) && ((temp_str[0] == u'x') || (temp_str[0] == u'X'))) {
    temp_str.erase(cbegin(temp_str));
  }

  if (temp_str[0] == u'+') {
    temp_str.erase(cbegin(temp_str));
  }

  else if (temp_str[0] == u'-') {
    negative_sign_found = true;
    temp_str.erase(cbegin(temp_str));
  }

  if (temp_str[0] == u'.') {
    fractional_part_found = true;
    temp_str.erase(cbegin(temp_str));
  }

  if (pos)
    *pos = 0;

  if (!fractional_part_found && (temp_str[0] == u'0'))
    return number_value;

  if ((base != 16) && ((temp_str[0] == u'e') || (temp_str[0] == u'E'))) {
    if (fractional_part_found)
      return number_value;
    exponential_sign_found = true;
    temp_str.erase(cbegin(temp_str));
  }

  u16string::size_type i{0u};

  for (; (!found_invalid_character && (i < temp_str.size())); i++) {
    switch (base) {
      case 2:

        if (temp_str[i] == u'.') {
          if (!fractional_part_found) {
            fractional_part_found = true;
            fractional_part_value = 0.f;
            fractional_part_position_index = -1;
          } else {
            found_invalid_character = true;
          }
        }

        else if (!exponential_sign_found &&
                 ((temp_str[i] == u'e') || (temp_str[i] == u'E'))) {
          exponential_sign_found = true;
        }

        else if (exponential_sign_found && (temp_str[i] == u'+')) {
          if ((temp_str[i - 1] != u'e') && (temp_str[i - 1] != u'E'))
            found_invalid_character = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && (temp_str[i] == u'-')) {
          if ((temp_str[i - 1] != u'e') && (temp_str[i - 1] != u'E'))
            found_invalid_character = true;

          else
            negative_exponent_sign_found = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && exponent_leading_zero_values &&
                 (temp_str[i] == u'0')) {
          exponential_part_value = 0;
        }

        else if ((temp_str[i] < u'0') || (temp_str[i] > u'1')) {
          found_invalid_character = true;
        }

        else {
          if (exponential_sign_found) {
            exponent_leading_zero_values = false;
            exponential_part_value *= 2;
            exponential_part_value += static_cast<int>(temp_str[i] - u'0');
          } else if (fractional_part_found) {
            fractional_part_value += static_cast<float>(
                static_cast<int>(temp_str[i] - u'0') *
                std::pow(2.f, fractional_part_position_index));
            fractional_part_position_index--;
          } else {
            number_value *= 2;
            number_value += static_cast<float>(temp_str[i] - u'0');
          }
        }

        if (found_invalid_character) {
          number_value += fractional_part_value;

          if (negative_sign_found)
            number_value = -number_value;

          if (exponential_sign_found) {
            if (negative_exponent_sign_found)
              exponential_part_value = -exponential_part_value;

            if (abs(exponential_part_value) != 0)
              number_value *= powf(2.f, exponential_part_value);
          }
        }

        break;

      case 8:

        if (temp_str[i] == u'.') {
          if (!fractional_part_found) {
            fractional_part_found = true;
            fractional_part_value = 0.f;
            fractional_part_position_index = -1;
          } else {
            found_invalid_character = true;
          }
        }

        else if (!exponential_sign_found &&
                 ((temp_str[i] == u'e') || (temp_str[i] == u'E'))) {
          exponential_sign_found = true;
        }

        else if (exponential_sign_found && (temp_str[i] == u'+')) {
          if ((temp_str[i - 1] != u'e') && (temp_str[i - 1] != u'E'))
            found_invalid_character = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && (temp_str[i] == u'-')) {
          if ((temp_str[i - 1] != u'e') && (temp_str[i - 1] != u'E'))
            found_invalid_character = true;

          else
            negative_exponent_sign_found = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && exponent_leading_zero_values &&
                 (temp_str[i] == u'0')) {
          exponential_part_value = 0;
        }

        else if ((temp_str[i] < u'0') || (temp_str[i] > u'7')) {
          found_invalid_character = true;
        }

        else {
          if (exponential_sign_found) {
            exponent_leading_zero_values = false;
            exponential_part_value *= 2;
            exponential_part_value += static_cast<int>(temp_str[i] - u'0');
          } else if (fractional_part_found) {
            fractional_part_value += static_cast<float>(
                static_cast<int>(temp_str[i] - u'0') *
                std::pow(8.f, fractional_part_position_index));
            fractional_part_position_index--;
          } else {
            number_value *= 8;
            number_value += static_cast<float>(temp_str[i] - u'0');
          }
        }

        if (found_invalid_character) {
          number_value += fractional_part_value;

          if (negative_sign_found)
            number_value = -number_value;

          if (exponential_sign_found) {
            if (negative_exponent_sign_found)
              exponential_part_value = -exponential_part_value;

            if (abs(exponential_part_value) != 0)
              number_value *= powf(8.f, exponential_part_value);
          }
        }

        break;

      case 10:
        if (temp_str[i] == u'.') {
          if (!fractional_part_found) {
            fractional_part_found = true;
            fractional_part_value = 0.f;
            fractional_part_position_index = -1;
          } else {
            found_invalid_character = true;
          }
        }

        else if (!exponential_sign_found &&
                 ((temp_str[i] == u'e') || (temp_str[i] == u'E'))) {
          exponential_sign_found = true;
        }

        else if (exponential_sign_found && (temp_str[i] == u'+')) {
          if ((temp_str[i - 1] != u'e') && (temp_str[i - 1] != u'E'))
            found_invalid_character = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && (temp_str[i] == u'-')) {
          if ((temp_str[i - 1] != u'e') && (temp_str[i - 1] != u'E'))
            found_invalid_character = true;

          else
            negative_exponent_sign_found = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && exponent_leading_zero_values &&
                 (temp_str[i] == u'0')) {
          exponential_part_value = 0;
        }

        else if ((temp_str[i] < u'0') || (temp_str[i] > u'9')) {
          found_invalid_character = true;
        }

        else {
          if (exponential_sign_found) {
            exponent_leading_zero_values = false;
            exponential_part_value *= 10;
            exponential_part_value += static_cast<int>(temp_str[i] - u'0');
          } else if (fractional_part_found) {
            fractional_part_value += static_cast<float>(
                static_cast<int>(temp_str[i] - u'0') *
                std::pow(10.f, fractional_part_position_index));
            fractional_part_position_index--;
          } else {
            number_value *= 10;
            number_value += static_cast<float>(temp_str[i] - u'0');
          }
        }

        if (found_invalid_character) {
          number_value += fractional_part_value;

          if (negative_sign_found)
            number_value = -number_value;

          if (exponential_sign_found) {
            if (negative_exponent_sign_found)
              exponential_part_value = -exponential_part_value;

            if (abs(exponential_part_value) != 0)
              number_value *= powf(10.f, exponential_part_value);
          }
        }

        break;

      case 16:
        if (temp_str[i] == u'.') {
          if (!fractional_part_found) {
            fractional_part_found = true;
            fractional_part_value = 0.f;
            fractional_part_position_index = -1;
          } else {
            found_invalid_character = true;
          }
        } else {
          if (fractional_part_found) {
            if (((temp_str[i] >= u'0') && (temp_str[i] <= u'9')) ||
                ((temp_str[i] >= u'A') && (temp_str[i] <= u'F'))

                || ((temp_str[i] >= u'a') && (temp_str[i] <= u'f'))) {
              number_value *= 16;

              if ((temp_str[i] >= u'0') && (temp_str[i] <= u'9')) {
                fractional_part_value += static_cast<float>(
                    static_cast<int>(temp_str[i] - u'0') *
                    std::pow(16.f, fractional_part_position_index));
              }

              else if ((temp_str[i] >= u'A') && (temp_str[i] <= u'F')) {
                fractional_part_value += static_cast<float>(
                    static_cast<int>(temp_str[i] - u'A') *
                    std::pow(16.f, fractional_part_position_index));
              }

              else if ((temp_str[i] >= u'a') && (temp_str[i] <= u'f')) {
                fractional_part_value += static_cast<float>(
                    static_cast<int>(temp_str[i] - u'a') *
                    std::pow(16.f, fractional_part_position_index));
              }

              fractional_part_position_index--;
            } else {
              found_invalid_character = true;
            }
          } else {
            if (((temp_str[i] >= u'0') && (temp_str[i] <= u'9')) ||
                ((temp_str[i] >= u'A') && (temp_str[i] <= u'F'))

                || ((temp_str[i] >= u'a') && (temp_str[i] <= u'f'))) {
              number_value *= 16;

              if ((temp_str[i] >= u'0') && (temp_str[i] <= u'9'))
                number_value += static_cast<float>(temp_str[i] - u'0');

              else if ((temp_str[i] >= u'A') && (temp_str[i] <= u'F'))
                number_value += static_cast<float>(10 + (temp_str[i] - u'A'));

              else if ((temp_str[i] >= u'a') && (temp_str[i] <= u'f'))
                number_value += static_cast<float>(10 + (temp_str[i] - u'a'));
            } else {
              found_invalid_character = true;
            }
          }
        }

        if (found_invalid_character) {
          number_value += fractional_part_value;

          if (negative_sign_found)
            number_value = -number_value;
        }

        break;

      default:
        if (temp_str[i] == u'.') {
          if (!fractional_part_found) {
            fractional_part_found = true;
            fractional_part_value = 0.f;
            fractional_part_position_index = -1;
          } else {
            found_invalid_character = true;
          }
        }

        else if (!exponential_sign_found &&
                 ((temp_str[i] == u'e') || (temp_str[i] == u'E'))) {
          exponential_sign_found = true;
        }

        else if (exponential_sign_found && (temp_str[i] == u'+')) {
          if ((temp_str[i - 1] != u'e') && (temp_str[i - 1] != u'E'))
            found_invalid_character = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && (temp_str[i] == u'-')) {
          if ((temp_str[i - 1] != u'e') && (temp_str[i - 1] != u'E'))
            found_invalid_character = true;

          else
            negative_exponent_sign_found = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && exponent_leading_zero_values &&
                 (temp_str[i] == u'0')) {
          exponential_part_value = 0;
        }

        else if ((temp_str[i] < u'0') || (temp_str[i] > u'9')) {
          found_invalid_character = true;
        }

        else {
          if (exponential_sign_found) {
            exponent_leading_zero_values = false;
            exponential_part_value *= 10;
            exponential_part_value += static_cast<int>(temp_str[i] - u'0');
          } else if (fractional_part_found) {
            fractional_part_value += static_cast<float>(
                static_cast<int>(temp_str[i] - u'0') *
                std::pow(10.f, fractional_part_position_index));
            fractional_part_position_index--;
          } else {
            number_value *= 10;
            number_value += static_cast<float>(temp_str[i] - u'0');
          }
        }

        if (found_invalid_character) {
          number_value += fractional_part_value;

          if (negative_sign_found)
            number_value = -number_value;

          if (exponential_sign_found) {
            if (negative_exponent_sign_found)
              exponential_part_value = -exponential_part_value;

            if (abs(exponential_part_value) != 0)
              number_value *= powf(10.f, exponential_part_value);
          }
        }

        break;
    }
  }

  if (!found_invalid_character) {
    number_value += fractional_part_value;

    if (negative_sign_found)
      number_value = -number_value;

    if (exponential_sign_found && (base != 16)) {
      if (negative_exponent_sign_found)
        exponential_part_value = -exponential_part_value;

      if (abs(exponential_part_value) != 0)
        number_value *= powf(2.f, exponential_part_value);
    }
  }

  if (pos)
    *pos = i;

  return number_value;
}

double stod(const u16string& str,
            size_t* pos,
            int base,
            bool ignore_leading_white_space_characters) {
  double number_value{};

  auto negative_sign_found{false};
  double fractional_part_value{};
  auto fractional_part_found{false};
  int fractional_part_position_index{-1};

  auto exponential_sign_found{false};
  auto negative_exponent_sign_found{false};
  auto exponent_leading_zero_values{true};
  int exponential_part_value{};

  auto found_invalid_character{false};

  auto temp_str{str};

  if (ignore_leading_white_space_characters)
    temp_str = ltrim(str);

  if ((base == 2) &&
      ((temp_str.substr(0, 2) == u"0b") || (temp_str.substr(0, 2) == u"0B"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 2) && ((temp_str[0] == u'b') || (temp_str[0] == u'B'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 8) && ((temp_str.substr(0, 2) == u"0o") ||
                           (temp_str.substr(0, 2) == u"0O"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 8) && ((temp_str[0] == u'0') || (temp_str[0] == u'o') ||
                           (temp_str[0] == u'O'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 16) && ((temp_str.substr(0, 2) == u"0x") ||
                            (temp_str.substr(0, 2) == u"0X"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 16) && ((temp_str[0] == u'x') || (temp_str[0] == u'X'))) {
    temp_str.erase(cbegin(temp_str));
  }

  if (temp_str[0] == u'+') {
    temp_str.erase(cbegin(temp_str));
  }

  else if (temp_str[0] == u'-') {
    negative_sign_found = true;
    temp_str.erase(cbegin(temp_str));
  }

  if (temp_str[0] == u'.') {
    fractional_part_found = true;
    temp_str.erase(cbegin(temp_str));
  }

  if (pos)
    *pos = 0;

  if (!fractional_part_found && (temp_str[0] == u'0'))
    return number_value;

  if ((base != 16) && ((temp_str[0] == u'e') || (temp_str[0] == u'E'))) {
    if (fractional_part_found)
      return number_value;
    exponential_sign_found = true;
    temp_str.erase(cbegin(temp_str));
  }

  u16string::size_type i{0u};

  for (; (!found_invalid_character && (i < temp_str.size())); i++) {
    switch (base) {
      case 2:

        if (temp_str[i] == u'.') {
          if (!fractional_part_found) {
            fractional_part_found = true;
            fractional_part_value = 0;
            fractional_part_position_index = -1;
          } else {
            found_invalid_character = true;
          }
        }

        else if (!exponential_sign_found &&
                 ((temp_str[i] == u'e') || (temp_str[i] == u'E'))) {
          exponential_sign_found = true;
        }

        else if (exponential_sign_found && (temp_str[i] == u'+')) {
          if ((temp_str[i - 1] != u'e') && (temp_str[i - 1] != u'E'))
            found_invalid_character = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && (temp_str[i] == u'-')) {
          if ((temp_str[i - 1] != u'e') && (temp_str[i - 1] != u'E'))
            found_invalid_character = true;

          else
            negative_exponent_sign_found = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && exponent_leading_zero_values &&
                 (temp_str[i] == u'0')) {
          exponential_part_value = 0;
        }

        else if ((temp_str[i] < u'0') || (temp_str[i] > u'1')) {
          found_invalid_character = true;
        }

        else {
          if (exponential_sign_found) {
            exponent_leading_zero_values = false;
            exponential_part_value *= 2;
            exponential_part_value += static_cast<int>(temp_str[i] - u'0');
          } else if (fractional_part_found) {
            fractional_part_value +=
                static_cast<double>(static_cast<int>(temp_str[i] - u'0') *
                                    pow(2.f, fractional_part_position_index));
            fractional_part_position_index--;
          } else {
            number_value *= 2;
            number_value += static_cast<double>(temp_str[i] - u'0');
          }
        }

        if (found_invalid_character) {
          number_value += fractional_part_value;

          if (negative_sign_found)
            number_value = -number_value;

          if (exponential_sign_found) {
            if (negative_exponent_sign_found)
              exponential_part_value = -exponential_part_value;

            if (abs(exponential_part_value) != 0)
              number_value *= pow(2, exponential_part_value);
          }
        }

        break;

      case 8:

        if (temp_str[i] == u'.') {
          if (!fractional_part_found) {
            fractional_part_found = true;
            fractional_part_value = 0;
            fractional_part_position_index = -1;
          } else {
            found_invalid_character = true;
          }
        }

        else if (!exponential_sign_found &&
                 ((temp_str[i] == u'e') || (temp_str[i] == u'E'))) {
          exponential_sign_found = true;
        }

        else if (exponential_sign_found && (temp_str[i] == u'+')) {
          if ((temp_str[i - 1] != u'e') && (temp_str[i - 1] != u'E'))
            found_invalid_character = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && (temp_str[i] == u'-')) {
          if ((temp_str[i - 1] != u'e') && (temp_str[i - 1] != u'E'))
            found_invalid_character = true;

          else
            negative_exponent_sign_found = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && exponent_leading_zero_values &&
                 (temp_str[i] == u'0')) {
          exponential_part_value = 0;
        }

        else if ((temp_str[i] < u'0') || (temp_str[i] > u'7')) {
          found_invalid_character = true;
        }

        else {
          if (exponential_sign_found) {
            exponent_leading_zero_values = false;
            exponential_part_value *= 2;
            exponential_part_value += static_cast<int>(temp_str[i] - u'0');
          } else if (fractional_part_found) {
            fractional_part_value +=
                static_cast<double>(static_cast<int>(temp_str[i] - u'0') *
                                    pow(8.f, fractional_part_position_index));
            fractional_part_position_index--;
          } else {
            number_value *= 8;
            number_value += static_cast<double>(temp_str[i] - u'0');
          }
        }

        if (found_invalid_character) {
          number_value += fractional_part_value;

          if (negative_sign_found)
            number_value = -number_value;

          if (exponential_sign_found) {
            if (negative_exponent_sign_found)
              exponential_part_value = -exponential_part_value;

            if (abs(exponential_part_value) != 0)
              number_value *= pow(8, exponential_part_value);
          }
        }

        break;

      case 10:
        if (temp_str[i] == u'.') {
          if (!fractional_part_found) {
            fractional_part_found = true;
            fractional_part_value = 0;
            fractional_part_position_index = -1;
          } else {
            found_invalid_character = true;
          }
        }

        else if (!exponential_sign_found &&
                 ((temp_str[i] == u'e') || (temp_str[i] == u'E'))) {
          exponential_sign_found = true;
        }

        else if (exponential_sign_found && (temp_str[i] == u'+')) {
          if ((temp_str[i - 1] != u'e') && (temp_str[i - 1] != u'E'))
            found_invalid_character = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && (temp_str[i] == u'-')) {
          if ((temp_str[i - 1] != u'e') && (temp_str[i - 1] != u'E'))
            found_invalid_character = true;

          else
            negative_exponent_sign_found = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && exponent_leading_zero_values &&
                 (temp_str[i] == u'0')) {
          exponential_part_value = 0;
        }

        else if ((temp_str[i] < u'0') || (temp_str[i] > u'9')) {
          found_invalid_character = true;
        }

        else {
          if (exponential_sign_found) {
            exponent_leading_zero_values = false;
            exponential_part_value *= 10;
            exponential_part_value += static_cast<int>(temp_str[i] - u'0');
          } else if (fractional_part_found) {
            fractional_part_value +=
                static_cast<double>(static_cast<int>(temp_str[i] - u'0') *
                                    pow(10.f, fractional_part_position_index));
            fractional_part_position_index--;
          } else {
            number_value *= 10;
            number_value += static_cast<double>(temp_str[i] - u'0');
          }
        }

        if (found_invalid_character) {
          number_value += fractional_part_value;

          if (negative_sign_found)
            number_value = -number_value;

          if (exponential_sign_found) {
            if (negative_exponent_sign_found)
              exponential_part_value = -exponential_part_value;

            if (abs(exponential_part_value) != 0)
              number_value *= pow(10, exponential_part_value);
          }
        }

        break;

      case 16:
        if (temp_str[i] == u'.') {
          if (!fractional_part_found) {
            fractional_part_found = true;
            fractional_part_value = 0;
            fractional_part_position_index = -1;
          } else {
            found_invalid_character = true;
          }
        } else {
          if (fractional_part_found) {
            if (((temp_str[i] >= u'0') && (temp_str[i] <= u'9')) ||
                ((temp_str[i] >= u'A') && (temp_str[i] <= u'F'))

                || ((temp_str[i] >= u'a') && (temp_str[i] <= u'f'))) {
              number_value *= 16;

              if ((temp_str[i] >= u'0') && (temp_str[i] <= u'9')) {
                fractional_part_value += static_cast<double>(
                    static_cast<int>(temp_str[i] - u'0') *
                    pow(16.f, fractional_part_position_index));
              }

              else if ((temp_str[i] >= u'A') && (temp_str[i] <= u'F')) {
                fractional_part_value += static_cast<double>(
                    static_cast<int>(temp_str[i] - u'A') *
                    pow(16.f, fractional_part_position_index));
              }

              else if ((temp_str[i] >= u'a') && (temp_str[i] <= u'f')) {
                fractional_part_value += static_cast<double>(
                    static_cast<int>(temp_str[i] - u'a') *
                    pow(16.f, fractional_part_position_index));
              }

              fractional_part_position_index--;
            } else {
              found_invalid_character = true;
            }
          } else {
            if (((temp_str[i] >= u'0') && (temp_str[i] <= u'9')) ||
                ((temp_str[i] >= u'A') && (temp_str[i] <= u'F'))

                || ((temp_str[i] >= u'a') && (temp_str[i] <= u'f'))) {
              number_value *= 16;

              if ((temp_str[i] >= u'0') && (temp_str[i] <= u'9'))
                number_value += static_cast<double>(temp_str[i] - u'0');

              else if ((temp_str[i] >= u'A') && (temp_str[i] <= u'F'))
                number_value += static_cast<double>(10 + (temp_str[i] - u'A'));

              else if ((temp_str[i] >= u'a') && (temp_str[i] <= u'f'))
                number_value += static_cast<double>(10 + (temp_str[i] - u'a'));
            } else {
              found_invalid_character = true;
            }
          }
        }

        if (found_invalid_character) {
          number_value += fractional_part_value;

          if (negative_sign_found)
            number_value = -number_value;
        }

        break;

      default:
        if (temp_str[i] == u'.') {
          if (!fractional_part_found) {
            fractional_part_found = true;
            fractional_part_value = 0;
            fractional_part_position_index = -1;
          } else {
            found_invalid_character = true;
          }
        }

        else if (!exponential_sign_found &&
                 ((temp_str[i] == u'e') || (temp_str[i] == u'E'))) {
          exponential_sign_found = true;
        }

        else if (exponential_sign_found && (temp_str[i] == u'+')) {
          if ((temp_str[i - 1] != u'e') && (temp_str[i - 1] != u'E'))
            found_invalid_character = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && (temp_str[i] == u'-')) {
          if ((temp_str[i - 1] != u'e') && (temp_str[i - 1] != u'E'))
            found_invalid_character = true;

          else
            negative_exponent_sign_found = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && exponent_leading_zero_values &&
                 (temp_str[i] == u'0')) {
          exponential_part_value = 0;
        }

        else if ((temp_str[i] < u'0') || (temp_str[i] > u'9')) {
          found_invalid_character = true;
        }

        else {
          if (exponential_sign_found) {
            exponent_leading_zero_values = false;
            exponential_part_value *= 10;
            exponential_part_value += static_cast<int>(temp_str[i] - u'0');
          } else if (fractional_part_found) {
            fractional_part_value +=
                static_cast<double>(static_cast<int>(temp_str[i] - u'0') *
                                    pow(10.f, fractional_part_position_index));
            fractional_part_position_index--;
          } else {
            number_value *= 10;
            number_value += static_cast<double>(temp_str[i] - u'0');
          }
        }

        if (found_invalid_character) {
          number_value += fractional_part_value;

          if (negative_sign_found)
            number_value = -number_value;

          if (exponential_sign_found) {
            if (negative_exponent_sign_found)
              exponential_part_value = -exponential_part_value;

            if (abs(exponential_part_value) != 0)
              number_value *= pow(10, exponential_part_value);
          }
        }

        break;
    }
  }

  if (!found_invalid_character) {
    number_value += fractional_part_value;

    if (negative_sign_found)
      number_value = -number_value;

    if (exponential_sign_found && (base != 16)) {
      if (negative_exponent_sign_found)
        exponential_part_value = -exponential_part_value;

      if (abs(exponential_part_value) != 0)
        number_value *= pow(2, exponential_part_value);
    }
  }

  if (pos)
    *pos = i;

  return number_value;
}

long double stold(const u16string& str,
                  size_t* pos,
                  int base,
                  bool ignore_leading_white_space_characters) {
  long double number_value{};

  auto negative_sign_found{false};
  long double fractional_part_value{};
  auto fractional_part_found{false};
  int fractional_part_position_index{-1};

  auto exponential_sign_found{false};
  auto negative_exponent_sign_found{false};
  auto exponent_leading_zero_values{true};
  int exponential_part_value{};

  auto found_invalid_character{false};

  auto temp_str{str};

  if (ignore_leading_white_space_characters)
    temp_str = ltrim(str);

  if ((base == 2) &&
      ((temp_str.substr(0, 2) == u"0b") || (temp_str.substr(0, 2) == u"0B"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 2) && ((temp_str[0] == u'b') || (temp_str[0] == u'B'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 8) && ((temp_str.substr(0, 2) == u"0o") ||
                           (temp_str.substr(0, 2) == u"0O"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 8) && ((temp_str[0] == u'0') || (temp_str[0] == u'o') ||
                           (temp_str[0] == u'O'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 16) && ((temp_str.substr(0, 2) == u"0x") ||
                            (temp_str.substr(0, 2) == u"0X"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 16) && ((temp_str[0] == u'x') || (temp_str[0] == u'X'))) {
    temp_str.erase(cbegin(temp_str));
  }

  if (temp_str[0] == u'+') {
    temp_str.erase(cbegin(temp_str));
  }

  else if (temp_str[0] == u'-') {
    negative_sign_found = true;
    temp_str.erase(cbegin(temp_str));
  }

  if (temp_str[0] == u'.') {
    fractional_part_found = true;
    temp_str.erase(cbegin(temp_str));
  }

  if (pos)
    *pos = 0;

  if (!fractional_part_found && (temp_str[0] == u'0'))
    return number_value;

  if ((base != 16) && ((temp_str[0] == u'e') || (temp_str[0] == u'E'))) {
    if (fractional_part_found)
      return number_value;
    exponential_sign_found = true;
    temp_str.erase(cbegin(temp_str));
  }

  u16string::size_type i{0u};

  for (; (!found_invalid_character && (i < temp_str.size())); i++) {
    switch (base) {
      case 2:

        if (temp_str[i] == u'.') {
          if (!fractional_part_found) {
            fractional_part_found = true;
            fractional_part_value = 0;
            fractional_part_position_index = -1;
          } else {
            found_invalid_character = true;
          }
        }

        else if (!exponential_sign_found &&
                 ((temp_str[i] == u'e') || (temp_str[i] == u'E'))) {
          exponential_sign_found = true;
        }

        else if (exponential_sign_found && (temp_str[i] == u'+')) {
          if ((temp_str[i - 1] != u'e') && (temp_str[i - 1] != u'E'))
            found_invalid_character = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && (temp_str[i] == u'-')) {
          if ((temp_str[i - 1] != u'e') && (temp_str[i - 1] != u'E'))
            found_invalid_character = true;

          else
            negative_exponent_sign_found = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && exponent_leading_zero_values &&
                 (temp_str[i] == u'0')) {
          exponential_part_value = 0;
        }

        else if ((temp_str[i] < u'0') || (temp_str[i] > u'1')) {
          found_invalid_character = true;
        }

        else {
          if (exponential_sign_found) {
            exponent_leading_zero_values = false;
            exponential_part_value *= 2;
            exponential_part_value += static_cast<int>(temp_str[i] - u'0');
          } else if (fractional_part_found) {
            fractional_part_value += static_cast<long double>(
                static_cast<int>(temp_str[i] - u'0') *
                pow(2.f, fractional_part_position_index));
            fractional_part_position_index--;
          } else {
            number_value *= 2;
            number_value += static_cast<long double>(temp_str[i] - u'0');
          }
        }

        if (found_invalid_character) {
          number_value += fractional_part_value;

          if (negative_sign_found)
            number_value = -number_value;

          if (exponential_sign_found) {
            if (negative_exponent_sign_found)
              exponential_part_value = -exponential_part_value;

            if (abs(exponential_part_value) != 0)
              number_value *= powl(2, exponential_part_value);
          }
        }

        break;

      case 8:

        if (temp_str[i] == u'.') {
          if (!fractional_part_found) {
            fractional_part_found = true;
            fractional_part_value = 0;
            fractional_part_position_index = -1;
          } else {
            found_invalid_character = true;
          }
        }

        else if (!exponential_sign_found &&
                 ((temp_str[i] == u'e') || (temp_str[i] == u'E'))) {
          exponential_sign_found = true;
        }

        else if (exponential_sign_found && (temp_str[i] == u'+')) {
          if ((temp_str[i - 1] != u'e') && (temp_str[i - 1] != u'E'))
            found_invalid_character = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && (temp_str[i] == u'-')) {
          if ((temp_str[i - 1] != u'e') && (temp_str[i - 1] != u'E'))
            found_invalid_character = true;

          else
            negative_exponent_sign_found = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && exponent_leading_zero_values &&
                 (temp_str[i] == u'0')) {
          exponential_part_value = 0;
        }

        else if ((temp_str[i] < u'0') || (temp_str[i] > u'7')) {
          found_invalid_character = true;
        }

        else {
          if (exponential_sign_found) {
            exponent_leading_zero_values = false;
            exponential_part_value *= 2;
            exponential_part_value += static_cast<int>(temp_str[i] - u'0');
          } else if (fractional_part_found) {
            fractional_part_value += static_cast<long double>(
                static_cast<int>(temp_str[i] - u'0') *
                pow(8.f, fractional_part_position_index));
            fractional_part_position_index--;
          } else {
            number_value *= 8;
            number_value += static_cast<long double>(temp_str[i] - u'0');
          }
        }

        if (found_invalid_character) {
          number_value += fractional_part_value;

          if (negative_sign_found)
            number_value = -number_value;

          if (exponential_sign_found) {
            if (negative_exponent_sign_found)
              exponential_part_value = -exponential_part_value;

            if (abs(exponential_part_value) != 0)
              number_value *= powl(8, exponential_part_value);
          }
        }

        break;

      case 10:
        if (temp_str[i] == u'.') {
          if (!fractional_part_found) {
            fractional_part_found = true;
            fractional_part_value = 0;
            fractional_part_position_index = -1;
          } else {
            found_invalid_character = true;
          }
        }

        else if (!exponential_sign_found &&
                 ((temp_str[i] == u'e') || (temp_str[i] == u'E'))) {
          exponential_sign_found = true;
        }

        else if (exponential_sign_found && (temp_str[i] == u'+')) {
          if ((temp_str[i - 1] != u'e') && (temp_str[i - 1] != u'E'))
            found_invalid_character = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && (temp_str[i] == u'-')) {
          if ((temp_str[i - 1] != u'e') && (temp_str[i - 1] != u'E'))
            found_invalid_character = true;

          else
            negative_exponent_sign_found = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && exponent_leading_zero_values &&
                 (temp_str[i] == u'0')) {
          exponential_part_value = 0;
        }

        else if ((temp_str[i] < u'0') || (temp_str[i] > u'9')) {
          found_invalid_character = true;
        }

        else {
          if (exponential_sign_found) {
            exponent_leading_zero_values = false;
            exponential_part_value *= 10;
            exponential_part_value += static_cast<int>(temp_str[i] - u'0');
          } else if (fractional_part_found) {
            fractional_part_value += static_cast<long double>(
                static_cast<int>(temp_str[i] - u'0') *
                pow(10.f, fractional_part_position_index));
            fractional_part_position_index--;
          } else {
            number_value *= 10;
            number_value += static_cast<long double>(temp_str[i] - u'0');
          }
        }

        if (found_invalid_character) {
          number_value += fractional_part_value;

          if (negative_sign_found)
            number_value = -number_value;

          if (exponential_sign_found) {
            if (negative_exponent_sign_found)
              exponential_part_value = -exponential_part_value;

            if (abs(exponential_part_value) != 0)
              number_value *= powl(10, exponential_part_value);
          }
        }

        break;

      case 16:
        if (temp_str[i] == u'.') {
          if (!fractional_part_found) {
            fractional_part_found = true;
            fractional_part_value = 0;
            fractional_part_position_index = -1;
          } else {
            found_invalid_character = true;
          }
        } else {
          if (fractional_part_found) {
            if (((temp_str[i] >= u'0') && (temp_str[i] <= u'9')) ||
                ((temp_str[i] >= u'A') && (temp_str[i] <= u'F'))

                || ((temp_str[i] >= u'a') && (temp_str[i] <= u'f'))) {
              number_value *= 16;

              if ((temp_str[i] >= u'0') && (temp_str[i] <= u'9')) {
                fractional_part_value += static_cast<long double>(
                    static_cast<int>(temp_str[i] - u'0') *
                    pow(16.f, fractional_part_position_index));
              }

              else if ((temp_str[i] >= u'A') && (temp_str[i] <= u'F')) {
                fractional_part_value += static_cast<long double>(
                    static_cast<int>(temp_str[i] - u'A') *
                    pow(16.f, fractional_part_position_index));
              }

              else if ((temp_str[i] >= u'a') && (temp_str[i] <= u'f')) {
                fractional_part_value += static_cast<long double>(
                    static_cast<int>(temp_str[i] - u'a') *
                    pow(16.f, fractional_part_position_index));
              }

              fractional_part_position_index--;
            } else {
              found_invalid_character = true;
            }
          } else {
            if (((temp_str[i] >= u'0') && (temp_str[i] <= u'9')) ||
                ((temp_str[i] >= u'A') && (temp_str[i] <= u'F'))

                || ((temp_str[i] >= u'a') && (temp_str[i] <= u'f'))) {
              number_value *= 16;

              if ((temp_str[i] >= u'0') && (temp_str[i] <= u'9'))
                number_value += static_cast<long double>(temp_str[i] - u'0');

              else if ((temp_str[i] >= u'A') && (temp_str[i] <= u'F'))
                number_value +=
                    static_cast<long double>(10 + (temp_str[i] - u'A'));

              else if ((temp_str[i] >= u'a') && (temp_str[i] <= u'f'))
                number_value +=
                    static_cast<long double>(10 + (temp_str[i] - u'a'));
            } else {
              found_invalid_character = true;
            }
          }
        }

        if (found_invalid_character) {
          number_value += fractional_part_value;

          if (negative_sign_found)
            number_value = -number_value;
        }

        break;

      default:
        if (temp_str[i] == u'.') {
          if (!fractional_part_found) {
            fractional_part_found = true;
            fractional_part_value = 0;
            fractional_part_position_index = -1;
          } else {
            found_invalid_character = true;
          }
        }

        else if (!exponential_sign_found &&
                 ((temp_str[i] == u'e') || (temp_str[i] == u'E'))) {
          exponential_sign_found = true;
        }

        else if (exponential_sign_found && (temp_str[i] == u'+')) {
          if ((temp_str[i - 1] != u'e') && (temp_str[i - 1] != u'E'))
            found_invalid_character = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && (temp_str[i] == u'-')) {
          if ((temp_str[i - 1] != u'e') && (temp_str[i - 1] != u'E'))
            found_invalid_character = true;

          else
            negative_exponent_sign_found = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && exponent_leading_zero_values &&
                 (temp_str[i] == u'0')) {
          exponential_part_value = 0;
        }

        else if ((temp_str[i] < u'0') || (temp_str[i] > u'9')) {
          found_invalid_character = true;
        }

        else {
          if (exponential_sign_found) {
            exponent_leading_zero_values = false;
            exponential_part_value *= 10;
            exponential_part_value += static_cast<int>(temp_str[i] - u'0');
          } else if (fractional_part_found) {
            fractional_part_value += static_cast<long double>(
                static_cast<int>(temp_str[i] - u'0') *
                pow(10.f, fractional_part_position_index));
            fractional_part_position_index--;
          } else {
            number_value *= 10;
            number_value += static_cast<long double>(temp_str[i] - u'0');
          }
        }

        if (found_invalid_character) {
          number_value += fractional_part_value;

          if (negative_sign_found)
            number_value = -number_value;

          if (exponential_sign_found) {
            if (negative_exponent_sign_found)
              exponential_part_value = -exponential_part_value;

            if (abs(exponential_part_value) != 0)
              number_value *= powl(10, exponential_part_value);
          }
        }

        break;
    }
  }

  if (!found_invalid_character) {
    number_value += fractional_part_value;

    if (negative_sign_found)
      number_value = -number_value;

    if (exponential_sign_found && (base != 16)) {
      if (negative_exponent_sign_found)
        exponential_part_value = -exponential_part_value;

      if (abs(exponential_part_value) != 0)
        number_value *= powl(2, exponential_part_value);
    }
  }

  if (pos)
    *pos = i;

  return number_value;
}

int stoi(const u32string& str,
         size_t* pos,
         int base,
         bool ignore_leading_white_space_characters) {
  int number_value{};

  auto temp_str{str};

  if (ignore_leading_white_space_characters)
    temp_str = ltrim(str);

  auto found_invalid_character{false};

  if ((base == 2) && ((temp_str[0] == U'b') || (temp_str[0] == U'B'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 2) && ((temp_str.substr(0, 2) == U"0b") ||
                           (temp_str.substr(0, 2) == U"0B"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 8) && ((temp_str[0] == U'0') || (temp_str[0] == U'o') ||
                           (temp_str[0] == U'O'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 8) && ((temp_str.substr(0, 2) == U"0o") ||
                           (temp_str.substr(0, 2) == U"0O"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 16) && ((temp_str[0] == U'x') || (temp_str[0] == U'X'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 16) && ((temp_str.substr(0, 2) == U"0x") ||
                            (temp_str.substr(0, 2) == U"0X"))) {
    temp_str.assign(temp_str.substr(2));
  }

  u32string::size_type i{0u};

  for (; (!found_invalid_character && (i < temp_str.size())); i++) {
    switch (base) {
      case 2:
        if ((temp_str[i] < U'0') || (temp_str[i] > U'1'))
          found_invalid_character = true;

        number_value *= 2;

        number_value += static_cast<int>(temp_str[i] - U'0');

        break;

      case 8:
        if ((temp_str[i] < U'0') || (temp_str[i] > U'7'))
          found_invalid_character = true;

        number_value *= 8;

        number_value += static_cast<int>(temp_str[i] - U'0');

        break;

      case 10:
        if ((temp_str[i] < U'0') || (temp_str[i] > U'9'))
          found_invalid_character = true;

        number_value *= 10;

        number_value += static_cast<int>(temp_str[i] - U'0');

        break;

      case 16:
        if (((temp_str[i] >= U'0') && (temp_str[i] <= U'9')) ||
            ((temp_str[i] >= U'A') && (temp_str[i] <= U'F'))

            || ((temp_str[i] >= U'a') && (temp_str[i] <= U'f'))) {
          number_value *= 16;

          if ((temp_str[i] >= U'0') && (temp_str[i] <= U'9'))
            number_value += static_cast<int>(temp_str[i] - U'0');

          else if ((temp_str[i] >= U'A') && (temp_str[i] <= U'F'))
            number_value += static_cast<int>(10 + (temp_str[i] - U'A'));

          else if ((temp_str[i] >= U'a') && (temp_str[i] <= U'f'))
            number_value += static_cast<int>(10 + (temp_str[i] - U'a'));
        } else {
          found_invalid_character = true;
        }

        break;

      default:
        if ((temp_str[i] < U'0') || (temp_str[i] > U'9'))
          found_invalid_character = true;

        number_value *= 10;

        number_value += static_cast<int>(temp_str[i] - U'0');

        break;
    }
  }

  if (pos)
    *pos = i;

  return number_value;
}

long stol(const u32string& str,
          size_t* pos,
          int base,
          bool ignore_leading_white_space_characters) {
  long number_value{};

  auto temp_str{str};

  if (ignore_leading_white_space_characters)
    temp_str = ltrim(str);

  auto found_invalid_character{false};

  if ((base == 2) && ((temp_str[0] == U'b') || (temp_str[0] == U'B'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 2) && ((temp_str.substr(0, 2) == U"0b") ||
                           (temp_str.substr(0, 2) == U"0B"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 8) && ((temp_str[0] == U'0') || (temp_str[0] == U'o') ||
                           (temp_str[0] == U'O'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 8) && ((temp_str.substr(0, 2) == U"0o") ||
                           (temp_str.substr(0, 2) == U"0O"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 16) && ((temp_str[0] == U'x') || (temp_str[0] == U'X'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 16) && ((temp_str.substr(0, 2) == U"0x") ||
                            (temp_str.substr(0, 2) == U"0X"))) {
    temp_str.assign(temp_str.substr(2));
  }

  u32string::size_type i{0u};

  for (; (!found_invalid_character && (i < temp_str.size())); i++) {
    switch (base) {
      case 2:
        if ((temp_str[i] < U'0') || (temp_str[i] > U'1'))
          found_invalid_character = true;

        number_value *= 2;

        number_value += static_cast<long>(temp_str[i] - U'0');

        break;

      case 8:
        if ((temp_str[i] < U'0') || (temp_str[i] > U'7'))
          found_invalid_character = true;

        number_value *= 8;

        number_value += static_cast<long>(temp_str[i] - U'0');

        break;

      case 10:
        if ((temp_str[i] < U'0') || (temp_str[i] > U'9'))
          found_invalid_character = true;

        number_value *= 10;

        number_value += static_cast<long>(temp_str[i] - U'0');

        break;

      case 16:
        if (((temp_str[i] >= U'0') && (temp_str[i] <= U'9')) ||
            ((temp_str[i] >= U'A') && (temp_str[i] <= U'F'))

            || ((temp_str[i] >= U'a') && (temp_str[i] <= U'f'))) {
          number_value *= 16;

          if ((temp_str[i] >= U'0') && (temp_str[i] <= U'9'))
            number_value += static_cast<long>(temp_str[i] - U'0');

          else if ((temp_str[i] >= U'A') && (temp_str[i] <= U'F'))
            number_value += static_cast<long>(10 + (temp_str[i] - U'A'));

          else if ((temp_str[i] >= U'a') && (temp_str[i] <= U'f'))
            number_value += static_cast<long>(10 + (temp_str[i] - U'a'));
        } else {
          found_invalid_character = true;
        }

        break;

      default:
        if ((temp_str[i] < U'0') || (temp_str[i] > U'9'))
          found_invalid_character = true;

        number_value *= 10;

        number_value += static_cast<long>(temp_str[i] - U'0');

        break;
    }
  }

  if (pos)
    *pos = i;

  return number_value;
}

unsigned long stoul(const u32string& str,
                    size_t* pos,
                    int base,
                    bool ignore_leading_white_space_characters) {
  unsigned long number_value{};

  auto temp_str{str};

  if (ignore_leading_white_space_characters)
    temp_str = ltrim(str);

  auto found_invalid_character{false};

  if ((base == 2) && ((temp_str[0] == U'b') || (temp_str[0] == U'B'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 2) && ((temp_str.substr(0, 2) == U"0b") ||
                           (temp_str.substr(0, 2) == U"0B"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 8) && ((temp_str[0] == U'0') || (temp_str[0] == U'o') ||
                           (temp_str[0] == U'O'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 8) && ((temp_str.substr(0, 2) == U"0o") ||
                           (temp_str.substr(0, 2) == U"0O"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 16) && ((temp_str[0] == U'x') || (temp_str[0] == U'X'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 16) && ((temp_str.substr(0, 2) == U"0x") ||
                            (temp_str.substr(0, 2) == U"0X"))) {
    temp_str.assign(temp_str.substr(2));
  }

  u32string::size_type i{0u};

  for (; (!found_invalid_character && (i < temp_str.size())); i++) {
    switch (base) {
      case 2:
        if ((temp_str[i] < U'0') || (temp_str[i] > U'1'))
          found_invalid_character = true;

        number_value *= 2;

        number_value += static_cast<unsigned long>(temp_str[i] - U'0');

        break;

      case 8:
        if ((temp_str[i] < U'0') || (temp_str[i] > U'7'))
          found_invalid_character = true;

        number_value *= 8;

        number_value += static_cast<unsigned long>(temp_str[i] - U'0');

        break;

      case 10:
        if ((temp_str[i] < U'0') || (temp_str[i] > U'9'))
          found_invalid_character = true;

        number_value *= 10;

        number_value += static_cast<unsigned long>(temp_str[i] - U'0');

        break;

      case 16:
        if (((temp_str[i] >= U'0') && (temp_str[i] <= U'9')) ||
            ((temp_str[i] >= U'A') && (temp_str[i] <= U'F'))

            || ((temp_str[i] >= U'a') && (temp_str[i] <= U'f'))) {
          number_value *= 16;

          if ((temp_str[i] >= U'0') && (temp_str[i] <= U'9'))
            number_value += static_cast<unsigned long>(temp_str[i] - U'0');

          else if ((temp_str[i] >= U'A') && (temp_str[i] <= U'F'))
            number_value +=
                static_cast<unsigned long>(10 + (temp_str[i] - U'A'));

          else if ((temp_str[i] >= U'a') && (temp_str[i] <= U'f'))
            number_value +=
                static_cast<unsigned long>(10 + (temp_str[i] - U'a'));
        } else {
          found_invalid_character = true;
        }

        break;

      default:
        if ((temp_str[i] < U'0') || (temp_str[i] > U'9'))
          found_invalid_character = true;

        number_value *= 10;

        number_value += static_cast<unsigned long>(temp_str[i] - U'0');

        break;
    }
  }

  if (pos)
    *pos = i;

  return number_value;
}

long long stoll(const u32string& str,
                size_t* pos,
                int base,
                bool ignore_leading_white_space_characters) {
  long long number_value{};

  auto temp_str{str};

  if (ignore_leading_white_space_characters)
    temp_str = ltrim(str);

  auto found_invalid_character{false};

  if ((base == 2) && ((temp_str[0] == U'b') || (temp_str[0] == U'B'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 2) && ((temp_str.substr(0, 2) == U"0b") ||
                           (temp_str.substr(0, 2) == U"0B"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 8) && ((temp_str[0] == U'0') || (temp_str[0] == U'o') ||
                           (temp_str[0] == U'O'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 8) && ((temp_str.substr(0, 2) == U"0o") ||
                           (temp_str.substr(0, 2) == U"0O"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 16) && ((temp_str[0] == U'x') || (temp_str[0] == U'X'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 16) && ((temp_str.substr(0, 2) == U"0x") ||
                            (temp_str.substr(0, 2) == U"0X"))) {
    temp_str.assign(temp_str.substr(2));
  }

  u32string::size_type i{0u};

  for (; (!found_invalid_character && (i < temp_str.size())); i++) {
    switch (base) {
      case 2:
        if ((temp_str[i] < U'0') || (temp_str[i] > U'1'))
          found_invalid_character = true;

        number_value *= 2;

        number_value += static_cast<long long>(temp_str[i] - U'0');

        break;

      case 8:
        if ((temp_str[i] < U'0') || (temp_str[i] > U'7'))
          found_invalid_character = true;

        number_value *= 8;

        number_value += static_cast<long long>(temp_str[i] - U'0');

        break;

      case 10:
        if ((temp_str[i] < U'0') || (temp_str[i] > U'9'))
          found_invalid_character = true;

        number_value *= 10;

        number_value += static_cast<long long>(temp_str[i] - U'0');

        break;

      case 16:
        if (((temp_str[i] >= U'0') && (temp_str[i] <= U'9')) ||
            ((temp_str[i] >= U'A') && (temp_str[i] <= U'F'))

            || ((temp_str[i] >= U'a') && (temp_str[i] <= U'f'))) {
          number_value *= 16;

          if ((temp_str[i] >= U'0') && (temp_str[i] <= U'9'))
            number_value += static_cast<long long>(temp_str[i] - U'0');

          else if ((temp_str[i] >= U'A') && (temp_str[i] <= U'F'))
            number_value += static_cast<long long>(10 + (temp_str[i] - U'A'));

          else if ((temp_str[i] >= U'a') && (temp_str[i] <= U'f'))
            number_value += static_cast<long long>(10 + (temp_str[i] - U'a'));
        } else {
          found_invalid_character = true;
        }

        break;

      default:
        if ((temp_str[i] < U'0') || (temp_str[i] > U'9'))
          found_invalid_character = true;

        number_value *= 10;

        number_value += static_cast<long long>(temp_str[i] - U'0');

        break;
    }
  }

  if (pos)
    *pos = i;

  return number_value;
}

unsigned long long stoull(const u32string& str,
                          size_t* pos,
                          int base,
                          bool ignore_leading_white_space_characters) {
  unsigned long long number_value{};

  auto temp_str{str};

  if (ignore_leading_white_space_characters)
    temp_str = ltrim(str);

  auto found_invalid_character{false};

  if ((base == 2) && ((temp_str[0] == U'b') || (temp_str[0] == U'B'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 2) && ((temp_str.substr(0, 2) == U"0b") ||
                           (temp_str.substr(0, 2) == U"0B"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 8) && ((temp_str[0] == U'0') || (temp_str[0] == U'o') ||
                           (temp_str[0] == U'O'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 8) && ((temp_str.substr(0, 2) == U"0o") ||
                           (temp_str.substr(0, 2) == U"0O"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 16) && ((temp_str[0] == U'x') || (temp_str[0] == U'X'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 16) && ((temp_str.substr(0, 2) == U"0x") ||
                            (temp_str.substr(0, 2) == U"0X"))) {
    temp_str.assign(temp_str.substr(2));
  }

  u32string::size_type i{0u};

  for (; (!found_invalid_character && (i < temp_str.size())); i++) {
    switch (base) {
      case 2:
        if ((temp_str[i] < U'0') || (temp_str[i] > U'1'))
          found_invalid_character = true;

        number_value *= 2;

        number_value += static_cast<unsigned long long>(temp_str[i] - U'0');

        break;

      case 8:
        if ((temp_str[i] < U'0') || (temp_str[i] > U'7'))
          found_invalid_character = true;

        number_value *= 8;

        number_value += static_cast<unsigned long long>(temp_str[i] - U'0');

        break;

      case 10:
        if ((temp_str[i] < U'0') || (temp_str[i] > U'9'))
          found_invalid_character = true;

        number_value *= 10;

        number_value += static_cast<unsigned long long>(temp_str[i] - U'0');

        break;

      case 16:
        if (((temp_str[i] >= U'0') && (temp_str[i] <= U'9')) ||
            ((temp_str[i] >= U'A') && (temp_str[i] <= U'F'))

            || ((temp_str[i] >= U'a') && (temp_str[i] <= U'f'))) {
          number_value *= 16;

          if ((temp_str[i] >= U'0') && (temp_str[i] <= U'9'))
            number_value += static_cast<unsigned long long>(temp_str[i] - U'0');

          else if ((temp_str[i] >= U'A') && (temp_str[i] <= U'F'))
            number_value +=
                static_cast<unsigned long long>(10 + (temp_str[i] - U'A'));

          else if ((temp_str[i] >= U'a') && (temp_str[i] <= U'f'))
            number_value +=
                static_cast<unsigned long long>(10 + (temp_str[i] - U'a'));
        } else {
          found_invalid_character = true;
        }

        break;

      default:
        if ((temp_str[i] < U'0') || (temp_str[i] > U'9'))
          found_invalid_character = true;

        number_value *= 10;

        number_value += static_cast<unsigned long long>(temp_str[i] - U'0');

        break;
    }
  }

  if (pos)
    *pos = i;

  return number_value;
}

float stof(const u32string& str,
           size_t* pos,
           int base,
           bool ignore_leading_white_space_characters) {
  float number_value{};

  auto negative_sign_found{false};
  float fractional_part_value{};
  auto fractional_part_found{false};
  int fractional_part_position_index{-1};

  auto exponential_sign_found{false};
  auto negative_exponent_sign_found{false};
  auto exponent_leading_zero_values{true};
  int exponential_part_value{};

  auto found_invalid_character{false};

  auto temp_str{str};

  if (ignore_leading_white_space_characters)
    temp_str = ltrim(str);

  if ((base == 2) &&
      ((temp_str.substr(0, 2) == U"0b") || (temp_str.substr(0, 2) == U"0B"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 2) && ((temp_str[0] == U'b') || (temp_str[0] == U'B'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 8) && ((temp_str.substr(0, 2) == U"0o") ||
                           (temp_str.substr(0, 2) == U"0O"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 8) && ((temp_str[0] == U'0') || (temp_str[0] == U'o') ||
                           (temp_str[0] == U'O'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 16) && ((temp_str.substr(0, 2) == U"0x") ||
                            (temp_str.substr(0, 2) == U"0X"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 16) && ((temp_str[0] == U'x') || (temp_str[0] == U'X'))) {
    temp_str.erase(cbegin(temp_str));
  }

  if (temp_str[0] == U'+') {
    temp_str.erase(cbegin(temp_str));
  }

  else if (temp_str[0] == U'-') {
    negative_sign_found = true;
    temp_str.erase(cbegin(temp_str));
  }

  if (temp_str[0] == U'.') {
    fractional_part_found = true;
    temp_str.erase(cbegin(temp_str));
  }

  if (pos)
    *pos = 0;

  if (!fractional_part_found && (temp_str[0] == U'0'))
    return number_value;

  if ((base != 16) && ((temp_str[0] == U'e') || (temp_str[0] == U'E'))) {
    if (fractional_part_found)
      return number_value;
    exponential_sign_found = true;
    temp_str.erase(cbegin(temp_str));
  }

  u32string::size_type i{0u};

  for (; (!found_invalid_character && (i < temp_str.size())); i++) {
    switch (base) {
      case 2:

        if (temp_str[i] == U'.') {
          if (!fractional_part_found) {
            fractional_part_found = true;
            fractional_part_value = 0.f;
            fractional_part_position_index = -1;
          } else {
            found_invalid_character = true;
          }
        }

        else if (!exponential_sign_found &&
                 ((temp_str[i] == U'e') || (temp_str[i] == U'E'))) {
          exponential_sign_found = true;
        }

        else if (exponential_sign_found && (temp_str[i] == U'+')) {
          if ((temp_str[i - 1] != U'e') && (temp_str[i - 1] != U'e'))
            found_invalid_character = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && (temp_str[i] == U'-')) {
          if ((temp_str[i - 1] != U'e') && (temp_str[i - 1] != U'e'))
            found_invalid_character = true;

          else
            negative_exponent_sign_found = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && exponent_leading_zero_values &&
                 (temp_str[i] == U'0')) {
          exponential_part_value = 0;
        }

        else if ((temp_str[i] < U'0') || (temp_str[i] > U'1')) {
          found_invalid_character = true;
        }

        else {
          if (exponential_sign_found) {
            exponent_leading_zero_values = false;
            exponential_part_value *= 2;
            exponential_part_value += static_cast<int>(temp_str[i] - U'0');
          } else if (fractional_part_found) {
            fractional_part_value +=
                static_cast<float>(static_cast<int>(temp_str[i] - U'0') *
                                   pow(2.f, fractional_part_position_index));
            fractional_part_position_index--;
          } else {
            number_value *= 2;
            number_value += static_cast<float>(temp_str[i] - U'0');
          }
        }

        if (found_invalid_character) {
          number_value += fractional_part_value;

          if (negative_sign_found)
            number_value = -number_value;

          if (exponential_sign_found) {
            if (negative_exponent_sign_found)
              exponential_part_value = -exponential_part_value;

            if (abs(exponential_part_value) != 0)
              number_value *= powf(2.f, exponential_part_value);
          }
        }

        break;

      case 8:

        if (temp_str[i] == U'.') {
          if (!fractional_part_found) {
            fractional_part_found = true;
            fractional_part_value = 0.f;
            fractional_part_position_index = -1;
          } else {
            found_invalid_character = true;
          }
        }

        else if (!exponential_sign_found &&
                 ((temp_str[i] == U'e') || (temp_str[i] == U'E'))) {
          exponential_sign_found = true;
        }

        else if (exponential_sign_found && (temp_str[i] == U'+')) {
          if ((temp_str[i - 1] != U'e') && (temp_str[i - 1] != U'e'))
            found_invalid_character = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && (temp_str[i] == U'-')) {
          if ((temp_str[i - 1] != U'e') && (temp_str[i - 1] != U'e'))
            found_invalid_character = true;

          else
            negative_exponent_sign_found = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && exponent_leading_zero_values &&
                 (temp_str[i] == U'0')) {
          exponential_part_value = 0;
        }

        else if ((temp_str[i] < U'0') || (temp_str[i] > U'7')) {
          found_invalid_character = true;
        }

        else {
          if (exponential_sign_found) {
            exponent_leading_zero_values = false;
            exponential_part_value *= 2;
            exponential_part_value += static_cast<int>(temp_str[i] - U'0');
          } else if (fractional_part_found) {
            fractional_part_value +=
                static_cast<float>(static_cast<int>(temp_str[i] - U'0') *
                                   pow(8.f, fractional_part_position_index));
            fractional_part_position_index--;
          } else {
            number_value *= 8;
            number_value += static_cast<float>(temp_str[i] - U'0');
          }
        }

        if (found_invalid_character) {
          number_value += fractional_part_value;

          if (negative_sign_found)
            number_value = -number_value;

          if (exponential_sign_found) {
            if (negative_exponent_sign_found)
              exponential_part_value = -exponential_part_value;

            if (abs(exponential_part_value) != 0)
              number_value *= powf(8.f, exponential_part_value);
          }
        }

        break;

      case 10:
        if (temp_str[i] == U'.') {
          if (!fractional_part_found) {
            fractional_part_found = true;
            fractional_part_value = 0.f;
            fractional_part_position_index = -1;
          } else {
            found_invalid_character = true;
          }
        }

        else if (!exponential_sign_found &&
                 ((temp_str[i] == U'e') || (temp_str[i] == U'E'))) {
          exponential_sign_found = true;
        }

        else if (exponential_sign_found && (temp_str[i] == U'+')) {
          if ((temp_str[i - 1] != U'e') && (temp_str[i - 1] != U'e'))
            found_invalid_character = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && (temp_str[i] == U'-')) {
          if ((temp_str[i - 1] != U'e') && (temp_str[i - 1] != U'e'))
            found_invalid_character = true;

          else
            negative_exponent_sign_found = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && exponent_leading_zero_values &&
                 (temp_str[i] == U'0')) {
          exponential_part_value = 0;
        }

        else if ((temp_str[i] < U'0') || (temp_str[i] > U'9')) {
          found_invalid_character = true;
        }

        else {
          if (exponential_sign_found) {
            exponent_leading_zero_values = false;
            exponential_part_value *= 10;
            exponential_part_value += static_cast<int>(temp_str[i] - U'0');
          } else if (fractional_part_found) {
            fractional_part_value +=
                static_cast<float>(static_cast<int>(temp_str[i] - U'0') *
                                   pow(10.f, fractional_part_position_index));
            fractional_part_position_index--;
          } else {
            number_value *= 10;
            number_value += static_cast<float>(temp_str[i] - U'0');
          }
        }

        if (found_invalid_character) {
          number_value += fractional_part_value;

          if (negative_sign_found)
            number_value = -number_value;

          if (exponential_sign_found) {
            if (negative_exponent_sign_found)
              exponential_part_value = -exponential_part_value;

            if (abs(exponential_part_value) != 0)
              number_value *= powf(10.f, exponential_part_value);
          }
        }

        break;

      case 16:
        if (temp_str[i] == U'.') {
          if (!fractional_part_found) {
            fractional_part_found = true;
            fractional_part_value = 0.f;
            fractional_part_position_index = -1;
          } else {
            found_invalid_character = true;
          }
        } else {
          if (fractional_part_found) {
            if (((temp_str[i] >= U'0') && (temp_str[i] <= U'9')) ||
                ((temp_str[i] >= U'A') && (temp_str[i] <= U'F'))

                || ((temp_str[i] >= U'a') && (temp_str[i] <= U'f'))) {
              number_value *= 16;

              if ((temp_str[i] >= U'0') && (temp_str[i] <= U'9')) {
                fractional_part_value += static_cast<float>(
                    static_cast<int>(temp_str[i] - U'0') *
                    pow(16.f, fractional_part_position_index));
              }

              else if ((temp_str[i] >= U'A') && (temp_str[i] <= U'F')) {
                fractional_part_value += static_cast<float>(
                    static_cast<int>(temp_str[i] - U'A') *
                    pow(16.f, fractional_part_position_index));
              }

              else if ((temp_str[i] >= U'a') && (temp_str[i] <= U'f')) {
                fractional_part_value += static_cast<float>(
                    static_cast<int>(temp_str[i] - U'a') *
                    pow(16.f, fractional_part_position_index));
              }

              fractional_part_position_index--;
            } else {
              found_invalid_character = true;
            }
          } else {
            if (((temp_str[i] >= U'0') && (temp_str[i] <= U'9')) ||
                ((temp_str[i] >= U'A') && (temp_str[i] <= U'F'))

                || ((temp_str[i] >= U'a') && (temp_str[i] <= U'f'))) {
              number_value *= 16;

              if ((temp_str[i] >= U'0') && (temp_str[i] <= U'9'))
                number_value += static_cast<float>(temp_str[i] - U'0');

              else if ((temp_str[i] >= U'A') && (temp_str[i] <= U'F'))
                number_value += static_cast<float>(10 + (temp_str[i] - U'A'));

              else if ((temp_str[i] >= U'a') && (temp_str[i] <= U'f'))
                number_value += static_cast<float>(10 + (temp_str[i] - U'a'));
            } else {
              found_invalid_character = true;
            }
          }
        }

        if (found_invalid_character) {
          number_value += fractional_part_value;

          if (negative_sign_found)
            number_value = -number_value;
        }

        break;

      default:
        if (temp_str[i] == U'.') {
          if (!fractional_part_found) {
            fractional_part_found = true;
            fractional_part_value = 0.f;
            fractional_part_position_index = -1;
          } else {
            found_invalid_character = true;
          }
        }

        else if (!exponential_sign_found &&
                 ((temp_str[i] == U'e') || (temp_str[i] == U'E'))) {
          exponential_sign_found = true;
        }

        else if (exponential_sign_found && (temp_str[i] == U'+')) {
          if ((temp_str[i - 1] != U'e') && (temp_str[i - 1] != U'e'))
            found_invalid_character = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && (temp_str[i] == U'-')) {
          if ((temp_str[i - 1] != U'e') && (temp_str[i - 1] != U'e'))
            found_invalid_character = true;

          else
            negative_exponent_sign_found = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && exponent_leading_zero_values &&
                 (temp_str[i] == U'0')) {
          exponential_part_value = 0;
        }

        else if ((temp_str[i] < U'0') || (temp_str[i] > U'9')) {
          found_invalid_character = true;
        }

        else {
          if (exponential_sign_found) {
            exponent_leading_zero_values = false;
            exponential_part_value *= 10;
            exponential_part_value += static_cast<int>(temp_str[i] - U'0');
          } else if (fractional_part_found) {
            fractional_part_value +=
                static_cast<float>(static_cast<int>(temp_str[i] - U'0') *
                                   pow(10.f, fractional_part_position_index));
            fractional_part_position_index--;
          } else {
            number_value *= 10;
            number_value += static_cast<float>(temp_str[i] - U'0');
          }
        }

        if (found_invalid_character) {
          number_value += fractional_part_value;

          if (negative_sign_found)
            number_value = -number_value;

          if (exponential_sign_found) {
            if (negative_exponent_sign_found)
              exponential_part_value = -exponential_part_value;

            if (abs(exponential_part_value) != 0)
              number_value *= powf(10.f, exponential_part_value);
          }
        }

        break;
    }
  }

  if (!found_invalid_character) {
    number_value += fractional_part_value;

    if (negative_sign_found)
      number_value = -number_value;

    if (exponential_sign_found && (base != 16)) {
      if (negative_exponent_sign_found)
        exponential_part_value = -exponential_part_value;

      if (abs(exponential_part_value) != 0)
        number_value *= powf(2.f, exponential_part_value);
    }
  }

  if (pos)
    *pos = i;

  return number_value;
}

double stod(const u32string& str,
            size_t* pos,
            int base,
            bool ignore_leading_white_space_characters) {
  double number_value{};

  auto negative_sign_found{false};
  double fractional_part_value{};
  auto fractional_part_found{false};
  int fractional_part_position_index{-1};

  auto exponential_sign_found{false};
  auto negative_exponent_sign_found{false};
  auto exponent_leading_zero_values{true};
  int exponential_part_value{};

  auto found_invalid_character{false};

  auto temp_str{str};

  if (ignore_leading_white_space_characters)
    temp_str = ltrim(str);

  if ((base == 2) &&
      ((temp_str.substr(0, 2) == U"0b") || (temp_str.substr(0, 2) == U"0B"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 2) && ((temp_str[0] == U'b') || (temp_str[0] == U'B'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 8) && ((temp_str.substr(0, 2) == U"0o") ||
                           (temp_str.substr(0, 2) == U"0O"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 8) && ((temp_str[0] == U'0') || (temp_str[0] == U'o') ||
                           (temp_str[0] == U'O'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 16) && ((temp_str.substr(0, 2) == U"0x") ||
                            (temp_str.substr(0, 2) == U"0X"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 16) && ((temp_str[0] == U'x') || (temp_str[0] == U'X'))) {
    temp_str.erase(cbegin(temp_str));
  }

  if (temp_str[0] == U'+') {
    temp_str.erase(cbegin(temp_str));
  }

  else if (temp_str[0] == U'-') {
    negative_sign_found = true;
    temp_str.erase(cbegin(temp_str));
  }

  if (temp_str[0] == U'.') {
    fractional_part_found = true;
    temp_str.erase(cbegin(temp_str));
  }

  if (pos)
    *pos = 0;

  if (!fractional_part_found && (temp_str[0] == U'0'))
    return number_value;

  if ((base != 16) && ((temp_str[0] == U'e') || (temp_str[0] == U'E'))) {
    if (fractional_part_found)
      return number_value;
    exponential_sign_found = true;
    temp_str.erase(cbegin(temp_str));
  }

  u32string::size_type i{0u};

  for (; (!found_invalid_character && (i < temp_str.size())); i++) {
    switch (base) {
      case 2:

        if (temp_str[i] == U'.') {
          if (!fractional_part_found) {
            fractional_part_found = true;
            fractional_part_value = 0;
            fractional_part_position_index = -1;
          } else {
            found_invalid_character = true;
          }
        }

        else if (!exponential_sign_found &&
                 ((temp_str[i] == U'e') || (temp_str[i] == U'E'))) {
          exponential_sign_found = true;
        }

        else if (exponential_sign_found && (temp_str[i] == U'+')) {
          if ((temp_str[i - 1] != U'e') && (temp_str[i - 1] != U'e'))
            found_invalid_character = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && (temp_str[i] == U'-')) {
          if ((temp_str[i - 1] != U'e') && (temp_str[i - 1] != U'e'))
            found_invalid_character = true;

          else
            negative_exponent_sign_found = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && exponent_leading_zero_values &&
                 (temp_str[i] == U'0')) {
          exponential_part_value = 0;
        }

        else if ((temp_str[i] < U'0') || (temp_str[i] > U'1')) {
          found_invalid_character = true;
        }

        else {
          if (exponential_sign_found) {
            exponent_leading_zero_values = false;
            exponential_part_value *= 2;
            exponential_part_value += static_cast<int>(temp_str[i] - U'0');
          } else if (fractional_part_found) {
            fractional_part_value +=
                static_cast<double>(static_cast<int>(temp_str[i] - U'0') *
                                    pow(2.f, fractional_part_position_index));
            fractional_part_position_index--;
          } else {
            number_value *= 2;
            number_value += static_cast<double>(temp_str[i] - U'0');
          }
        }

        if (found_invalid_character) {
          number_value += fractional_part_value;

          if (negative_sign_found)
            number_value = -number_value;

          if (exponential_sign_found) {
            if (negative_exponent_sign_found)
              exponential_part_value = -exponential_part_value;

            if (abs(exponential_part_value) != 0)
              number_value *= pow(2, exponential_part_value);
          }
        }

        break;

      case 8:

        if (temp_str[i] == U'.') {
          if (!fractional_part_found) {
            fractional_part_found = true;
            fractional_part_value = 0;
            fractional_part_position_index = -1;
          } else {
            found_invalid_character = true;
          }
        }

        else if (!exponential_sign_found &&
                 ((temp_str[i] == U'e') || (temp_str[i] == U'E'))) {
          exponential_sign_found = true;
        }

        else if (exponential_sign_found && (temp_str[i] == U'+')) {
          if ((temp_str[i - 1] != U'e') && (temp_str[i - 1] != U'e'))
            found_invalid_character = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && (temp_str[i] == U'-')) {
          if ((temp_str[i - 1] != U'e') && (temp_str[i - 1] != U'e'))
            found_invalid_character = true;

          else
            negative_exponent_sign_found = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && exponent_leading_zero_values &&
                 (temp_str[i] == U'0')) {
          exponential_part_value = 0;
        }

        else if ((temp_str[i] < U'0') || (temp_str[i] > U'7')) {
          found_invalid_character = true;
        }

        else {
          if (exponential_sign_found) {
            exponent_leading_zero_values = false;
            exponential_part_value *= 2;
            exponential_part_value += static_cast<int>(temp_str[i] - U'0');
          } else if (fractional_part_found) {
            fractional_part_value +=
                static_cast<double>(static_cast<int>(temp_str[i] - U'0') *
                                    pow(8.f, fractional_part_position_index));
            fractional_part_position_index--;
          } else {
            number_value *= 8;
            number_value += static_cast<double>(temp_str[i] - U'0');
          }
        }

        if (found_invalid_character) {
          number_value += fractional_part_value;

          if (negative_sign_found)
            number_value = -number_value;

          if (exponential_sign_found) {
            if (negative_exponent_sign_found)
              exponential_part_value = -exponential_part_value;

            if (abs(exponential_part_value) != 0)
              number_value *= pow(8, exponential_part_value);
          }
        }

        break;

      case 10:
        if (temp_str[i] == U'.') {
          if (!fractional_part_found) {
            fractional_part_found = true;
            fractional_part_value = 0;
            fractional_part_position_index = -1;
          } else {
            found_invalid_character = true;
          }
        }

        else if (!exponential_sign_found &&
                 ((temp_str[i] == U'e') || (temp_str[i] == U'E'))) {
          exponential_sign_found = true;
        }

        else if (exponential_sign_found && (temp_str[i] == U'+')) {
          if ((temp_str[i - 1] != U'e') && (temp_str[i - 1] != U'e'))
            found_invalid_character = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && (temp_str[i] == U'-')) {
          if ((temp_str[i - 1] != U'e') && (temp_str[i - 1] != U'e'))
            found_invalid_character = true;

          else
            negative_exponent_sign_found = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && exponent_leading_zero_values &&
                 (temp_str[i] == U'0')) {
          exponential_part_value = 0;
        }

        else if ((temp_str[i] < U'0') || (temp_str[i] > U'9')) {
          found_invalid_character = true;
        }

        else {
          if (exponential_sign_found) {
            exponent_leading_zero_values = false;
            exponential_part_value *= 10;
            exponential_part_value += static_cast<int>(temp_str[i] - U'0');
          } else if (fractional_part_found) {
            fractional_part_value +=
                static_cast<double>(static_cast<int>(temp_str[i] - U'0') *
                                    pow(10.f, fractional_part_position_index));
            fractional_part_position_index--;
          } else {
            number_value *= 10;
            number_value += static_cast<double>(temp_str[i] - U'0');
          }
        }

        if (found_invalid_character) {
          number_value += fractional_part_value;

          if (negative_sign_found)
            number_value = -number_value;

          if (exponential_sign_found) {
            if (negative_exponent_sign_found)
              exponential_part_value = -exponential_part_value;

            if (abs(exponential_part_value) != 0)
              number_value *= pow(10, exponential_part_value);
          }
        }

        break;

      case 16:
        if (temp_str[i] == U'.') {
          if (!fractional_part_found) {
            fractional_part_found = true;
            fractional_part_value = 0;
            fractional_part_position_index = -1;
          } else {
            found_invalid_character = true;
          }
        } else {
          if (fractional_part_found) {
            if (((temp_str[i] >= U'0') && (temp_str[i] <= U'9')) ||
                ((temp_str[i] >= U'A') && (temp_str[i] <= U'F'))

                || ((temp_str[i] >= U'a') && (temp_str[i] <= U'f'))) {
              number_value *= 16;

              if ((temp_str[i] >= U'0') && (temp_str[i] <= U'9')) {
                fractional_part_value += static_cast<double>(
                    static_cast<int>(temp_str[i] - U'0') *
                    pow(16.f, fractional_part_position_index));
              }

              else if ((temp_str[i] >= U'A') && (temp_str[i] <= U'F')) {
                fractional_part_value += static_cast<double>(
                    static_cast<int>(temp_str[i] - U'A') *
                    pow(16.f, fractional_part_position_index));
              }

              else if ((temp_str[i] >= U'a') && (temp_str[i] <= U'f')) {
                fractional_part_value += static_cast<double>(
                    static_cast<int>(temp_str[i] - U'a') *
                    pow(16.f, fractional_part_position_index));
              }

              fractional_part_position_index--;
            } else {
              found_invalid_character = true;
            }
          } else {
            if (((temp_str[i] >= U'0') && (temp_str[i] <= U'9')) ||
                ((temp_str[i] >= U'A') && (temp_str[i] <= U'F'))

                || ((temp_str[i] >= U'a') && (temp_str[i] <= U'f'))) {
              number_value *= 16;

              if ((temp_str[i] >= U'0') && (temp_str[i] <= U'9'))
                number_value += static_cast<double>(temp_str[i] - U'0');

              else if ((temp_str[i] >= U'A') && (temp_str[i] <= U'F'))
                number_value += static_cast<double>(10 + (temp_str[i] - U'A'));

              else if ((temp_str[i] >= U'a') && (temp_str[i] <= U'f'))
                number_value += static_cast<double>(10 + (temp_str[i] - U'a'));
            } else {
              found_invalid_character = true;
            }
          }
        }

        if (found_invalid_character) {
          number_value += fractional_part_value;

          if (negative_sign_found)
            number_value = -number_value;
        }

        break;

      default:
        if (temp_str[i] == U'.') {
          if (!fractional_part_found) {
            fractional_part_found = true;
            fractional_part_value = 0;
            fractional_part_position_index = -1;
          } else {
            found_invalid_character = true;
          }
        }

        else if (!exponential_sign_found &&
                 ((temp_str[i] == U'e') || (temp_str[i] == U'E'))) {
          exponential_sign_found = true;
        }

        else if (exponential_sign_found && (temp_str[i] == U'+')) {
          if ((temp_str[i - 1] != U'e') && (temp_str[i - 1] != U'e'))
            found_invalid_character = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && (temp_str[i] == U'-')) {
          if ((temp_str[i - 1] != U'e') && (temp_str[i - 1] != U'e'))
            found_invalid_character = true;

          else
            negative_exponent_sign_found = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && exponent_leading_zero_values &&
                 (temp_str[i] == U'0')) {
          exponential_part_value = 0;
        }

        else if ((temp_str[i] < U'0') || (temp_str[i] > U'9')) {
          found_invalid_character = true;
        }

        else {
          if (exponential_sign_found) {
            exponent_leading_zero_values = false;
            exponential_part_value *= 10;
            exponential_part_value += static_cast<int>(temp_str[i] - U'0');
          } else if (fractional_part_found) {
            fractional_part_value +=
                static_cast<double>(static_cast<int>(temp_str[i] - U'0') *
                                    pow(10.f, fractional_part_position_index));
            fractional_part_position_index--;
          } else {
            number_value *= 10;
            number_value += static_cast<double>(temp_str[i] - U'0');
          }
        }

        if (found_invalid_character) {
          number_value += fractional_part_value;

          if (negative_sign_found)
            number_value = -number_value;

          if (exponential_sign_found) {
            if (negative_exponent_sign_found)
              exponential_part_value = -exponential_part_value;

            if (abs(exponential_part_value) != 0)
              number_value *= pow(10, exponential_part_value);
          }
        }

        break;
    }
  }

  if (!found_invalid_character) {
    number_value += fractional_part_value;

    if (negative_sign_found)
      number_value = -number_value;

    if (exponential_sign_found && (base != 16)) {
      if (negative_exponent_sign_found)
        exponential_part_value = -exponential_part_value;

      if (abs(exponential_part_value) != 0)
        number_value *= pow(2, exponential_part_value);
    }
  }

  if (pos)
    *pos = i;

  return number_value;
}

long double stold(const u32string& str,
                  size_t* pos,
                  int base,
                  bool ignore_leading_white_space_characters) {
  long double number_value{};

  auto negative_sign_found{false};
  long double fractional_part_value{};
  auto fractional_part_found{false};
  int fractional_part_position_index{-1};

  auto exponential_sign_found{false};
  auto negative_exponent_sign_found{false};
  auto exponent_leading_zero_values{true};
  int exponential_part_value{};

  auto found_invalid_character{false};

  auto temp_str{str};

  if (ignore_leading_white_space_characters)
    temp_str = ltrim(str);

  if ((base == 2) &&
      ((temp_str.substr(0, 2) == U"0b") || (temp_str.substr(0, 2) == U"0B"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 2) && ((temp_str[0] == U'b') || (temp_str[0] == U'B'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 8) && ((temp_str.substr(0, 2) == U"0o") ||
                           (temp_str.substr(0, 2) == U"0O"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 8) && ((temp_str[0] == U'0') || (temp_str[0] == U'o') ||
                           (temp_str[0] == U'O'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 16) && ((temp_str.substr(0, 2) == U"0x") ||
                            (temp_str.substr(0, 2) == U"0X"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 16) && ((temp_str[0] == U'x') || (temp_str[0] == U'X'))) {
    temp_str.erase(cbegin(temp_str));
  }

  if (temp_str[0] == U'+') {
    temp_str.erase(cbegin(temp_str));
  }

  else if (temp_str[0] == U'-') {
    negative_sign_found = true;
    temp_str.erase(cbegin(temp_str));
  }

  if (temp_str[0] == U'.') {
    fractional_part_found = true;
    temp_str.erase(cbegin(temp_str));
  }

  if (pos)
    *pos = 0;

  if (!fractional_part_found && (temp_str[0] == U'0'))
    return number_value;

  if ((base != 16) && ((temp_str[0] == U'e') || (temp_str[0] == U'E'))) {
    if (fractional_part_found)
      return number_value;
    exponential_sign_found = true;
    temp_str.erase(cbegin(temp_str));
  }

  u32string::size_type i{0u};

  for (; (!found_invalid_character && (i < temp_str.size())); i++) {
    switch (base) {
      case 2:

        if (temp_str[i] == U'.') {
          if (!fractional_part_found) {
            fractional_part_found = true;
            fractional_part_value = 0;
            fractional_part_position_index = -1;
          } else {
            found_invalid_character = true;
          }
        }

        else if (!exponential_sign_found &&
                 ((temp_str[i] == U'e') || (temp_str[i] == U'E'))) {
          exponential_sign_found = true;
        }

        else if (exponential_sign_found && (temp_str[i] == U'+')) {
          if ((temp_str[i - 1] != U'e') && (temp_str[i - 1] != U'e'))
            found_invalid_character = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && (temp_str[i] == U'-')) {
          if ((temp_str[i - 1] != U'e') && (temp_str[i - 1] != U'e'))
            found_invalid_character = true;

          else
            negative_exponent_sign_found = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && exponent_leading_zero_values &&
                 (temp_str[i] == U'0')) {
          exponential_part_value = 0;
        }

        else if ((temp_str[i] < U'0') || (temp_str[i] > U'1')) {
          found_invalid_character = true;
        }

        else {
          if (exponential_sign_found) {
            exponent_leading_zero_values = false;
            exponential_part_value *= 2;
            exponential_part_value += static_cast<int>(temp_str[i] - U'0');
          } else if (fractional_part_found) {
            fractional_part_value += static_cast<long double>(
                static_cast<int>(temp_str[i] - U'0') *
                pow(2.f, fractional_part_position_index));
            fractional_part_position_index--;
          } else {
            number_value *= 2;
            number_value += static_cast<long double>(temp_str[i] - U'0');
          }
        }

        if (found_invalid_character) {
          number_value += fractional_part_value;

          if (negative_sign_found)
            number_value = -number_value;

          if (exponential_sign_found) {
            if (negative_exponent_sign_found)
              exponential_part_value = -exponential_part_value;

            if (abs(exponential_part_value) != 0)
              number_value *= powl(2, exponential_part_value);
          }
        }

        break;

      case 8:

        if (temp_str[i] == U'.') {
          if (!fractional_part_found) {
            fractional_part_found = true;
            fractional_part_value = 0;
            fractional_part_position_index = -1;
          } else {
            found_invalid_character = true;
          }
        }

        else if (!exponential_sign_found &&
                 ((temp_str[i] == U'e') || (temp_str[i] == U'E'))) {
          exponential_sign_found = true;
        }

        else if (exponential_sign_found && (temp_str[i] == U'+')) {
          if ((temp_str[i - 1] != U'e') && (temp_str[i - 1] != U'e'))
            found_invalid_character = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && (temp_str[i] == U'-')) {
          if ((temp_str[i - 1] != U'e') && (temp_str[i - 1] != U'e'))
            found_invalid_character = true;

          else
            negative_exponent_sign_found = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && exponent_leading_zero_values &&
                 (temp_str[i] == U'0')) {
          exponential_part_value = 0;
        }

        else if ((temp_str[i] < U'0') || (temp_str[i] > U'7')) {
          found_invalid_character = true;
        }

        else {
          if (exponential_sign_found) {
            exponent_leading_zero_values = false;
            exponential_part_value *= 2;
            exponential_part_value += static_cast<int>(temp_str[i] - U'0');
          } else if (fractional_part_found) {
            fractional_part_value += static_cast<long double>(
                static_cast<int>(temp_str[i] - U'0') *
                pow(8.f, fractional_part_position_index));
            fractional_part_position_index--;
          } else {
            number_value *= 8;
            number_value += static_cast<long double>(temp_str[i] - U'0');
          }
        }

        if (found_invalid_character) {
          number_value += fractional_part_value;

          if (negative_sign_found)
            number_value = -number_value;

          if (exponential_sign_found) {
            if (negative_exponent_sign_found)
              exponential_part_value = -exponential_part_value;

            if (abs(exponential_part_value) != 0)
              number_value *= powl(8, exponential_part_value);
          }
        }

        break;

      case 10:
        if (temp_str[i] == U'.') {
          if (!fractional_part_found) {
            fractional_part_found = true;
            fractional_part_value = 0;
            fractional_part_position_index = -1;
          } else {
            found_invalid_character = true;
          }
        }

        else if (!exponential_sign_found &&
                 ((temp_str[i] == U'e') || (temp_str[i] == U'E'))) {
          exponential_sign_found = true;
        }

        else if (exponential_sign_found && (temp_str[i] == U'+')) {
          if ((temp_str[i - 1] != U'e') && (temp_str[i - 1] != U'e'))
            found_invalid_character = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && (temp_str[i] == U'-')) {
          if ((temp_str[i - 1] != U'e') && (temp_str[i - 1] != U'e'))
            found_invalid_character = true;

          else
            negative_exponent_sign_found = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && exponent_leading_zero_values &&
                 (temp_str[i] == U'0')) {
          exponential_part_value = 0;
        }

        else if ((temp_str[i] < U'0') || (temp_str[i] > U'9')) {
          found_invalid_character = true;
        }

        else {
          if (exponential_sign_found) {
            exponent_leading_zero_values = false;
            exponential_part_value *= 10;
            exponential_part_value += static_cast<int>(temp_str[i] - U'0');
          } else if (fractional_part_found) {
            fractional_part_value += static_cast<long double>(
                static_cast<int>(temp_str[i] - U'0') *
                pow(10.f, fractional_part_position_index));
            fractional_part_position_index--;
          } else {
            number_value *= 10;
            number_value += static_cast<long double>(temp_str[i] - U'0');
          }
        }

        if (found_invalid_character) {
          number_value += fractional_part_value;

          if (negative_sign_found)
            number_value = -number_value;

          if (exponential_sign_found) {
            if (negative_exponent_sign_found)
              exponential_part_value = -exponential_part_value;

            if (abs(exponential_part_value) != 0)
              number_value *= powl(10, exponential_part_value);
          }
        }

        break;

      case 16:
        if (temp_str[i] == U'.') {
          if (!fractional_part_found) {
            fractional_part_found = true;
            fractional_part_value = 0;
            fractional_part_position_index = -1;
          } else {
            found_invalid_character = true;
          }
        } else {
          if (fractional_part_found) {
            if (((temp_str[i] >= U'0') && (temp_str[i] <= U'9')) ||
                ((temp_str[i] >= U'A') && (temp_str[i] <= U'F'))

                || ((temp_str[i] >= U'a') && (temp_str[i] <= U'f'))) {
              number_value *= 16;

              if ((temp_str[i] >= U'0') && (temp_str[i] <= U'9')) {
                fractional_part_value += static_cast<long double>(
                    static_cast<int>(temp_str[i] - U'0') *
                    pow(16.f, fractional_part_position_index));
              }

              else if ((temp_str[i] >= U'A') && (temp_str[i] <= U'F')) {
                fractional_part_value += static_cast<long double>(
                    static_cast<int>(temp_str[i] - U'A') *
                    pow(16.f, fractional_part_position_index));
              }

              else if ((temp_str[i] >= U'a') && (temp_str[i] <= U'f')) {
                fractional_part_value += static_cast<long double>(
                    static_cast<int>(temp_str[i] - U'a') *
                    pow(16.f, fractional_part_position_index));
              }

              fractional_part_position_index--;
            } else {
              found_invalid_character = true;
            }
          } else {
            if (((temp_str[i] >= U'0') && (temp_str[i] <= U'9')) ||
                ((temp_str[i] >= U'A') && (temp_str[i] <= U'F'))

                || ((temp_str[i] >= U'a') && (temp_str[i] <= U'f'))) {
              number_value *= 16;

              if ((temp_str[i] >= U'0') && (temp_str[i] <= U'9'))
                number_value += static_cast<long double>(temp_str[i] - U'0');

              else if ((temp_str[i] >= U'A') && (temp_str[i] <= U'F'))
                number_value +=
                    static_cast<long double>(10 + (temp_str[i] - U'A'));

              else if ((temp_str[i] >= U'a') && (temp_str[i] <= U'f'))
                number_value +=
                    static_cast<long double>(10 + (temp_str[i] - U'a'));
            } else {
              found_invalid_character = true;
            }
          }
        }

        if (found_invalid_character) {
          number_value += fractional_part_value;

          if (negative_sign_found)
            number_value = -number_value;
        }

        break;

      default:
        if (temp_str[i] == U'.') {
          if (!fractional_part_found) {
            fractional_part_found = true;
            fractional_part_value = 0;
            fractional_part_position_index = -1;
          } else {
            found_invalid_character = true;
          }
        }

        else if (!exponential_sign_found &&
                 ((temp_str[i] == U'e') || (temp_str[i] == U'E'))) {
          exponential_sign_found = true;
        }

        else if (exponential_sign_found && (temp_str[i] == U'+')) {
          if ((temp_str[i - 1] != U'e') && (temp_str[i - 1] != U'e'))
            found_invalid_character = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && (temp_str[i] == U'-')) {
          if ((temp_str[i - 1] != U'e') && (temp_str[i - 1] != U'e'))
            found_invalid_character = true;

          else
            negative_exponent_sign_found = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && exponent_leading_zero_values &&
                 (temp_str[i] == U'0')) {
          exponential_part_value = 0;
        }

        else if ((temp_str[i] < U'0') || (temp_str[i] > U'9')) {
          found_invalid_character = true;
        }

        else {
          if (exponential_sign_found) {
            exponent_leading_zero_values = false;
            exponential_part_value *= 10;
            exponential_part_value += static_cast<int>(temp_str[i] - U'0');
          } else if (fractional_part_found) {
            fractional_part_value += static_cast<long double>(
                static_cast<int>(temp_str[i] - U'0') *
                pow(10.f, fractional_part_position_index));
            fractional_part_position_index--;
          } else {
            number_value *= 10;
            number_value += static_cast<long double>(temp_str[i] - U'0');
          }
        }

        if (found_invalid_character) {
          number_value += fractional_part_value;

          if (negative_sign_found)
            number_value = -number_value;

          if (exponential_sign_found) {
            if (negative_exponent_sign_found)
              exponential_part_value = -exponential_part_value;

            if (abs(exponential_part_value) != 0)
              number_value *= powl(10, exponential_part_value);
          }
        }

        break;
    }
  }

  if (!found_invalid_character) {
    number_value += fractional_part_value;

    if (negative_sign_found)
      number_value = -number_value;

    if (exponential_sign_found && (base != 16)) {
      if (negative_exponent_sign_found)
        exponential_part_value = -exponential_part_value;

      if (abs(exponential_part_value) != 0)
        number_value *= powl(2, exponential_part_value);
    }
  }

  if (pos)
    *pos = i;

  return number_value;
}

}  // namespace stl::helper
