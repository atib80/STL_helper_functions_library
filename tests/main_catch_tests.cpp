#define CATCH_CONFIG_MAIN

#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <cstring>
#include <iterator>
#include <map>
#include <random>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "../include/catch.hpp"
#include "../include/stl_helper_functions.hpp"

using namespace std;
using namespace std::chrono;
using namespace std::string_literals;
using namespace stl::helper;

long long get_random_number(const long long lower_bound,
                            const long long upper_bound) {
  mt19937 rand_engine{static_cast<unsigned>(
      high_resolution_clock::now().time_since_epoch().count())};
  uniform_int_distribution<long long> num_distr{lower_bound, upper_bound};

  return num_distr(rand_engine);
}

template <typename T>
std::vector<T> generate_sequence_of_random_values(
    const T& low,
    const T& high,
    const size_t num_of_elements) {
  std::random_device rd{};
  std::mt19937 rand_engine{rd()};
  std::uniform_int_distribution<T> dist{low, high};

  std::vector<T> seq;
  seq.reserve(num_of_elements);

  for (size_t i{}; i < num_of_elements; ++i)
    seq.emplace_back(dist(rand_engine));

  return seq;
}
TEST_CASE("int say_slow(std::ostream&, const size_t, const char*, Args...)",
          "Testing correct work of global template function int say_slow(const "
          "size_t time_delay_in_ms, const char* format_string, Args... args)") {
  constexpr size_t buffer_size{256U};
  static char buffer[buffer_size];
  const char* printed_message = "The word 'apple' consists of 5 characters.\n";

  const auto length1 = strlen(printed_message);
  const auto length2 = len(printed_message);

  SNPRINTF(buffer, buffer_size, "The word '%s' consists of %d characters.\n",
           "apple", 5);
  const size_t formatted_string_length{len(buffer)};
  std::ostringstream oss{};
  const auto ret_val = say_slow(
      oss, 5U, "The word '%s' consists of %d characters.\n", "apple", 5);

  REQUIRE(length1 == length2);

  REQUIRE(length1 == formatted_string_length);
  REQUIRE(length1 == ret_val);
  REQUIRE(length1 == oss.str().length());

  REQUIRE(length2 == formatted_string_length);
  REQUIRE(length2 == ret_val);
  REQUIRE(length1 == oss.str().length());
}

TEST_CASE(
    "int say_slow(std::wostream&, const size_t, const wchar_t*, Args...)",
    "Testing correct work of global template function int say_slow(const "
    "size_t time_delay_in_ms, const wchar_t* format_string, Args... args)") {
  constexpr size_t buffer_size{256U};
  static wchar_t buffer[buffer_size];
  const wchar_t* printed_message =
      L"The word 'apple' consists of 5 characters.\n";

  const auto length1 = wcslen(printed_message);
  const auto length2 = len(printed_message);

  SNWPRINTF(buffer, buffer_size, L"The word '%ls' consists of %d characters.\n",
            L"apple", 5);
  const size_t formatted_string_length{len(buffer)};

  std::wostringstream woss{};

  const auto ret_val = say_slow(
      woss, 5U, L"The word '%ls' consists of %d characters.\n", L"apple", 5);

  REQUIRE(length1 == length2);

  REQUIRE(length1 == formatted_string_length);
  REQUIRE(length1 == ret_val);
  REQUIRE(length1 == woss.str().length());

  REQUIRE(length2 == formatted_string_length);
  REQUIRE(length2 == ret_val);
  REQUIRE(length2 == woss.str().length());
}

TEST_CASE("int say(std::ostream&, const char* format_string, Args... args)",
          "Testing correct work of global template function int say(const "
          "char* format_string, Args... args)") {
  constexpr size_t buffer_size{256U};
  static char buffer[buffer_size];
  const char* printed_message = "The word 'apple' consists of 5 characters.\n";
  const auto length1 = strlen(printed_message);
  const auto length2 = len(printed_message);

  SNPRINTF(buffer, buffer_size, "The word '%s' consists of %d characters.\n",
           "apple", 5);
  const size_t formatted_string_length{len(buffer)};

  std::ostringstream oss{};
  const auto ret_val =
      say(oss, "The word '%s' consists of %d characters.\n", "apple", 5);

  REQUIRE(length1 == length2);

  REQUIRE(length1 == formatted_string_length);
  REQUIRE(length1 == ret_val);
  REQUIRE(length1 == oss.str().length());

  REQUIRE(length2 == formatted_string_length);
  REQUIRE(length2 == ret_val);
  REQUIRE(length2 == oss.str().length());
}

TEST_CASE("int say(std::wostream&, const wchar_t* format_string, Args... args)",
          "Testing correct work of global template function int say(const "
          "wchar_t* format_string, Args... args)") {
  constexpr size_t buffer_size{256U};
  static wchar_t buffer[buffer_size];
  const wchar_t* printed_message =
      L"The word 'apple' consists of 5 characters.\n";
  const auto length1 = wcslen(printed_message);
  const auto length2 = len(printed_message);

  SNWPRINTF(buffer, buffer_size, L"The word '%ls' consists of %d characters.\n",
            L"apple", 5);
  const size_t formatted_string_length{len(buffer)};
  std::wostringstream woss{};
  const auto ret_val =
      say(woss, L"The word '%ls' consists of %d characters.\n", L"apple", 5);

  REQUIRE(length1 == formatted_string_length);
  REQUIRE(length1 == ret_val);
  REQUIRE(length1 == woss.str().length());

  REQUIRE(length2 == formatted_string_length);
  REQUIRE(length2 == ret_val);
  REQUIRE(length2 == woss.str().length());
}

TEST_CASE("is_non_const_char_array_type<T>",
          "Testing is_non_const_char_array_type<T> class template") {
  REQUIRE(is_non_const_char_array_type<char[10]>::value);
  REQUIRE(is_non_const_char_array_type<wchar_t[10]>::value);
  REQUIRE(is_non_const_char_array_type<char16_t[10]>::value);
  REQUIRE(is_non_const_char_array_type<char32_t[10]>::value);
  REQUIRE(is_non_const_char_array_type_v<char[10]>);
  REQUIRE(is_non_const_char_array_type_v<wchar_t[10]>);
  REQUIRE(is_non_const_char_array_type_v<char16_t[10]>);
  REQUIRE(is_non_const_char_array_type_v<char32_t[10]>);

  REQUIRE(!is_non_const_char_array_type<const char[10]>::value);
  REQUIRE(!is_non_const_char_array_type<const wchar_t[10]>::value);
  REQUIRE(!is_non_const_char_array_type<const char16_t[10]>::value);
  REQUIRE(!is_non_const_char_array_type<const char32_t[10]>::value);
  REQUIRE(!is_non_const_char_array_type_v<const char[10]>);
  REQUIRE(!is_non_const_char_array_type_v<const wchar_t[10]>);
  REQUIRE(!is_non_const_char_array_type_v<const char16_t[10]>);
  REQUIRE(!is_non_const_char_array_type_v<const char32_t[10]>);
}

TEST_CASE("is_const_char_array_type<T>",
          "Testing is_const_char_array_type<T> class template") {
  REQUIRE(is_const_char_array_type<const char[10]>::value);
  REQUIRE(is_const_char_array_type<const wchar_t[10]>::value);
  REQUIRE(is_const_char_array_type<const char16_t[10]>::value);
  REQUIRE(is_const_char_array_type<const char32_t[10]>::value);
  REQUIRE(is_const_char_array_type_v<const char[10]>);
  REQUIRE(is_const_char_array_type_v<const wchar_t[10]>);
  REQUIRE(is_const_char_array_type_v<const char16_t[10]>);
  REQUIRE(is_const_char_array_type_v<const char32_t[10]>);

  REQUIRE(!is_const_char_array_type<char[10]>::value);
  REQUIRE(!is_const_char_array_type<wchar_t[10]>::value);
  REQUIRE(!is_const_char_array_type<char16_t[10]>::value);
  REQUIRE(!is_const_char_array_type<char32_t[10]>::value);
  REQUIRE(!is_const_char_array_type_v<char[10]>);
  REQUIRE(!is_const_char_array_type_v<wchar_t[10]>);
  REQUIRE(!is_const_char_array_type_v<char16_t[10]>);
  REQUIRE(!is_const_char_array_type_v<char32_t[10]>);
}

TEST_CASE(
    "size_t len(T src, const size_t max_allowed_string_length = "
    "max_string_length)",
    "Testing global function len)") {
  const char ch1{'a'};
  const wchar_t ch2{L'A'};
  const char16_t ch3{u'b'};
  const char32_t ch4{U'B'};

  REQUIRE(len(ch1) == 1U);
  REQUIRE(len(ch2) == 1U);
  REQUIRE(len(ch3) == 1U);
  REQUIRE(len(ch4) == 1U);

  REQUIRE(len('a') == 1U);
  REQUIRE(len('b') == 1U);
  REQUIRE(len('c') == 1U);
  REQUIRE(len('d') == 1U);

  REQUIRE(len("Hello") == 5U);
  REQUIRE(len(L"Hello") == 5U);
  REQUIRE(len(u"Hello") == 5U);
  REQUIRE(len(U"Hello") == 5U);

  const char* src1 = "Hello World!\n";
  REQUIRE(len(src1) == strlen(src1));

  char char_buffer[]{"Hello World!\n"};
  REQUIRE(len(char_buffer) == 13);

  array<char, len("Hello World!\n") + 1> char_array{"Hello World!\n"};
  REQUIRE(len(char_array) == 13);

  const wchar_t* src2 = L"\tHello there, my friend!\n";
  REQUIRE(len(src2) == wcslen(src2));

  const char16_t* src3 = u"\tHello there, my friend!\n";
  u16string src3_str{src3};
  REQUIRE(len(src3) == src3_str.length());

  const char32_t* src4 = U"\tHello there, my friend!\n";
  u32string src4_str{src4};
  REQUIRE(len(src4) == src4_str.length());

  string src5{"Hello World!\n"};
  REQUIRE(len(src5) == src5.length());

  wstring src6{L"\tHello there, my friend!\n"};
  REQUIRE(len(src6) == src6.length());

  u16string src7{u"Hello World!\n"};
  REQUIRE(len(src7) == src7.length());

  u32string src8{U"\tHello there, my friend!\n"};
  REQUIRE(len(src8) == src8.length());
}

TEST_CASE("bool trim_in_place(CharPointerType mutable_char_buffer)",
          "Testing global function template bool trim_in_place(CharPointerType "
          "mutable_char_buffer)") {
  char char_buffer[64] = "\t Hello World!\t \n";
  const char* char_str = "Hello World!";

  REQUIRE(trim_in_place(char_buffer));

  REQUIRE(0 == strcmp(char_buffer, char_str));
  REQUIRE(0 == str_compare(char_buffer, char_str));

  wchar_t wchar_t_buffer[64] = L" \t Hello World!\t \n";
  const wchar_t* wchar_t_str = L"Hello World!";

  REQUIRE(trim_in_place(wchar_t_buffer));

  REQUIRE(0 == wcscmp(wchar_t_buffer, wchar_t_str));
  REQUIRE(0 == str_compare(wchar_t_buffer, wchar_t_str));

  char16_t char16_t_buffer[64] = u" \t Hello World!\t \n";
  const char16_t* char16_t_str = u"Hello World!";

  REQUIRE(trim_in_place(char16_t_buffer));

  u16string src_u16string{char16_t_buffer};
  u16string dst_u16string{char16_t_str};

  REQUIRE(src_u16string == dst_u16string);
  REQUIRE(0 == str_compare(char16_t_buffer, char16_t_str));

  char32_t char32_t_buffer[64] = U" \t Hello World!\t \n";
  const char32_t* char32_t_str_dst = U"Hello World!";

  REQUIRE(trim_in_place(char32_t_buffer));

  u32string src_u32string{char32_t_buffer};
  u32string dst_u32string{char32_t_str_dst};

  REQUIRE(src_u32string == dst_u32string);
  REQUIRE(0 == str_compare(char32_t_buffer, char32_t_str_dst));
}

TEST_CASE("bool ltrim_in_place(CharPointerType mutable_char_buffer)",
          "Testing global function template bool "
          "ltrim_in_place(CharPointerType mutable_char_buffer)") {
  char char_buffer[64] = "\t Hello World!";
  const char* char_str = "Hello World!";

  REQUIRE(ltrim_in_place(char_buffer));

  REQUIRE(0 == strcmp(char_buffer, char_str));
  REQUIRE(0 == str_compare(char_buffer, char_str));

  wchar_t wchar_t_buffer[64] = L" \t Hello World!";
  const wchar_t* wchar_t_str = L"Hello World!";

  REQUIRE(ltrim_in_place(wchar_t_buffer));

  REQUIRE(0 == wcscmp(wchar_t_buffer, wchar_t_str));
  REQUIRE(0 == str_compare(wchar_t_buffer, wchar_t_str));

  char16_t char16_t_buffer[64] = u" \t Hello World!";
  const char16_t* char16_t_str = u"Hello World!";

  REQUIRE(ltrim_in_place(char16_t_buffer));

  u16string src_u16string{char16_t_buffer};
  u16string dst_u16string{char16_t_str};

  REQUIRE(src_u16string == dst_u16string);
  REQUIRE(0 == str_compare(char16_t_buffer, char16_t_str));

  char32_t char32_t_buffer[64] = U" \t Hello World!";
  const char32_t* char32_t_str_dst = U"Hello World!";

  REQUIRE(ltrim_in_place(char32_t_buffer));

  u32string src_u32string{char32_t_buffer};
  u32string dst_u32string{char32_t_str_dst};

  REQUIRE(src_u32string == dst_u32string);
  REQUIRE(0 == str_compare(char32_t_buffer, char32_t_str_dst));
}

TEST_CASE("bool rtrim_in_place(CharPointerType mutable_char_buffer)",
          "Testing global function template bool "
          "rtrim_in_place(CharPointerType mutable_char_buffer)") {
  char char_buffer[64] = "Hello World!\t\n";
  const char* char_str = "Hello World!";

  REQUIRE(rtrim_in_place(char_buffer));

  REQUIRE(0 == strcmp(char_buffer, char_str));
  REQUIRE(0 == str_compare(char_buffer, char_str));

  wchar_t wchar_t_buffer[64] = L"Hello World!\t\n";
  const wchar_t* wchar_t_str = L"Hello World!";

  REQUIRE(rtrim_in_place(wchar_t_buffer));

  REQUIRE(wcscmp(wchar_t_buffer, wchar_t_str) == 0);
  REQUIRE(0 == str_compare(wchar_t_buffer, wchar_t_str));

  char16_t char16_t_buffer[64] = u"Hello World!\t\n";
  const char16_t* char16_t_str = u"Hello World!";

  REQUIRE(rtrim_in_place(char16_t_buffer));

  u16string src_u16string{char16_t_buffer};
  u16string dst_u16string{char16_t_str};

  REQUIRE(src_u16string == dst_u16string);
  REQUIRE(0 == str_compare(char16_t_buffer, char16_t_str));

  char32_t char32_t_buffer[64] = U"Hello World!\t\n";
  const char32_t* char32_t_str_dst = U"Hello World!";

  REQUIRE(rtrim_in_place(char32_t_buffer));

  u32string src_u32string{char32_t_buffer};
  u32string dst_u32string{char32_t_str_dst};

  REQUIRE(src_u32string == dst_u32string);
  REQUIRE(0 == str_compare(char32_t_buffer, char32_t_str_dst));
}

TEST_CASE("auto trim(ConstCharPointerType src)",
          "Testing global function auto trim(ConstCharPointerType src)") {
  const char* src_char = " \t Hello World!\t \n";
  const string src_string{" \t Hello World!\t \n"};
  const string dst_string{"Hello World!"};

  string output_string{trim(src_char)};

  REQUIRE(output_string == dst_string);

  output_string = trim(src_string);

  REQUIRE(output_string == dst_string);

  REQUIRE(dst_string == trim(" \t Hello World!\t \n"));

  const wchar_t* src_wchar_t = L" \t Hello World!\t \n";
  const wstring src_wstring{L" \t Hello World!\t \n"};
  const wstring dst_wstring{L"Hello World!"};

  wstring output_wstring{trim(src_wchar_t)};

  REQUIRE(output_wstring == dst_wstring);

  output_wstring = trim(src_wstring);

  REQUIRE(output_wstring == dst_wstring);
  REQUIRE(dst_wstring == trim(L" \t Hello World!\t \n"));

  const char16_t* src_char16_t = u" \t Hello World!\t \n";
  const u16string src_u16string{u" \t Hello World!\t \n"};
  const u16string dst_u16string{u"Hello World!"};

  u16string output_u16string{trim(src_char16_t)};

  REQUIRE(output_u16string == dst_u16string);

  output_u16string = trim(src_u16string);

  REQUIRE(output_u16string == dst_u16string);
  REQUIRE(dst_u16string == trim(u" \t Hello World!\t \n"));

  const char32_t* src_char32_t = U" \t Hello World!\t \n";
  const u32string src_u32string{U" \t Hello World!\t \n"};
  const u32string dst_u32string{U"Hello World!"};

  u32string output_u32string{trim(src_char32_t)};

  REQUIRE(output_u32string == dst_u32string);

  output_u32string = trim(src_u32string);

  REQUIRE(output_u32string == dst_u32string);
  REQUIRE(dst_u32string == trim(U" \t Hello World!\t \n"));
}

TEST_CASE("auto ltrim(ConstCharPointerType src)",
          "Testing global function auto ltrim(ConstCharPointerType src)") {
  const char* src_char = " \t Hello World!";
  const string src_string{" \t Hello World!"};
  const string dst_string{"Hello World!"};

  string output_string{ltrim(src_char)};

  REQUIRE(output_string == dst_string);

  output_string = ltrim(src_string);

  REQUIRE(output_string == dst_string);
  REQUIRE(dst_string == ltrim(" \t Hello World!"));

  const wchar_t* src_wchar_t = L" \t Hello World!";
  const wstring src_wstring{L" \t Hello World!"};
  const wstring dst_wstring{L"Hello World!"};

  wstring output_wstring{ltrim(src_wchar_t)};

  REQUIRE(output_wstring == dst_wstring);

  output_wstring = ltrim(src_wstring);

  REQUIRE(output_wstring == dst_wstring);
  REQUIRE(dst_wstring == ltrim(L" \t Hello World!"));

  const char16_t* src_char16_t = u" \t Hello World!";
  const u16string src_u16string{u" \t Hello World!"};
  const u16string dst_u16string{u"Hello World!"};

  u16string output_u16string{ltrim(src_char16_t)};

  REQUIRE(output_u16string == dst_u16string);

  output_u16string = ltrim(src_u16string);

  REQUIRE(output_u16string == dst_u16string);
  REQUIRE(dst_u16string == ltrim(u" \t Hello World!"));

  const char32_t* src_char32_t = U" \t Hello World!";
  const u32string src_u32string{U" \t Hello World!"};
  const u32string dst_u32string{U"Hello World!"};

  u32string output_u32string{ltrim(src_char32_t)};

  REQUIRE(output_u32string == dst_u32string);

  output_u32string = ltrim(src_u32string);

  REQUIRE(output_u32string == dst_u32string);
  REQUIRE(dst_u32string == ltrim(U" \t Hello World!"));
}

TEST_CASE("auto rtrim(ConstCharPointerType src)",
          "Testing global function auto rtrim(ConstCharPointerType src)") {
  const char* src_char = "Hello World!\t \n";
  const string src_string{"Hello World!\t \n"};
  const string dst_string{"Hello World!"};

  string output_string{rtrim(src_char)};

  REQUIRE(output_string == dst_string);

  output_string = rtrim(src_string);

  REQUIRE(output_string == dst_string);
  REQUIRE(dst_string == rtrim("Hello World!\t \n"));

  const wchar_t* src_wchar_t = L"Hello World!\t \n";
  const wstring src_wstring{L"Hello World!\t \n"};
  const wstring dst_wstring{L"Hello World!"};

  wstring output_wstring{rtrim(src_wchar_t)};

  REQUIRE(output_wstring == dst_wstring);

  output_wstring = rtrim(src_wstring);

  REQUIRE(output_wstring == dst_wstring);
  REQUIRE(dst_wstring == rtrim(L"Hello World!\t \n"));

  const char16_t* src_char16_t = u"Hello World!\t \n";
  const u16string src_u16string{u"Hello World!\t \n"};
  const u16string dst_u16string{u"Hello World!"};

  u16string output_u16string{rtrim(src_char16_t)};

  REQUIRE(output_u16string == dst_u16string);

  output_u16string = rtrim(src_u16string);

  REQUIRE(output_u16string == dst_u16string);
  REQUIRE(dst_u16string == rtrim(u"Hello World!\t \n"));

  const char32_t* src_char32_t = U"Hello World!\t \n";
  const u32string src_u32string{U"Hello World!\t \n"};
  const u32string dst_u32string{U"Hello World!"};

  u32string output_u32string{rtrim(src_char32_t)};

  REQUIRE(output_u32string == dst_u32string);

  output_u32string = rtrim(src_u32string);

  REQUIRE(output_u32string == dst_u32string);
  REQUIRE(dst_u32string == rtrim(U"Hello World!\t \n"));
}

// ==========================================================================
// Test cases for trim_in_place, ltrim_in_place, rtrim_in_place, trim, ltrim,
// accepting C++ string types as input
// ==========================================================================

TEST_CASE(
    "bool trim_in_place(T& src, const "
    "add_const_pointer_to_char_type_t<get_char_type_t<T>> chars_to_trim = "
    "default_whitespace_chars_v<get_char_type_t<T>>") {
  string input1{"\t Hello World!\t \n"};
  const string expected_input1{"Hello World!"};

  REQUIRE(trim_in_place(input1));
  REQUIRE(expected_input1 == input1);

  wstring input2{L" \t Hello World!\t \n"};
  const wstring expected_input2{L"Hello World!"};

  REQUIRE(trim_in_place(input2));
  REQUIRE(expected_input2 == input2);

  u16string input3{u" \t Hello World!\t \n"};
  const u16string expected_input3{u"Hello World!"};

  REQUIRE(trim_in_place(input3));
  REQUIRE(expected_input3 == input3);

  u32string input4{U" \t Hello World!\t \n"};
  const u32string expected_input4{U"Hello World!"};

  REQUIRE(trim_in_place(input4));
  REQUIRE(expected_input4 == input4);
}

TEST_CASE(
    "bool ltrim_in_place(T& src,\
  const add_const_pointer_to_char_type_t<get_char_type_t<T>> chars_to_trim =\
  default_whitespace_chars_v<get_char_type_t<T>>") {
  string input1{"\t Hello World!"};
  const string expected_input1{"Hello World!"};

  REQUIRE(trim_in_place(input1));
  REQUIRE(expected_input1 == input1);

  wstring input2{L" \t Hello World!"};
  const wstring expected_input2{L"Hello World!"};

  REQUIRE(trim_in_place(input2));
  REQUIRE(expected_input2 == input2);

  u16string input3{u" \t Hello World!"};
  const u16string expected_input3{u"Hello World!"};

  REQUIRE(trim_in_place(input3));
  REQUIRE(expected_input3 == input3);

  u32string input4{U" \t Hello World!"};
  const u32string expected_input4{U"Hello World!"};

  REQUIRE(trim_in_place(input4));
  REQUIRE(expected_input4 == input4);
}

TEST_CASE(
    "bool rtrim_in_place(T src, "
    "add_const_pointer_to_char_type_t<get_char_type_t<T>> chars_to_trim = "
    "default_whitespace_chars_v<get_char_type_t<T>>") {
  string input1{"Hello World!\t \n"};
  const string expected_input1{"Hello World!"};

  REQUIRE(trim_in_place(input1));
  REQUIRE(expected_input1 == input1);

  wstring input2{L"Hello World!\t \n"};
  const wstring expected_input2{L"Hello World!"};

  REQUIRE(trim_in_place(input2));
  REQUIRE(expected_input2 == input2);

  u16string input3{u"Hello World!\t \n"};
  const u16string expected_input3{u"Hello World!"};

  REQUIRE(trim_in_place(input3));
  REQUIRE(expected_input3 == input3);

  u32string input4{U"Hello World!\t \n"};
  const u32string expected_input4{U"Hello World!"};

  REQUIRE(trim_in_place(input4));
  REQUIRE(expected_input4 == input4);
}

TEST_CASE(
    "std::basic_string<get_char_type_t<T>> trim(const T& src, "
    "add_const_pointer_to_char_type_t<get_char_type_t<T>> chars_to_trim = "
    "default_whitespace_chars_v<get_char_type_t<T>>") {
  const char* src_char = " \t Hello World!\t \n";
  const string src_string{" \t Hello World!\t \n"};
  const string dst_string{"Hello World!"};

  string output_string{trim(src_char)};

  REQUIRE(output_string == dst_string);

  output_string = trim(src_string);

  REQUIRE(output_string == dst_string);

  REQUIRE(dst_string == trim(" \t Hello World!\t \n"));

  const wchar_t* src_wchar_t = L" \t Hello World!\t \n";
  const wstring src_wstring{L" \t Hello World!\t \n"};
  const wstring dst_wstring{L"Hello World!"};

  wstring output_wstring{trim(src_wchar_t)};

  REQUIRE(output_wstring == dst_wstring);

  output_wstring = trim(src_wstring);

  REQUIRE(output_wstring == dst_wstring);
  REQUIRE(dst_wstring == trim(L" \t Hello World!\t \n"));

  const char16_t* src_char16_t = u" \t Hello World!\t \n";
  const u16string src_u16string{u" \t Hello World!\t \n"};
  const u16string dst_u16string{u"Hello World!"};

  u16string output_u16string{trim(src_char16_t)};

  REQUIRE(output_u16string == dst_u16string);

  output_u16string = trim(src_u16string);

  REQUIRE(output_u16string == dst_u16string);
  REQUIRE(dst_u16string == trim(u" \t Hello World!\t \n"));

  const char32_t* src_char32_t = U" \t Hello World!\t \n";
  const u32string src_u32string{U" \t Hello World!\t \n"};
  const u32string dst_u32string{U"Hello World!"};

  u32string output_u32string{trim(src_char32_t)};

  REQUIRE(output_u32string == dst_u32string);

  output_u32string = trim(src_u32string);

  REQUIRE(output_u32string == dst_u32string);
  REQUIRE(dst_u32string == trim(U" \t Hello World!\t \n"));
}

TEST_CASE(
    "std::basic_string<get_char_type_t<T>> ltrim(const T& src, "
    "add_const_pointer_to_char_type_t<get_char_type_t<T>> chars_to_trim = "
    "default_whitespace_chars_v<get_char_type_t<T>>)") {
  const char* src_char = " \t Hello World!";
  const string src_string{" \t Hello World!"};
  const string dst_string{"Hello World!"};

  string output_string{ltrim(src_char)};

  REQUIRE(output_string == dst_string);

  output_string = ltrim(src_string);

  REQUIRE(output_string == dst_string);
  REQUIRE(dst_string == ltrim(" \t Hello World!"));

  const wchar_t* src_wchar_t = L" \t Hello World!";
  const wstring src_wstring{L" \t Hello World!"};
  const wstring dst_wstring{L"Hello World!"};

  wstring output_wstring{ltrim(src_wchar_t)};

  REQUIRE(output_wstring == dst_wstring);

  output_wstring = ltrim(src_wstring);

  REQUIRE(output_wstring == dst_wstring);
  REQUIRE(dst_wstring == ltrim(L" \t Hello World!"));

  const char16_t* src_char16_t = u" \t Hello World!";
  const u16string src_u16string{u" \t Hello World!"};
  const u16string dst_u16string{u"Hello World!"};

  u16string output_u16string{ltrim(src_char16_t)};

  REQUIRE(output_u16string == dst_u16string);

  output_u16string = ltrim(src_u16string);

  REQUIRE(output_u16string == dst_u16string);
  REQUIRE(dst_u16string == ltrim(u" \t Hello World!"));

  const char32_t* src_char32_t = U" \t Hello World!";
  const u32string src_u32string{U" \t Hello World!"};
  const u32string dst_u32string{U"Hello World!"};

  u32string output_u32string{ltrim(src_char32_t)};

  REQUIRE(output_u32string == dst_u32string);

  output_u32string = ltrim(src_u32string);

  REQUIRE(output_u32string == dst_u32string);
  REQUIRE(dst_u32string == ltrim(U" \t Hello World!"));
}

TEST_CASE(
    "std::basic_string<get_char_type_t<T>> rtrim(const T& src, "
    "add_const_pointer_to_char_type_t<typename T::value_type> chars_to_trim = "
    "default_whitespace_chars_v<typename T::value_type>)") {
  const char* src_char = "Hello World!\t \n";
  const string src_string{"Hello World!\t \n"};
  const string dst_string{"Hello World!"};

  string output_string{rtrim(src_char)};

  REQUIRE(output_string == dst_string);

  output_string = rtrim(src_string);

  REQUIRE(output_string == dst_string);
  REQUIRE(dst_string == rtrim("Hello World!\t \n"));

  const wchar_t* src_wchar_t = L"Hello World!\t \n";
  const wstring src_wstring{L"Hello World!\t \n"};
  const wstring dst_wstring{L"Hello World!"};

  wstring output_wstring{rtrim(src_wchar_t)};

  REQUIRE(output_wstring == dst_wstring);

  output_wstring = rtrim(src_wstring);

  REQUIRE(output_wstring == dst_wstring);
  REQUIRE(dst_wstring == rtrim(L"Hello World!\t \n"));

  const char16_t* src_char16_t = u"Hello World!\t \n";
  const u16string src_u16string{u"Hello World!\t \n"};
  const u16string dst_u16string{u"Hello World!"};

  u16string output_u16string{rtrim(src_char16_t)};

  REQUIRE(output_u16string == dst_u16string);

  output_u16string = rtrim(src_u16string);

  REQUIRE(output_u16string == dst_u16string);
  REQUIRE(dst_u16string == rtrim(u"Hello World!\t \n"));

  const char32_t* src_char32_t = U"Hello World!\t \n";
  const u32string src_u32string{U"Hello World!\t \n"};
  const u32string dst_u32string{U"Hello World!"};

  u32string output_u32string{rtrim(src_char32_t)};

  REQUIRE(output_u32string == dst_u32string);

  output_u32string = rtrim(src_u32string);

  REQUIRE(output_u32string == dst_u32string);
  REQUIRE(dst_u32string == rtrim(U"Hello World!\t \n"));
}

// **************************************************************************

// TEST_CASE("int u16_strcmp(const char16_t* str1, const char16_t* str2)",
//  "Testing global function int u16_strcmp(const char16_t* str1, const
// char16_t* str2)")
//{
//
//  const char16_t* str1 = u"apple";
//  const char16_t* str2 = u"apple";
//
//  REQUIRE(str_compare(str1, str2) == 0);
//
//  REQUIRE(str_compare(u16string(u"apple"), u16string(u"banana")) < 0);
//}
//
// TEST_CASE("int u32_strcmp(const char32_t* str1, const char32_t* str2)",
//  "Testing global function int u32_strcmp(const char32_t* str1, const
// char32_t* str2)")
//{
//  REQUIRE(str_compare(U"apple", U"apple") == 0);
//
//  REQUIRE(str_compare(U"apple", U"banana") < 0);
//}

// TEST_CASE("int u16_strncmp(const char16_t* str1, const char16_t* str2, size_t
// number_of_characters_to_compare)",   "Testing global function int
// u16_strncmp(const char16_t* str1, const char16_t* str2, size_t
// number_of_characters_to_compare)"
//)
//{
//  REQUIRE(str_compare_n(u"apple", u"appLE", 3) == 0);
//
//  REQUIRE(str_compare_n(u"apple", u"banana", 3) < 0);
//}
//
// TEST_CASE("int u32_strncmp(const char32_t* str1, const char32_t* str2, size_t
// number_of_characters_to_compare)",   "Testing global function int
// u32_strncmp(const char32_t* str1, const char32_t* str2, size_t
// number_of_characters_to_compare)"
//)
//{
//  REQUIRE(str_compare_n(U"apple", U"appLE", 3) == 0);
//
//  REQUIRE(str_compare_n(U"apple", U"banana", 3) < 0);
//}
//
// TEST_CASE("int u16_stricmp(const char16_t* str1, const char16_t* str2, const
// std::locale& loc = std::locale{})",  "Testing global function int
// u16_stricmp(const char16_t* str1, const char16_t* str2, const std::locale&
// loc = std::locale{})"
//)
//{
//  REQUIRE(str_compare_i(u"apple", u"apple") == 0);
//
//  REQUIRE(str_compare_i(u"apple", u"banana") < 0);
//}
//
// TEST_CASE("int u32_stricmp(const char32_t* str1, const char32_t* str2, const
// std::locale& loc = std::locale{})",  "Testing global function int
// u32_stricmp(const char32_t* str1, const char32_t* str2, const std::locale&
// loc = std::locale{})"
//)
//{
//  REQUIRE(str_compare_i(U"apple", U"apple") == 0);
//
//  REQUIRE(str_compare_i(U"apple", U"banana") < 0);
//}
//
// TEST_CASE(
//  "int u16_strnicmp(const char16_t* str1, const char16_t* str2, size_t
// number_of_characters_to_compare, const std::locale& loc = std::locale{})"
//  ,
//  "Testing global function int u16_strnicmp(const char16_t* str1, const
// char16_t* str2, size_t number_of_characters_to_compare, const std::locale&
// loc = std::locale{})"
//)
//{
//  REQUIRE(str_compare_n_i(u"apple", u"apple", 3) == 0);
//
//  REQUIRE(str_compare_n_i(u"apple", u"banana", 3) < 0);
//}
//
// TEST_CASE(
//  "int u32_strnicmp(const char32_t* str1, const char32_t* str2, size_t
// number_of_characters_to_compare, const std::locale& loc = std::locale{})"
//  ,
//  "Testing global function int u32_strnicmp(const char32_t* str1, const
// char32_t* str2, size_t number_of_characters_to_compare, const std::locale&
// loc = std::locale{})"
//)
//{
//  REQUIRE(str_compare_n_i(U"apple", U"apple", 3) == 0);
//
//  REQUIRE(str_compare_n_i(U"apple", U"banana", 3) < 0);
//}

/*
TEST_CASE("char16_t* u16_strcpy(char16_t* dst, const size_t
dst_capacity_in_number_of_characters, const char16_t* src)", "Testing global
function char16_t* u16_strcpy(char16_t* dst, const size_t
dst_capacity_in_number_of_characters, const char16_t* src)"
)
{
  char16_t src[128];

  char16_t dst[64] = u"\tHello World!\n";

  REQUIRE(trim(dst));

  REQUIRE(str_copy(src, sizeof(src)/sizeof(src[0]), dst) !=
nullptr);

  REQUIRE(str_compare(src, u"Hello World!") == 0);
}

TEST_CASE("char32_t* u32_strcpy(char32_t* dst, const size_t
dst_capacity_in_number_of_characters, const char32_t* src)", "Testing global
function char32_t* u32_strcpy(char32_t* dst, const size_t
dst_capacity_in_number_of_characters, const char32_t* src)"
)
{
  char32_t src[128];

  char32_t dst[64] = U"\tHello World!\n";

  REQUIRE(trim(dst));

  REQUIRE(u32_strcpy(src, sizeof(src) / sizeof(src[0]), dst) !=
nullptr);

  REQUIRE(u32_strcmp(src, U"Hello World!") == 0);
}

TEST_CASE(
  "char16_t* u16_strncpy(char16_t* dst, const size_t
dst_capacity_in_number_of_characters, const char16_t* src, const size_t
number_of_characters_to_copy)"
  ,
  "Testing global function char16_t* u16_strncpy(char16_t* dst,
const size_t dst_capacity_in_number_of_characters, const char16_t* src, const
size_t number_of_characters_to_copy)"
)
{
  char16_t src[128];

  char16_t dst[64] = u"\tHello World!\n";

  REQUIRE(trim(dst));

  REQUIRE(u16_strncpy(src, sizeof(src) / sizeof(src[0]), dst, 5)
!= nullptr);

  REQUIRE(u16_strncmp(src, u"Hello World!", 5) == 0);
}

TEST_CASE(
  "char32_t* u32_strncpy(char32_t* dst, const size_t
dst_capacity_in_number_of_characters, const char32_t* src, const size_t
number_of_characters_to_copy)"
  ,
  "Testing global function char32_t* u32_strncpy(char32_t* dst,
const size_t dst_capacity_in_number_of_characters, const char32_t* src, const
size_t number_of_characters_to_copy)"
)
{
  char32_t src[128];

  char32_t dst[64] = U"\tHello World!\n";

  REQUIRE(trim(dst));

  REQUIRE(u32_strncpy(src, sizeof(src) / sizeof(src[0]), dst, 5)
!= nullptr);

  REQUIRE(u32_strncmp(src, U"Hello World!", 5) == 0);
}

TEST_CASE("char16_t* u16_strcat(char16_t* dst, const size_t
dst_capacity_in_number_of_characters, const char16_t* src)", "Testing global
function char16_t* u16_strcat(char16_t* dst, const size_t
dst_capacity_in_number_of_characters, const char16_t* src)"
)
{
  char16_t src[512] = u" \t Hello World!\t \n";

  const char16_t* dst = u" How are you today?";

  REQUIRE(trim(src));

  REQUIRE(u16_strcat(src, sizeof(src) / sizeof(src[0]), dst) !=
nullptr);

  REQUIRE(u16_strcmp(src, u"Hello World! How are you today?") ==
0);
}

TEST_CASE("char32_t* u32_strcat(char32_t* dst, const size_t
dst_capacity_in_number_of_characters, const char32_t* src)", "Testing global
function char32_t* u32_strcat(char32_t* dst, const size_t
dst_capacity_in_number_of_characters, const char32_t* src)"
)
{
  char32_t src[512] = U" \t Hello World!\t \n";

  const char32_t* dst = U" How are you today?";

  REQUIRE(trim(src));

  REQUIRE(u32_strcat(src, sizeof(src) / sizeof(src[0]), dst) !=
nullptr);

  REQUIRE(u32_strcmp(src, U"Hello World! How are you today?") ==
0);
}

TEST_CASE(
  "char16_t* u16_strncat(char16_t* dst, const size_t
dst_capacity_in_number_of_characters, const char16_t* src, const size_t
number_of_characters_to_concatenate)"
  ,
  "Testing global function char16_t* u16_strncat(char16_t* dst,
const size_t dst_capacity_in_number_of_characters, const char16_t* src, const
size_t number_of_characters_to_concatenate)"
)
{
  char16_t src[512] = u" \t Hello World!\t \n";

  const char16_t* dst = u" How are you today?";

  REQUIRE(trim(src));

  REQUIRE(u16_strncat(src, sizeof(src) / sizeof(src[0]), dst, 4)
!= nullptr);

  REQUIRE(u16_strcmp(src, u"Hello World! How") == 0);
}

TEST_CASE(
  "char32_t* u32_strncat(char32_t* dst, const size_t
dst_capacity_in_number_of_characters, const char32_t* src, const size_t
number_of_characters_to_concatenate)"
  ,
  "Testing global function char32_t* u32_strncat(char32_t* dst,
const size_t dst_capacity_in_number_of_characters, const char32_t* src, const
size_t number_of_characters_to_concatenate)"
)
{
  char32_t src[512] = U" \t Hello World!\t \n";

  const char32_t* dst = U" How are you today?";

  REQUIRE(trim(src));

  REQUIRE(u32_strncat(src, sizeof(src) / sizeof(src[0]), dst, 4)
!= nullptr);

  REQUIRE(u32_strcmp(src, U"Hello World! How") == 0);
}

TEST_CASE("const char16_t* u16_strstr(const char16_t* src, const char16_t*
needle)", "Testing global function const char16_t* u16_strstr(const char16_t*
src, const char16_t* needle)")
{
  const char16_t* src = u"Hello World! How are you today?";

  const char16_t* needle = u"today";

  REQUIRE(u16_strstr(src, needle) != nullptr);
}

TEST_CASE("const char32_t* u32_strstr(const char32_t* src, const char32_t*
needle)", "Testing global function const char32_t* u32_strstr(const char32_t*
src, const char32_t* needle)")
{
  const char32_t* src = U"Hello World! How are you today?";

  const char32_t* needle = U"today";

  REQUIRE(u32_strstr(src, needle) != nullptr);
}

TEST_CASE("char16_t* u16_strstr(char16_t* src, const char16_t* needle)",
  "Testing global function char16_t* u16_strstr(char16_t* src,
const char16_t* needle)")
{
  char16_t src[512] = u" \t Hello World!\t \n";

  const char16_t* dst = u"World";

  REQUIRE(trim(src));

  REQUIRE(u16_strstr(src, dst) != nullptr);
}

TEST_CASE("char32_t* u32_strstr(char32_t* src, const char32_t* needle)",
  "Testing global function char32_t* u32_strstr(char32_t* src,
const char32_t* needle)")
{
  char32_t src[512] = U" \t Hello World!\t \n";

  const char32_t* dst = U"World";

  REQUIRE(trim(src));

  REQUIRE(u32_strstr(src, dst) != nullptr);
}

TEST_CASE(
  "const char16_t* u16_strstri(const char16_t* src, const
char16_t* needle, const std::locale& loc = std::locale{})", "Testing global
function const char16_t* u16_strstri(const char16_t* src, const char16_t*
needle, const std::locale& loc = std::locale{})"
)
{
  const char16_t* src = u"Hello World! How are you TODAY?";

  const char16_t* needle = u"today";

  REQUIRE(u16_strstri(src, needle) != nullptr);
}

TEST_CASE(
  "const char32_t* u32_strstri(const char32_t* src, const
char32_t* needle, const std::locale& loc = std::locale{})", "Testing global
function const char32_t* u32_strstri(const char32_t* src, const char32_t*
needle, const std::locale& loc = std::locale{})"
)
{
  const char32_t* src = U"Hello World! How are you TODAY?";

  const char32_t* needle = U"today";

  REQUIRE(u32_strstri(src, needle) != nullptr);
}

TEST_CASE("char16_t* u16_strstri(char16_t* src, const char16_t* needle, const
std::locale& loc = std::locale{})", "Testing global function char16_t*
u16_strstri(char16_t* src, const char16_t* needle, const std::locale& loc =
std::locale{})"
)
{
  char16_t src[512] = u" \t Hello World!\t \n";

  const char16_t* dst = u"Hello World!";

  REQUIRE(trim(src));

  REQUIRE(u16_strstri(src, dst) != nullptr);
}

TEST_CASE("char32_t* u32_strstri(char32_t* src, const char32_t* needle, const
std::locale& loc = std::locale{})", "Testing global function char32_t*
u32_strstri(char32_t* src, const char32_t* needle, const std::locale& loc =
std::locale{})"
)
{
  char32_t src[512] = U" \t Hello World!\t \n";

  const char32_t* dst = U"Hello World!";

  REQUIRE(trim(src));

  REQUIRE(u32_strstri(src, dst) != nullptr);
}

TEST_CASE("StringType trim(const StringType& str)",
  "Testing global template function StringType trim(const
StringType& str)")
{
  const string src{"\t Hello World!\t \n"};

  const string dst{trim(src)};

  REQUIRE(dst == string{ "Hello World!" });
}

TEST_CASE("StringType ltrim(const StringType& str)",
  "Testing global template function StringType ltrim(const
StringType& str)")
{
  const wstring src{L"\t Hello World!\t \n"};

  const wstring dst{ltrim(src)};

  REQUIRE(dst == wstring{ L"Hello World!\t \n" });
}

TEST_CASE("StringType rtrim(const StringType& str)",
  "Testing global template function StringType rtrim(const
StringType& str)")
{
  const u32string src{U"\t Hello World!\t \n"};

  const u32string dst{rtrim(src)};

  REQUIRE(dst == u32string{ U"\t Hello World!" });
}
*/
TEST_CASE(
    "str_split function template",
    "std::vector<std::basic_string<char_type>> split(const T& src,"
    "const U& needle,"
    "const V& needle_parts_separator_token,"
    "const bool split_on_whole_needle = false,"
    "const bool ignore_empty_string = true,"
    "size_t const max_count = std::basic_string<get_char_type_t<T>>::npos)") {
  const char* source{"apple|banana|cabbage|lemon|orange|pepper|plum"};
  const auto parts{str_split(source, "|", "", true)};

  REQUIRE(parts.front() == "apple"s);

  REQUIRE(parts[3] == "lemon"s);

  REQUIRE(parts.back() == "plum"s);
}

TEST_CASE("str_split_range function template",
          "std::vector<std::basic_string<typename "
          "std::iterator_traits<IteratorType>::value_type>> split(IteratorType "
          "first, IteratorType last, const NeedleType& needle, const "
          "NeedleSeparatorType& needle_parts_separator_token, const bool "
          "split_on_whole_needle = false, const bool ignore_empty_string = "
          "true, const size_t max_count = std::numeric_limits<size_t>::max()") {
  const wstring source{L"apple#banana@cabbage<lemon>orange@pepper#plum"};
  const auto parts{
      str_split_range(cbegin(source), cend(source), L"<|>|#|@", L"|", false)};

  REQUIRE(parts.front() == L"apple"s);

  REQUIRE(parts[3] == L"lemon"s);

  REQUIRE(parts.back() == L"plum"s);
}

TEST_CASE(
    "split function template",
    "std::vector<std::pair<SrcIterType, SrcIterType>> split(const SrcIterType "
    "src_first, const SrcIterType src_last, const DstIterType needle_first, "
    "const DstIterType needle_last, const bool split_on_whole_sequence = true, "
    "const bool ignore_empty_sequence = true, const size_t max_count = "
    "std::numeric_limits<size_t>::max())") {
  const u32string source{
      U"apple|-|banana|-|cabbage|-|lemon|-|orange|-|pepper|-|plum"};
  const char32_t needle[]{U"|-|"};

  const auto parts{split(cbegin(source), cend(source), &needle[0],
                         &needle[0] + len(needle), true)};

  REQUIRE(parts.size() == 7);

  const u32string first_str(parts.front().first, parts.front().second);
  const u32string third_str(parts[3].first, parts[3].second);
  const u32string last_str(parts.back().first, parts.back().second);

  REQUIRE(str_compare(first_str.c_str(), U"apple") == 0);

  REQUIRE(str_compare(third_str.c_str(), U"lemon") == 0);

  REQUIRE(str_compare(last_str.c_str(), U"plum") == 0);
}

TEST_CASE("str_starts_with function templates",
          "bool str_starts_with(const T& src, const U& needle, const bool "
          "ignore_case = false, const std::locale& loc = std::locale{})") {
  const char* src_cstr{"Apple is one of my favorite fruits."};
  const char cstr_buffer[]{"Apple is one of my favorite fruits."};
  const string src_string{src_cstr};
  const string_view src_sv{src_string};

  REQUIRE(str_starts_with(cstr_buffer, "Apple"));
  REQUIRE(str_starts_with(cstr_buffer, "apPLE", true));
  REQUIRE(str_starts_with(cstr_buffer, 'A'));
  REQUIRE(str_starts_with(cstr_buffer, 'a', true));
  REQUIRE(str_starts_with(cstr_buffer, "Apple"s));
  REQUIRE(str_starts_with(cstr_buffer, "applE"s, true));
  REQUIRE(str_starts_with(cstr_buffer, "Apple"sv));
  REQUIRE(str_starts_with(cstr_buffer, "applE"sv, true));

  REQUIRE(str_starts_with(src_cstr, "Apple"));
  REQUIRE(str_starts_with(src_cstr, "apPLE", true));
  REQUIRE(str_starts_with(src_cstr, 'A'));
  REQUIRE(str_starts_with(src_cstr, 'a', true));
  REQUIRE(str_starts_with(src_cstr, "Apple"s));
  REQUIRE(str_starts_with(src_cstr, "applE"s, true));
  REQUIRE(str_starts_with(src_cstr, "Apple"sv));
  REQUIRE(str_starts_with(src_cstr, "applE"sv, true));

  REQUIRE(str_starts_with(src_string, "Apple"));
  REQUIRE(str_starts_with(src_string, "applE", true));
  REQUIRE(str_starts_with(src_string, 'A'));
  REQUIRE(str_starts_with(src_string, 'a', true));
  REQUIRE(str_starts_with(src_string, "Apple"s));
  REQUIRE(str_starts_with(src_string, "applE"s, true));
  REQUIRE(str_starts_with(src_string, "Apple"sv));
  REQUIRE(str_starts_with(src_string, "applE"sv, true));

  REQUIRE(str_starts_with(src_sv, "Apple"));
  REQUIRE(str_starts_with(src_sv, "applE", true));
  REQUIRE(str_starts_with(src_sv, 'A'));
  REQUIRE(str_starts_with(src_sv, 'a', true));
  REQUIRE(str_starts_with(src_sv, "Apple"s));
  REQUIRE(str_starts_with(src_sv, "applE"s, true));
  REQUIRE(str_starts_with(src_sv, "Apple"sv));
  REQUIRE(str_starts_with(src_sv, "applE"sv, true));

  const wchar_t* src_wcstr{L"Apple is one of my favorite fruits."};
  const wchar_t wstr_buffer[]{L"Apple is one of my favorite fruits."};
  const wstring src_wstring{src_wcstr};
  const wstring_view src_wsv{src_wstring};

  REQUIRE(str_starts_with(wstr_buffer, L"Apple"));
  REQUIRE(str_starts_with(wstr_buffer, L"apPLE", true));
  REQUIRE(str_starts_with(wstr_buffer, L'A'));
  REQUIRE(str_starts_with(wstr_buffer, L'a', true));
  REQUIRE(str_starts_with(wstr_buffer, L"Apple"s));
  REQUIRE(str_starts_with(wstr_buffer, L"applE"s, true));
  REQUIRE(str_starts_with(wstr_buffer, L"Apple"sv));
  REQUIRE(str_starts_with(wstr_buffer, L"applE"sv, true));

  REQUIRE(str_starts_with(src_wcstr, L"Apple"));
  REQUIRE(str_starts_with(src_wcstr, L"apPLE", true));
  REQUIRE(str_starts_with(src_wcstr, L'A'));
  REQUIRE(str_starts_with(src_wcstr, L'a', true));
  REQUIRE(str_starts_with(src_wcstr, L"Apple"s));
  REQUIRE(str_starts_with(src_wcstr, L"applE"s, true));
  REQUIRE(str_starts_with(src_wcstr, L"Apple"sv));
  REQUIRE(str_starts_with(src_wcstr, L"applE"sv, true));

  REQUIRE(str_starts_with(src_wstring, L"Apple"));
  REQUIRE(str_starts_with(src_wstring, L"applE", true));
  REQUIRE(str_starts_with(src_wstring, L'A'));
  REQUIRE(str_starts_with(src_wstring, L'a', true));
  REQUIRE(str_starts_with(src_wstring, L"Apple"s));
  REQUIRE(str_starts_with(src_wstring, L"applE"s, true));
  REQUIRE(str_starts_with(src_wstring, L"Apple"sv));
  REQUIRE(str_starts_with(src_wstring, L"applE"sv, true));

  REQUIRE(str_starts_with(src_wsv, L"Apple"));
  REQUIRE(str_starts_with(src_wsv, L"applE", true));
  REQUIRE(str_starts_with(src_wsv, L'A'));
  REQUIRE(str_starts_with(src_wsv, L'a', true));
  REQUIRE(str_starts_with(src_wsv, L"Apple"s));
  REQUIRE(str_starts_with(src_wsv, L"applE"s, true));
  REQUIRE(str_starts_with(src_wsv, L"Apple"sv));
  REQUIRE(str_starts_with(src_wsv, L"applE"sv, true));
}

TEST_CASE(
    "str_contains function template",
    "bool str_contains(const T& src, const U& needle, size_t start_pos = 0U, "
    "bool ignore_case = false, const std::locale & loc = std::locale{})") {
  const char* src_cstr{"Apple is one of my favorite fruits."};
  const char cstr_buffer[]{"Apple is one of my favorite fruits."};
  const string src_string{src_cstr};
  const string_view src_sv{src_string};

  REQUIRE(str_contains(cstr_buffer, "Apple", 0U));
  REQUIRE(str_contains(cstr_buffer, "apPLE", 0U, true));
  REQUIRE(str_contains(cstr_buffer, 'f', 5U));
  REQUIRE(str_contains(cstr_buffer, 'F', 5U, true));
  REQUIRE(str_contains(cstr_buffer, "Apple"s, 0U));
  REQUIRE(str_contains(cstr_buffer, "applE"s, 0U, true));
  REQUIRE(str_contains(cstr_buffer, "Apple"sv, 0U));
  REQUIRE(str_contains(cstr_buffer, "applE"sv, 0U, true));

  REQUIRE(str_contains(src_cstr, "Apple", 0U));
  REQUIRE(str_contains(src_cstr, "apPLE", 0U, true));
  REQUIRE(str_contains(src_cstr, 'f', 5U));
  REQUIRE(str_contains(src_cstr, 'F', 5U, true));
  REQUIRE(str_contains(src_cstr, "Apple"s, 0U));
  REQUIRE(str_contains(src_cstr, "applE"s, 0U, true));
  REQUIRE(str_contains(src_cstr, "Apple"sv, 0U));
  REQUIRE(str_contains(src_cstr, "applE"sv, 0U, true));

  REQUIRE(str_contains(src_string, "Apple", 0U));
  REQUIRE(str_contains(src_string, "apPLE", 0U, true));
  REQUIRE(str_contains(src_string, 'f', 5U));
  REQUIRE(str_contains(src_string, 'F', 5U, true));
  REQUIRE(str_contains(src_string, "Apple"s, 0U));
  REQUIRE(str_contains(src_string, "applE"s, 0U, true));
  REQUIRE(str_contains(src_string, "Apple"sv, 0U));
  REQUIRE(str_contains(src_string, "applE"sv, 0U, true));

  REQUIRE(str_contains(src_sv, "Apple", 0U));
  REQUIRE(str_contains(src_sv, "apPLE", 0U, true));
  REQUIRE(str_contains(src_sv, 'f', 5U));
  REQUIRE(str_contains(src_sv, 'F', 5U, true));
  REQUIRE(str_contains(src_sv, "Apple"s, 0U));
  REQUIRE(str_contains(src_sv, "applE"s, 0U, true));
  REQUIRE(str_contains(src_sv, "Apple"sv, 0U));
  REQUIRE(str_contains(src_sv, "applE"sv, 0U, true));

  const wchar_t* src_wcstr{L"Apple is one of my favorite fruits."};
  const wchar_t wstr_buffer[]{L"Apple is one of my favorite fruits."};
  const wstring src_wstring{src_wcstr};
  const wstring_view src_wsv{src_wstring};

  REQUIRE(str_contains(wstr_buffer, L"Apple", 0U));
  REQUIRE(str_contains(wstr_buffer, L"apPLE", 0U, true));
  REQUIRE(str_contains(wstr_buffer, L'f', 5U));
  REQUIRE(str_contains(wstr_buffer, L'F', 5U, true));
  REQUIRE(str_contains(wstr_buffer, L"Apple"s, 0U));
  REQUIRE(str_contains(wstr_buffer, L"applE"s, 0U, true));
  REQUIRE(str_contains(wstr_buffer, L"Apple"sv, 0U));
  REQUIRE(str_contains(wstr_buffer, L"applE"sv, 0U, true));

  REQUIRE(str_contains(src_wcstr, L"Apple", 0U));
  REQUIRE(str_contains(src_wcstr, L"apPLE", 0U, true));
  REQUIRE(str_contains(src_wcstr, L'f', 5U));
  REQUIRE(str_contains(src_wcstr, L'F', 5U, true));
  REQUIRE(str_contains(src_wcstr, L"Apple"s, 0U));
  REQUIRE(str_contains(src_wcstr, L"applE"s, 0U, true));
  REQUIRE(str_contains(src_wcstr, L"Apple"sv, 0U));
  REQUIRE(str_contains(src_wcstr, L"applE"sv, 0U, true));

  REQUIRE(str_contains(src_wstring, L"Apple", 0U));
  REQUIRE(str_contains(src_wstring, L"apPLE", 0U, true));
  REQUIRE(str_contains(src_wstring, L'f', 5U));
  REQUIRE(str_contains(src_wstring, L'F', 5U, true));
  REQUIRE(str_contains(src_wstring, L"Apple"s, 0U));
  REQUIRE(str_contains(src_wstring, L"applE"s, 0U, true));
  REQUIRE(str_contains(src_wstring, L"Apple"sv, 0U));
  REQUIRE(str_contains(src_wstring, L"applE"sv, 0U, true));

  REQUIRE(str_contains(src_wsv, L"Apple", 0U));
  REQUIRE(str_contains(src_wsv, L"apPLE", 0U, true));
  REQUIRE(str_contains(src_wsv, L'f', 5U));
  REQUIRE(str_contains(src_wsv, L'F', 5U, true));
  REQUIRE(str_contains(src_wsv, L"Apple"s, 0U));
  REQUIRE(str_contains(src_wsv, L"applE"s, 0U, true));
  REQUIRE(str_contains(src_wsv, L"Apple"sv, 0U));
  REQUIRE(str_contains(src_wsv, L"applE"sv, 0U, true));
}

TEST_CASE("str_index_of function template",
          "typename std::basic_string<get_char_type_t<T>>::size_type "
          "str_index_of(const T& src, const U& needle, const size_t start_pos "
          "= 0U, const bool ignore_case = false, const std::locale & loc = "
          "std::locale{})") {
  const char* src_cstr{"Hello World!"};
  const char cstr_buffer[]{"Hello World!"};
  const string src_string{src_cstr};
  const string_view src_sv{src_string};

  REQUIRE(0U == str_index_of(cstr_buffer, "Hello", 0U));
  REQUIRE(0U == str_index_of(cstr_buffer, "heLlO", 0U, true));
  REQUIRE(6U == str_index_of(cstr_buffer, 'W', 5U));
  REQUIRE(6U == str_index_of(cstr_buffer, 'w', 5U, true));
  REQUIRE(0U == str_index_of(cstr_buffer, "Hello"s, 0U));
  REQUIRE(0U == str_index_of(cstr_buffer, "heLlO"s, 0U, true));
  REQUIRE(0U == str_index_of(cstr_buffer, "Hello"sv, 0U));
  REQUIRE(0U == str_index_of(cstr_buffer, "heLlO"sv, 0U, true));

  REQUIRE(0U == str_index_of(src_cstr, "Hello", 0U));
  REQUIRE(0U == str_index_of(src_cstr, "heLlO", 0U, true));
  REQUIRE(6U == str_index_of(src_cstr, 'W', 5U));
  REQUIRE(6U == str_index_of(src_cstr, 'w', 5U, true));
  REQUIRE(0U == str_index_of(src_cstr, "Hello"s, 0U));
  REQUIRE(0U == str_index_of(src_cstr, "heLlO"s, 0U, true));
  REQUIRE(0U == str_index_of(src_cstr, "Hello"sv, 0U));
  REQUIRE(0U == str_index_of(src_cstr, "heLlO"sv, 0U, true));

  REQUIRE(0U == str_index_of(src_string, "Hello", 0U));
  REQUIRE(0U == str_index_of(src_string, "heLlO", 0U, true));
  REQUIRE(6U == str_index_of(src_string, 'W', 5U));
  REQUIRE(6U == str_index_of(src_string, 'w', 5U, true));
  REQUIRE(0U == str_index_of(src_string, "Hello"s, 0U));
  REQUIRE(0U == str_index_of(src_string, "heLlO"s, 0U, true));
  REQUIRE(0U == str_index_of(src_string, "Hello"sv, 0U));
  REQUIRE(0U == str_index_of(src_string, "heLlO"sv, 0U, true));

  REQUIRE(0U == str_index_of(src_sv, "Hello", 0U));
  REQUIRE(0U == str_index_of(src_sv, "heLlO", 0U, true));
  REQUIRE(6U == str_index_of(src_sv, 'W', 5U));
  REQUIRE(6U == str_index_of(src_sv, 'w', 5U, true));
  REQUIRE(0U == str_index_of(src_sv, "Hello"s, 0U));
  REQUIRE(0U == str_index_of(src_sv, "heLlO"s, 0U, true));
  REQUIRE(0U == str_index_of(src_sv, "Hello"sv, 0U));
  REQUIRE(0U == str_index_of(src_sv, "heLlO"sv, 0U, true));

  const wchar_t* src_wcstr{L"Hello World!"};
  const wchar_t wstr_buffer[]{L"Hello World!"};
  const wstring src_wstring{src_wcstr};
  const wstring_view src_wsv{src_wstring};

  REQUIRE(0U == str_index_of(wstr_buffer, L"Hello", 0U));
  REQUIRE(0U == str_index_of(wstr_buffer, L"heLlO", 0U, true));
  REQUIRE(6U == str_index_of(wstr_buffer, L'W', 5U));
  REQUIRE(6U == str_index_of(wstr_buffer, L'w', 5U, true));
  REQUIRE(0U == str_index_of(wstr_buffer, L"Hello"s, 0U));
  REQUIRE(0U == str_index_of(wstr_buffer, L"heLlO"s, 0U, true));
  REQUIRE(0U == str_index_of(wstr_buffer, L"Hello"sv, 0U));
  REQUIRE(0U == str_index_of(wstr_buffer, L"heLlO"sv, 0U, true));

  REQUIRE(0U == str_index_of(src_wcstr, L"Hello", 0U));
  REQUIRE(0U == str_index_of(src_wcstr, L"heLlO", 0U, true));
  REQUIRE(6U == str_index_of(src_wcstr, L'W', 5U));
  REQUIRE(6U == str_index_of(src_wcstr, L'w', 5U, true));
  REQUIRE(0U == str_index_of(src_wcstr, L"Hello"s, 0U));
  REQUIRE(0U == str_index_of(src_wcstr, L"heLlO"s, 0U, true));
  REQUIRE(0U == str_index_of(src_wcstr, L"Hello"sv, 0U));
  REQUIRE(0U == str_index_of(src_wcstr, L"heLlO"sv, 0U, true));

  REQUIRE(0U == str_index_of(src_wstring, L"Hello", 0U));
  REQUIRE(0U == str_index_of(src_wstring, L"heLlO", 0U, true));
  REQUIRE(6U == str_index_of(src_wstring, L'W', 5U));
  REQUIRE(6U == str_index_of(src_wstring, L'w', 5U, true));
  REQUIRE(0U == str_index_of(src_wstring, L"Hello"s, 0U));
  REQUIRE(0U == str_index_of(src_wstring, L"heLlO"s, 0U, true));
  REQUIRE(0U == str_index_of(src_wstring, L"Hello"sv, 0U));
  REQUIRE(0U == str_index_of(src_wstring, L"heLlO"sv, 0U, true));

  REQUIRE(0U == str_index_of(src_wsv, L"Hello", 0U));
  REQUIRE(0U == str_index_of(src_wsv, L"heLlO", 0U, true));
  REQUIRE(6U == str_index_of(src_wsv, L'W', 5U));
  REQUIRE(6U == str_index_of(src_wsv, L'w', 5U, true));
  REQUIRE(0U == str_index_of(src_wsv, L"Hello"s, 0U));
  REQUIRE(0U == str_index_of(src_wsv, L"heLlO"s, 0U, true));
  REQUIRE(0U == str_index_of(src_wsv, L"Hello"sv, 0U));
  REQUIRE(0U == str_index_of(src_wsv, L"heLlO"sv, 0U, true));
}

TEST_CASE("str_ends_with function template",
          "bool str_ends_with(const T & src, const U& needle, bool ignore_case "
          "= false, const std::locale& loc = std::locale{}") {
  const char* src_cstr{"Hello World"};
  const char cstr_buffer[]{"Hello World"};
  const string src_string{src_cstr};
  const string_view src_sv{src_string};

  REQUIRE(str_ends_with(cstr_buffer, "World"));
  REQUIRE(str_ends_with(cstr_buffer, "woRlD", true));
  REQUIRE(str_ends_with(cstr_buffer, 'd'));
  REQUIRE(str_ends_with(cstr_buffer, 'D', true));
  REQUIRE(str_ends_with(cstr_buffer, "World"s));
  REQUIRE(str_ends_with(cstr_buffer, "woRlD"s, true));
  REQUIRE(str_ends_with(cstr_buffer, "World"sv));
  REQUIRE(str_ends_with(cstr_buffer, "woRlD"sv, true));

  REQUIRE(str_ends_with(src_cstr, "World"));
  REQUIRE(str_ends_with(src_cstr, "woRlD", true));
  REQUIRE(str_ends_with(src_cstr, 'd'));
  REQUIRE(str_ends_with(src_cstr, 'D', true));
  REQUIRE(str_ends_with(src_cstr, "World"s));
  REQUIRE(str_ends_with(src_cstr, "woRlD"s, true));
  REQUIRE(str_ends_with(src_cstr, "World"sv));
  REQUIRE(str_ends_with(src_cstr, "woRlD"sv, true));

  REQUIRE(str_ends_with(src_string, "World"));
  REQUIRE(str_ends_with(src_string, "woRlD", true));
  REQUIRE(str_ends_with(src_string, 'd'));
  REQUIRE(str_ends_with(src_string, 'D', true));
  REQUIRE(str_ends_with(src_string, "World"s));
  REQUIRE(str_ends_with(src_string, "woRlD"s, true));
  REQUIRE(str_ends_with(src_string, "World"sv));
  REQUIRE(str_ends_with(src_string, "woRlD"sv, true));

  REQUIRE(str_ends_with(src_sv, "World"));
  REQUIRE(str_ends_with(src_sv, "woRlD", true));
  REQUIRE(str_ends_with(src_sv, 'd'));
  REQUIRE(str_ends_with(src_sv, 'D', true));
  REQUIRE(str_ends_with(src_sv, "World"s));
  REQUIRE(str_ends_with(src_sv, "woRlD"s, true));
  REQUIRE(str_ends_with(src_sv, "World"sv));
  REQUIRE(str_ends_with(src_sv, "woRlD"sv, true));

  const wchar_t* src_wcstr{L"Hello World"};
  const wchar_t wstr_buffer[]{L"Hello World"};
  const wstring src_wstring{src_wcstr};
  const wstring_view src_wsv{src_wstring};

  REQUIRE(str_ends_with(wstr_buffer, L"World"));
  REQUIRE(str_ends_with(wstr_buffer, L"woRlD", true));
  REQUIRE(str_ends_with(wstr_buffer, L'd'));
  REQUIRE(str_ends_with(wstr_buffer, L'D', true));
  REQUIRE(str_ends_with(wstr_buffer, L"World"s));
  REQUIRE(str_ends_with(wstr_buffer, L"woRlD"s, true));
  REQUIRE(str_ends_with(wstr_buffer, L"World"sv));
  REQUIRE(str_ends_with(wstr_buffer, L"woRlD"sv, true));

  REQUIRE(str_ends_with(src_wcstr, L"World"));
  REQUIRE(str_ends_with(src_wcstr, L"woRlD", true));
  REQUIRE(str_ends_with(src_wcstr, L'd'));
  REQUIRE(str_ends_with(src_wcstr, L'D', true));
  REQUIRE(str_ends_with(src_wcstr, L"World"s));
  REQUIRE(str_ends_with(src_wcstr, L"woRlD"s, true));
  REQUIRE(str_ends_with(src_wcstr, L"World"sv));
  REQUIRE(str_ends_with(src_wcstr, L"woRlD"sv, true));

  REQUIRE(str_ends_with(src_wstring, L"World"));
  REQUIRE(str_ends_with(src_wstring, L"woRlD", true));
  REQUIRE(str_ends_with(src_wstring, L'd'));
  REQUIRE(str_ends_with(src_wstring, L'D', true));
  REQUIRE(str_ends_with(src_wstring, L"World"s));
  REQUIRE(str_ends_with(src_wstring, L"woRlD"s, true));
  REQUIRE(str_ends_with(src_wstring, L"World"sv));
  REQUIRE(str_ends_with(src_wstring, L"woRlD"sv, true));

  REQUIRE(str_ends_with(src_wsv, L"World"));
  REQUIRE(str_ends_with(src_wsv, L"woRlD", true));
  REQUIRE(str_ends_with(src_wsv, L'd'));
  REQUIRE(str_ends_with(src_wsv, L'D', true));
  REQUIRE(str_ends_with(src_wsv, L"World"s));
  REQUIRE(str_ends_with(src_wsv, L"woRlD"s, true));
  REQUIRE(str_ends_with(src_wsv, L"World"sv));
  REQUIRE(str_ends_with(src_wsv, L"woRlD"sv, true));
}

TEST_CASE("bool has_key(const ContainerType& container,const KeyType& key)",
          "Testing global function template bool has_key(const ContainerType& "
          "container,const KeyType& key)") {
  set<int> unique_numbers1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  unordered_set<int> unique_numbers2{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  map<string, int> unique_number_labels1{
      {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4}, {"five", 5},
      {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}, {"ten", 10}};
  unordered_map<string, int> unique_number_labels2{
      {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4}, {"five", 5},
      {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}, {"ten", 10}};
  multiset<int> numbers1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  unordered_multiset<int> numbers2{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  multimap<string, int> number_labels1{
      {"one", 1},   {"two", 2},   {"three", 3}, {"one", 1},  {"five", 5},
      {"three", 3}, {"seven", 7}, {"eight", 8}, {"nine", 9}, {"ten", 10}};
  unordered_multimap<string, int> number_labels2{
      {"one", 1},   {"two", 2},   {"three", 3}, {"one", 1},  {"five", 5},
      {"three", 3}, {"seven", 7}, {"eight", 8}, {"nine", 9}, {"ten", 10}};

  REQUIRE(has_key(unique_numbers1, 5));
  REQUIRE(!has_key(unique_numbers1, 15));
  REQUIRE(has_key(unique_numbers2, 5));
  REQUIRE(!has_key(unique_numbers2, 15));

  REQUIRE(has_key(unique_number_labels1, "five"));
  REQUIRE(!has_key(unique_number_labels1, "fifteen"));
  REQUIRE(has_key(unique_number_labels2, "five"));
  REQUIRE(!has_key(unique_number_labels2, "fifteen"));

  REQUIRE(has_key(numbers1, 5));
  REQUIRE(!has_key(numbers1, 15));
  REQUIRE(has_key(numbers2, 5));
  REQUIRE(!has_key(numbers2, 15));

  REQUIRE(has_key(number_labels1, "five"));
  REQUIRE(!has_key(number_labels1, "fifteen"));
  REQUIRE(has_key(number_labels2, "five"));
  REQUIRE(!has_key(number_labels2, "fifteen"));
}

TEST_CASE(
    "bool has_value(const ContainerType& container, const ValueType& value)",
    "Testing global function template bool has_value(const ContainerType& "
    "container, const ValueType& value)") {
  array<int, 10> ar{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
  vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  deque<int> d{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  forward_list<int> fl{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  list<int> dl{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  REQUIRE(has_value(ar, 5));
  REQUIRE(!has_value(ar, 15));
  REQUIRE(has_value(v, 5));
  REQUIRE(!has_value(v, 15));
  REQUIRE(has_value(d, 5));
  REQUIRE(!has_value(d, 15));
  REQUIRE(has_value(fl, 5));
  REQUIRE(!has_value(fl, 15));
  REQUIRE(has_value(dl, 5));
  REQUIRE(!has_value(dl, 15));

  set<int> unique_numbers1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  unordered_set<int> unique_numbers2{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  map<string, int> unique_number_labels1{
      {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4}, {"five", 5},
      {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}, {"ten", 10}};
  unordered_map<string, int> unique_number_labels2{
      {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4}, {"five", 5},
      {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}, {"ten", 10}};
  multiset<int> numbers1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  unordered_multiset<int> numbers2{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  multimap<string, int> number_labels1{
      {"one", 1},   {"two", 2},   {"three", 3}, {"one", 1},  {"five", 5},
      {"three", 3}, {"seven", 7}, {"eight", 8}, {"nine", 9}, {"ten", 10}};
  unordered_multimap<string, int> number_labels2{
      {"one", 1},   {"two", 2},   {"three", 3}, {"one", 1},  {"five", 5},
      {"three", 3}, {"seven", 7}, {"eight", 8}, {"nine", 9}, {"ten", 10}};

  REQUIRE(has_value(unique_numbers1, 5));
  REQUIRE(!has_value(unique_numbers1, 15));
  REQUIRE(has_value(unique_numbers2, 5));
  REQUIRE(!has_value(unique_numbers2, 15));

  REQUIRE(has_value(unique_number_labels1, 5));
  REQUIRE(!has_value(unique_number_labels1, 15));
  REQUIRE(has_value(unique_number_labels2, 5));
  REQUIRE(!has_value(unique_number_labels2, 15));

  REQUIRE(has_value(numbers1, 5));
  REQUIRE(!has_value(numbers1, 15));
  REQUIRE(has_value(numbers2, 5));
  REQUIRE(!has_value(numbers2, 15));

  REQUIRE(has_value(number_labels1, 5));
  REQUIRE(!has_value(number_labels1, 15));
  REQUIRE(has_value(number_labels2, 5));
  REQUIRE(!has_value(number_labels2, 15));
}

TEST_CASE(
    "bool has_kv_pair(const ContainerType& container, const typename "
    "ContainerType::value_type& key_value_pair)",
    "Testing global function template bool has_kv_pair(const "
    "ContainerType& container, const typename ContainerType::value_type& "
    "key_value_pair)") {
  map<string, int> unique_number_labels1{
      {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4}, {"five", 5},
      {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}, {"ten", 10}};
  unordered_map<string, int> unique_number_labels2{
      {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4}, {"five", 5},
      {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}, {"ten", 10}};
  multimap<string, int> number_labels1{
      {"one", 1},   {"two", 2},   {"three", 3}, {"one", 1},  {"five", 5},
      {"three", 3}, {"seven", 7}, {"eight", 8}, {"nine", 9}, {"ten", 10}};
  unordered_multimap<string, int> number_labels2{
      {"one", 1},   {"two", 2},   {"three", 3}, {"one", 1},  {"five", 5},
      {"three", 3}, {"seven", 7}, {"eight", 8}, {"nine", 9}, {"ten", 10}};

  REQUIRE(has_kv_pair(unique_number_labels1, {"one", 1}));
  REQUIRE(!has_kv_pair(unique_number_labels1, {"fifteen", 15}));

  REQUIRE(has_kv_pair(unique_number_labels2, {"one", 1}));
  REQUIRE(!has_kv_pair(unique_number_labels2, {"fifteen", 15}));

  REQUIRE(has_kv_pair(number_labels1, {"one", 1}));
  REQUIRE(!has_kv_pair(number_labels1, {"fifteen", 15}));

  REQUIRE(has_kv_pair(number_labels2, {"one", 1}));
  REQUIRE(!has_kv_pair(number_labels2, {"fifteen", 15}));
}

TEST_CASE(
    "bool has_item(ForwardIterType first, ForwardIterType last, ItemType&& "
    "item)",
    "Testing global function template bool has_item(ForwardIterType first, "
    "ForwardIterType last, ItemType&& item)") {
  array<int, 10> ar{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
  vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  deque<int> d{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  forward_list<int> fl{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  list<int> dl{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  REQUIRE(has_item(cbegin(ar), cend(ar), 5));
  REQUIRE(has_item(cbegin(ar), cbegin(ar) + 5, 5));
  REQUIRE(!has_item(cbegin(ar), cbegin(ar) + 3, 5));

  REQUIRE(has_item(cbegin(v), cend(v), 5));
  REQUIRE(has_item(cbegin(v), cbegin(v) + 5, 5));
  REQUIRE(!has_item(cbegin(v), cbegin(v) + 3, 5));

  REQUIRE(has_item(cbegin(d), cend(d), 5));
  REQUIRE(has_item(cbegin(d), cbegin(d) + 5, 5));
  REQUIRE(!has_item(cbegin(d), cbegin(d) + 3, 5));

  auto fl_first{cbegin(fl)};
  auto fl_last1{fl_first}, fl_last2{fl_first};
  advance(fl_last1, 5);
  advance(fl_last2, 3);

  REQUIRE(has_item(fl_first, cend(fl), 5));
  REQUIRE(has_item(fl_first, fl_last1, 5));
  REQUIRE(!has_item(fl_first, fl_last2, 5));

  auto dl_first{cbegin(dl)};
  auto dl_last1{dl_first}, dl_last2{dl_first};
  advance(dl_last1, 5);
  advance(dl_last2, 3);

  REQUIRE(has_item(dl_first, cend(dl), 5));
  REQUIRE(has_item(dl_first, dl_last1, 5));
  REQUIRE(!has_item(dl_first, dl_last2, 5));

  map<string, int> unique_number_labels1{
      {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4}, {"five", 5},
      {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}, {"ten", 10}};
  unordered_map<string, int> unique_number_labels2{
      {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4}, {"five", 5},
      {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}, {"ten", 10}};
  multimap<string, int> number_labels1{
      {"one", 1},   {"two", 2},   {"three", 3}, {"one", 1},  {"five", 5},
      {"three", 3}, {"seven", 7}, {"eight", 8}, {"nine", 9}, {"ten", 10}};
  unordered_multimap<string, int> number_labels2{
      {"one", 1},   {"two", 2},   {"three", 3}, {"one", 1},  {"five", 5},
      {"three", 3}, {"seven", 7}, {"eight", 8}, {"nine", 9}, {"ten", 10}};

  REQUIRE(has_item(cbegin(unique_number_labels1), cend(unique_number_labels1),
                   pair<const string, int>{"one"s, 1}));
  REQUIRE(!has_item(cbegin(unique_number_labels1), cend(unique_number_labels1),
                    pair<const string, int>{"fifteen"s, 15}));

  REQUIRE(has_item(cbegin(unique_number_labels2), cend(unique_number_labels2),
                   pair<const string, int>{"one"s, 1}));
  REQUIRE(!has_item(cbegin(unique_number_labels2), cend(unique_number_labels2),
                    pair<const string, int>{"fifteen"s, 15}));

  REQUIRE(has_item(cbegin(number_labels1), cend(number_labels1),
                   pair<const string, int>{"one"s, 1}));
  REQUIRE(!has_item(cbegin(number_labels1), cend(number_labels1),
                    pair<const string, int>{"fifteen"s, 15}));

  REQUIRE(has_item(cbegin(number_labels2), cend(number_labels2),
                   pair<const string, int>{"one"s, 1}));
  REQUIRE(!has_item(cbegin(number_labels2), cend(number_labels2),
                    pair<const string, int>{"fifteen"s, 15}));
}

TEST_CASE(
    "std::basic_string<get_char_type<T>> substr(const T& src, const size_t "
    "start_pos, size_t character_count = std::numeric_limits<size_t>::max())",
    "Testing substr global function template") {
  const string expected_result1{"World"};
  const wstring expected_result2{L"World"};
  const u16string expected_result3{u"World"};
  const u32string expected_result4{U"World"};

  string actual_result1 = substr("Hello World!", 6U, 5U);
  REQUIRE(actual_result1 == expected_result1);

  const wchar_t* wcstr = L"Hello World!";
  wstring actual_result2 = substr(wcstr, 6U, 5U);
  REQUIRE(actual_result2 == expected_result2);

  const u16string u16src_str{u"Hello World!"};
  u16string actual_result3 = substr(u16src_str, 6U, 5U);
  REQUIRE(actual_result3 == expected_result3);

  const u32string_view u32src_sv{U"Hello World!"};
  u32string actual_result4 = substr(u32src_sv, 6U, 5U);
  REQUIRE(actual_result4 == expected_result4);
}

TEST_CASE(
    "std::pair<ForwardIterType, ForwardIterType> "
    "find_first_sequence_of_allowed_elements(ForwardIterType first, "
    "ForwardIterType last, const ContainerType& haystack, const bool "
    "is_haystack_sorted = false)",
    "Testing global function template "
    "find_first_sequence_of_allowed_elements") {
  std::random_device rd{};
  constexpr const array<char, 64> allowed_chars{
      {"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_"}};

  vector<char> vector_of_allowed_chars_unsorted{cbegin(allowed_chars),
                                                cend(allowed_chars)};

  shuffle(begin(vector_of_allowed_chars_unsorted),
          end(vector_of_allowed_chars_unsorted), mt19937{rd()});

  list<char> list_of_allowed_chars_unsorted{
      cbegin(vector_of_allowed_chars_unsorted),
      cend(vector_of_allowed_chars_unsorted)};

  unordered_set<char> allowed_chars_hash_set{cbegin(allowed_chars),
                                             cend(allowed_chars)};

  const vector<string> sentences{"fun&!! time", "Love dogs!",
                                 "I_love_both cats and dogs as well!"};
  const vector<string> correct_words{"fun", "Love", "I_love_both"};

  for (size_t i{}; i != sentences.size(); ++i) {
    const auto first_last_iter_pair1 = find_first_sequence_of_allowed_elements(
        cbegin(sentences.at(i)), cend(sentences.at(i)),
        vector_of_allowed_chars_unsorted);
    const auto first_last_iter_pair2 = find_first_sequence_of_allowed_elements(
        cbegin(sentences.at(i)), cend(sentences.at(i)),
        list_of_allowed_chars_unsorted);
    const auto first_last_iter_pair3 = find_first_sequence_of_allowed_elements(
        cbegin(sentences.at(i)), cend(sentences.at(i)), allowed_chars_hash_set);

    const string found_word1(first_last_iter_pair1.first,
                             first_last_iter_pair1.second);
    const string found_word2(first_last_iter_pair2.first,
                             first_last_iter_pair2.second);
    const string found_word3(first_last_iter_pair3.first,
                             first_last_iter_pair3.second);

    REQUIRE(correct_words.at(i) == found_word1);
    REQUIRE(found_word1 == found_word2);
    REQUIRE(found_word1 == found_word3);
    REQUIRE(found_word2 == found_word3);
  }
}

TEST_CASE(
    "std::pair<IterType, IterType> find_longest_word(IterType first, const "
    "IterType last, ContainerType& haystack)",
    "Testing global function template find_longest_word") {
  std::random_device rd{};
  constexpr const array<char, 64> allowed_chars{
      {"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_"}};

  vector<char> vector_of_allowed_chars_unsorted{cbegin(allowed_chars),
                                                cend(allowed_chars)};

  shuffle(begin(vector_of_allowed_chars_unsorted),
          end(vector_of_allowed_chars_unsorted), mt19937{rd()});

  list<char> list_of_allowed_chars_unsorted{
      cbegin(vector_of_allowed_chars_unsorted),
      cend(vector_of_allowed_chars_unsorted)};

  unordered_set<char> allowed_chars_hash_set{cbegin(allowed_chars),
                                             cend(allowed_chars)};

  const vector<string> sentences{"fun&!! time", "I love dogs!",
                                 "I_love_both cats and dogs as well!"};
  const vector<string> correct_words{"time", "love", "I_love_both"};

  for (size_t i{}; i != sentences.size(); ++i) {
    const auto first_last_iter_pair1 =
        find_longest_word(cbegin(sentences.at(i)), cend(sentences.at(i)),
                          vector_of_allowed_chars_unsorted);
    const auto first_last_iter_pair2 =
        find_longest_word(cbegin(sentences.at(i)), cend(sentences.at(i)),
                          list_of_allowed_chars_unsorted);
    const auto first_last_iter_pair3 = find_longest_word(
        cbegin(sentences.at(i)), cend(sentences.at(i)), allowed_chars_hash_set);

    const string found_word1(first_last_iter_pair1.first,
                             first_last_iter_pair1.second);
    const string found_word2(first_last_iter_pair2.first,
                             first_last_iter_pair2.second);
    const string found_word3(first_last_iter_pair3.first,
                             first_last_iter_pair3.second);

    REQUIRE(correct_words.at(i) == found_word1);
    REQUIRE(found_word1 == found_word2);
    REQUIRE(found_word1 == found_word3);
    REQUIRE(found_word2 == found_word3);
  }
}

TEST_CASE(
    "constexpr std::pair<ForwardIterType1, ForwardIterType2> "
    "copy_forward_while_true(ForwardIterType1 src_first, const "
    "ForwardIterType1 src_last, ForwardIterType2 dst_first, Predicate p) "
    "noexcept(boolean expression)",
    "Testing global function template copy_forward_while_true") {
  const vector<int> src1{};
  vector<int> dst1{};
  const vector<int> expected_numbers1{};

  const auto iter_pair1 =
      copy_forward_while_true(cbegin(src1), cend(src1), back_inserter(dst1),
                              [](const auto n) { return n % 2 == 1; });

  REQUIRE(0U == dst1.size());
  REQUIRE(expected_numbers1 == dst1);
  REQUIRE(iter_pair1.first == cend(src1));

  const vector<int> src2{0, 2, 4, 6, 7, 8, 10, 11, 12, 14};
  vector<int> dst2{};
  const vector<int> expected_numbers2{};

  const auto iter_pair2 =
      copy_forward_while_true(cbegin(src2), cend(src2), back_inserter(dst2),
                              [](const auto n) { return n % 2 == 1; });

  REQUIRE(0U == dst2.size());
  REQUIRE(expected_numbers2 == dst2);
  REQUIRE(iter_pair2.first == cbegin(src2));
  REQUIRE(*(iter_pair2.first) == 0);

  const vector<int> src3{0, 2, 4, 6, 7, 8, 10, 11, 12, 14};
  vector<int> dst3{};
  const vector<int> expected_numbers3{0, 2, 4, 6};

  const auto iter_pair3 =
      copy_forward_while_true(cbegin(src3), cend(src3), back_inserter(dst3),
                              [](const auto n) { return n % 2 == 0; });

  REQUIRE(4U == dst3.size());
  REQUIRE(expected_numbers3 == dst3);
  REQUIRE(iter_pair3.first != cend(src3));
  REQUIRE(*(iter_pair3.first) == 7);
}

TEST_CASE(
    "constexpr std::pair<ForwardIterType1, ForwardIterType2> "
    "copy_forward_while_false(ForwardIterType1 src_first, const "
    "ForwardIterType1 src_last, ForwardIterType2 dst_first, Predicate p) "
    "noexcept(boolean expression)",
    "Testing global function template copy_forward_while_false") {
  const vector<int> src1{};
  vector<int> dst1{};
  const vector<int> expected_numbers1{};

  const auto iter_pair1 =
      copy_forward_while_false(cbegin(src1), cend(src1), back_inserter(dst1),
                               [](const auto n) { return n % 2 == 0; });

  REQUIRE(0U == dst1.size());
  REQUIRE(expected_numbers1 == dst1);
  REQUIRE(iter_pair1.first == cend(src1));

  const vector<int> src2{0, 2, 4, 6, 7, 8, 10, 11, 12, 14};
  vector<int> dst2{};
  const vector<int> expected_numbers2{};

  const auto iter_pair2 =
      copy_forward_while_false(cbegin(src2), cend(src2), back_inserter(dst2),
                               [](const auto n) { return n % 2 == 0; });

  REQUIRE(0U == dst2.size());
  REQUIRE(expected_numbers2 == dst2);
  REQUIRE(iter_pair2.first == cbegin(src2));
  REQUIRE(*(iter_pair2.first) == 0);

  const vector<int> src3{0, 2, 4, 6, 7, 8, 10, 11, 12, 14};
  vector<int> dst3{};
  const vector<int> expected_numbers3{0, 2, 4, 6};

  const auto iter_pair3 =
      copy_forward_while_false(cbegin(src3), cend(src3), back_inserter(dst3),
                               [](const auto n) { return n % 2 == 1; });

  REQUIRE(4U == dst3.size());
  REQUIRE(expected_numbers3 == dst3);
  REQUIRE(iter_pair3.first != cend(src3));
  REQUIRE(*(iter_pair3.first) == 7);
}

TEST_CASE(
    "constexpr std::pair<BidirIterType1, BidirIterType2> "
    "copy_backward_while_true(const BidirIterType1 src_first, BidirIterType1 "
    "src_last, BidirIterType2 dst_last, Predicate p) noexcept(boolean "
    "expression)",
    "Testing global function template copy_backward_while_true") {
  const vector<int> src1{};
  vector<int> dst1(src1.size(), 0);
  const vector<int> expected_numbers1{};

  const auto iter_pair1 =
      copy_backward_while_true(cbegin(src1), cend(src1), end(dst1),
                               [](const auto n) { return n % 2 == 1; });

  REQUIRE(0U == dst1.size());
  REQUIRE(expected_numbers1 == dst1);
  REQUIRE(iter_pair1.first == cend(src1));
  REQUIRE(iter_pair1.second == end(dst1));

  const vector<int> src2{0, 2, 4, 6, 7, 8, 10, 11, 12, 14};
  vector<int> dst2(src2.size(), 0);
  const vector<int> expected_numbers2{dst2};

  const auto iter_pair2 =
      copy_backward_while_true(cbegin(src2), cend(src2), end(dst2),
                               [](const auto n) { return n % 2 == 1; });

  REQUIRE(src2.size() == dst2.size());
  REQUIRE(expected_numbers2 == dst2);
  REQUIRE(iter_pair2.first == cend(src2));
  REQUIRE(iter_pair2.second == end(dst2));

  const vector<int> src3{0, 2, 4, 6, 7, 8, 10, 11, 12, 14, 16};
  vector<int> dst3(src3.size(), 0);
  const vector<int> expected_numbers3{0, 0, 0, 0, 0, 0, 0, 0, 12, 14, 16};

  const auto iter_pair3 =
      copy_backward_while_true(cbegin(src3), cend(src3), end(dst3),
                               [](const auto n) { return n % 2 == 0; });

  REQUIRE(src3.size() == dst3.size());
  REQUIRE(vector<int>(iter_pair3.first, cend(src3)) ==
          vector<int>(iter_pair3.second, end(dst3)));
  REQUIRE(expected_numbers3 == dst3);
  REQUIRE(iter_pair3.first != cend(src3));
  REQUIRE(*(iter_pair3.first) == 12);
  REQUIRE(*(iter_pair3.second) == 12);
}

TEST_CASE(
    "constexpr std::pair<BidirIterType1, BidirIterType2> "
    "copy_backward_while_false(const BidirIterType1 src_first, BidirIterType1 "
    "src_last, BidirIterType2 dst_last, Predicate p) noexcept(boolean "
    "expression)",
    "Testing global function template copy_backward_while_false") {
  const vector<int> src1{};
  vector<int> dst1(src1.size(), 0);
  const vector<int> expected_numbers1{};

  const auto iter_pair1 =
      copy_backward_while_false(cbegin(src1), cend(src1), end(dst1),
                                [](const auto n) { return n % 2 == 0; });

  REQUIRE(0U == dst1.size());
  REQUIRE(expected_numbers1 == dst1);
  REQUIRE(iter_pair1.first == cend(src1));
  REQUIRE(iter_pair1.second == end(dst1));

  const vector<int> src2{0, 2, 4, 6, 7, 8, 10, 11, 12, 14};
  vector<int> dst2(src2.size(), 0);
  const vector<int> expected_numbers2{dst2};

  const auto iter_pair2 =
      copy_backward_while_false(cbegin(src2), cend(src2), end(dst2),
                                [](const auto n) { return n % 2 == 0; });

  REQUIRE(src2.size() == dst2.size());
  REQUIRE(expected_numbers2 == dst2);
  REQUIRE(iter_pair2.first == cend(src2));
  REQUIRE(iter_pair2.second == end(dst2));

  const vector<int> src3{0, 2, 4, 6, 7, 8, 10, 11, 12, 14, 16};
  vector<int> dst3(src3.size(), 0);
  const vector<int> expected_numbers3{0, 0, 0, 0, 0, 0, 0, 0, 12, 14, 16};

  const auto iter_pair3 =
      copy_backward_while_false(cbegin(src3), cend(src3), end(dst3),
                                [](const auto n) { return n % 2 == 1; });

  REQUIRE(src3.size() == dst3.size());
  REQUIRE(vector<int>(iter_pair3.first, cend(src3)) ==
          vector<int>(iter_pair3.second, end(dst3)));
  REQUIRE(expected_numbers3 == dst3);
  REQUIRE(iter_pair3.first != cend(src3));
  REQUIRE(*(iter_pair3.first) == 12);
  REQUIRE(*(iter_pair3.second) == 12);
}

TEST_CASE(
    "constexpr std::pair<ForwardIterType1, ForwardIterType2> "
    "move_forward_while_true(ForwardIterType1 src_first, const "
    "ForwardIterType1 src_last, ForwardIterType2 dst_first, Predicate p) "
    "noexcept(boolean expression)",
    "Testing global function template move_forward_while_true") {
  const vector<string> src1{};
  vector<string> dst1{};
  const vector<string> expected_numbers1{};

  const auto iter_pair1 = move_forward_while_true(
      cbegin(src1), cend(src1), back_inserter(dst1),
      [](const auto& n) { return !n.empty() && n.back() % 2 == 1; });

  REQUIRE(0U == dst1.size());
  REQUIRE(expected_numbers1 == dst1);
  REQUIRE(iter_pair1.first == cend(src1));

  const vector<string> src2{"0", "2",  "4",  "6",  "7",
                            "8", "10", "11", "12", "14"};
  vector<string> dst2{};
  const vector<string> expected_numbers2{};

  const auto iter_pair2 = move_forward_while_true(
      cbegin(src2), cend(src2), back_inserter(dst2),
      [](const auto& n) { return !n.empty() && n.back() % 2 == 1; });

  REQUIRE(0U == dst2.size());
  REQUIRE(expected_numbers2 == dst2);
  REQUIRE(iter_pair2.first == cbegin(src2));
  REQUIRE(*(iter_pair2.first) == "0");

  const vector<string> src3{"0", "2",  "4",  "6",  "7",
                            "8", "10", "11", "12", "14"};
  vector<string> dst3{};
  const vector<string> expected_numbers3{"0", "2", "4", "6"};

  const auto iter_pair3 = move_forward_while_true(
      cbegin(src3), cend(src3), back_inserter(dst3),
      [](const auto& n) { return !n.empty() && n.back() % 2 == 0; });

  REQUIRE(4U == dst3.size());
  REQUIRE(expected_numbers3 == dst3);
  REQUIRE(iter_pair3.first != cend(src3));
  REQUIRE(*(iter_pair3.first) == "7");
}

TEST_CASE(
    "constexpr std::pair<ForwardIterType1, ForwardIterType2> "
    "move_forward_while_false(ForwardIterType1 src_first, const "
    "ForwardIterType1 src_last, ForwardIterType2 dst_first, Predicate p) "
    "noexcept(boolean expression)",
    "Testing global function template move_forward_while_false") {
  const vector<string> src1{};
  vector<string> dst1{};
  const vector<string> expected_numbers1{};

  const auto iter_pair1 = move_forward_while_false(
      cbegin(src1), cend(src1), back_inserter(dst1),
      [](const auto& n) { return !n.empty() && n.back() % 2 == 0; });

  REQUIRE(0U == dst1.size());
  REQUIRE(expected_numbers1 == dst1);
  REQUIRE(iter_pair1.first == cend(src1));

  const vector<string> src2{"0", "2",  "4",  "6",  "7",
                            "8", "10", "11", "12", "14"};
  vector<string> dst2{};
  const vector<string> expected_numbers2{};

  const auto iter_pair2 = move_forward_while_false(
      cbegin(src2), cend(src2), back_inserter(dst2),
      [](const auto& n) { return !n.empty() && n.back() % 2 == 0; });

  REQUIRE(0U == dst2.size());
  REQUIRE(expected_numbers2 == dst2);
  REQUIRE(iter_pair2.first == cbegin(src2));
  REQUIRE(*(iter_pair2.first) == "0");

  const vector<string> src3{"0", "2",  "4",  "6",  "7",
                            "8", "10", "11", "12", "14"};
  vector<string> dst3{};
  const vector<string> expected_numbers3{"0", "2", "4", "6"};

  const auto iter_pair3 = move_forward_while_false(
      cbegin(src3), cend(src3), back_inserter(dst3),
      [](const auto& n) { return !n.empty() && n.back() % 2 == 1; });

  REQUIRE(4U == dst3.size());
  REQUIRE(expected_numbers3 == dst3);
  REQUIRE(iter_pair3.first != cend(src3));
  REQUIRE(*(iter_pair3.first) == "7");
}

TEST_CASE(
    "constexpr std::pair<BidirIterType1, BidirIterType2> "
    "move_backward_while_true(const BidirIterType1 src_first, BidirIterType1 "
    "src_last, BidirIterType2 dst_last, Predicate p) noexcept(boolean "
    "expression)",
    "Testing global function template move_backward_while_true") {
  const vector<string> src1{};
  vector<string> dst1{src1};
  const vector<string> expected_numbers1{};

  const auto iter_pair1 = move_backward_while_true(
      cbegin(src1), cend(src1), end(dst1),
      [](const auto n) { return !n.empty() && n.back() % 2 == 1; });

  REQUIRE(0U == dst1.size());
  REQUIRE(expected_numbers1 == dst1);
  REQUIRE(iter_pair1.first == cend(src1));
  REQUIRE(iter_pair1.second == end(dst1));

  const vector<string> src2{"0", "2",  "4",  "6",  "7",
                            "8", "10", "11", "12", "14"};
  vector<string> dst2(src2.size(), "");
  const vector<string> expected_numbers2{dst2};

  const auto iter_pair2 = move_backward_while_true(
      cbegin(src2), cend(src2), end(dst2),
      [](const auto n) { return !n.empty() && n.back() % 2 == 1; });

  REQUIRE(src2.size() == dst2.size());
  REQUIRE(expected_numbers2 == dst2);
  REQUIRE(iter_pair2.first == cend(src2));
  REQUIRE(iter_pair2.second == end(dst2));

  const vector<string> src3{"0",  "2",  "4",  "6",  "7", "8",
                            "10", "11", "12", "14", "16"};
  vector<string> dst3(src3.size(), "0");
  const vector<string> expected_numbers3{"0", "0", "0",  "0",  "0", "0",
                                         "0", "0", "12", "14", "16"};

  const auto iter_pair3 = move_backward_while_true(
      cbegin(src3), cend(src3), end(dst3),
      [](const auto n) { return !n.empty() && n.back() % 2 == 0; });

  REQUIRE(src3.size() == dst3.size());
  REQUIRE(vector<string>(iter_pair3.first, cend(src3)) ==
          vector<string>(iter_pair3.second, end(dst3)));
  REQUIRE(expected_numbers3 == dst3);
  REQUIRE(iter_pair3.first != cend(src3));
  REQUIRE(*(iter_pair3.first) == "12");
  REQUIRE(*(iter_pair3.second) == "12");
}

TEST_CASE(
    "constexpr std::pair<BidirIterType1, BidirIterType2> "
    "move_backward_while_false(const BidirIterType1 src_first, BidirIterType1 "
    "src_last, BidirIterType2 dst_last, Predicate p) noexcept(boolean "
    "expression)",
    "Testing global function template move_backward_while_false") {
  const vector<string> src1{};
  vector<string> dst1{src1};
  const vector<string> expected_numbers1{};

  const auto iter_pair1 = move_backward_while_false(
      cbegin(src1), cend(src1), end(dst1),
      [](const auto n) { return !n.empty() && n.back() % 2 == 0; });

  REQUIRE(0U == dst1.size());
  REQUIRE(expected_numbers1 == dst1);
  REQUIRE(iter_pair1.first == cend(src1));
  REQUIRE(iter_pair1.second == end(dst1));

  const vector<string> src2{"0", "2",  "4",  "6",  "7",
                            "8", "10", "11", "12", "14"};
  vector<string> dst2(src2.size(), "");
  const vector<string> expected_numbers2{dst2};

  const auto iter_pair2 = move_backward_while_false(
      cbegin(src2), cend(src2), end(dst2),
      [](const auto n) { return !n.empty() && n.back() % 2 == 0; });

  REQUIRE(src2.size() == dst2.size());
  REQUIRE(expected_numbers2 == dst2);
  REQUIRE(iter_pair2.first == cend(src2));
  REQUIRE(iter_pair2.second == end(dst2));

  const vector<string> src3{"0",  "2",  "4",  "6",  "7", "8",
                            "10", "11", "12", "14", "16"};
  vector<string> dst3(src3.size(), "0");
  const vector<string> expected_numbers3{"0", "0", "0",  "0",  "0", "0",
                                         "0", "0", "12", "14", "16"};

  const auto iter_pair3 = move_backward_while_false(
      cbegin(src3), cend(src3), end(dst3),
      [](const auto n) { return !n.empty() && n.back() % 2 == 1; });

  REQUIRE(src3.size() == dst3.size());
  REQUIRE(vector<string>(iter_pair3.first, cend(src3)) ==
          vector<string>(iter_pair3.second, end(dst3)));
  REQUIRE(expected_numbers3 == dst3);
  REQUIRE(iter_pair3.first != cend(src3));
  REQUIRE(*(iter_pair3.first) == "12");
  REQUIRE(*(iter_pair3.second) == "12");
}

TEST_CASE("void tracer::operator()(const char* format, Args&&... args) const",
          "Testing custom tracer struct's operator() member function") {
  ostringstream oss1;
  ostringstream oss2;

  const char* file_name{__FILE__};
  const size_t line_number{__LINE__};

  oss1 << file_name << " (line no.: " << line_number
       << ") -> Printing Hello World to stdout.";

  const string oss2_str{
      tracer{oss2, file_name, line_number}("Printing Hello World to stdout.")};

  REQUIRE(oss1.str() == oss2_str);
}

TEST_CASE(
    "BidirIterType stable_partition(BidirIterType first, BidirIterType last, "
    "UnaryPredicate p)",
    "Testing global function template stl::helper::stable_partition") {
  std::srand(std::time(nullptr));

  std::vector<int> vec{1, 0, -1, -3, -2, 2, 8, 3, 5, -7, 4, -9, 7, -10};
  std::vector<int> vec_copy{vec};

  const auto vec_last = std::stable_partition(
      std::begin(vec), std::end(vec), [](const int n) { return n > 0; });
  const auto vec_copy_last =
      stl::helper::stable_partition(std::begin(vec_copy), std::end(vec_copy),
                                    [](const int n) { return n > 0; });

  REQUIRE(std::equal(std::begin(vec), vec_last, std::begin(vec_copy),
                     vec_copy_last));
  REQUIRE((std::vector<int>(std::begin(vec), vec_last) ==
           std::vector<int>{1, 2, 8, 3, 5, 4, 7}));
  REQUIRE((std::vector<int>(std::begin(vec_copy), vec_copy_last) ==
           std::vector<int>{1, 2, 8, 3, 5, 4, 7}));

  std::vector<int> vec1{};
  REQUIRE(std::end(vec1) ==
          stl::helper::stable_partition(std::begin(vec1), std::end(vec1),
                                        [](const int n) { return n > 0; }));

  std::vector<int> vec2{-8};
  REQUIRE(std::end(vec2) ==
          stl::helper::stable_partition(std::begin(vec2), std::end(vec2),
                                        [](const int n) { return n > 0; }));

  std::vector<int> vec3{8};
  REQUIRE(std::end(vec3) ==
          stl::helper::stable_partition(std::begin(vec3), std::end(vec3),
                                        [](const int n) { return n > 0; }));

  const int number_of_test_cases = 10 + std::rand() % 100;

  for (int i{}; i < number_of_test_cases; ++i) {
    std::vector<int> vec4{generate_sequence_of_random_values(
        -1000, 1000, 10 + std::rand() % 1000)};
    std::vector<int> vec4_copy{vec4};

    const auto vec4_last = std::stable_partition(
        std::begin(vec4), std::end(vec4), [](const int n) { return n > 0; });
    const auto vec4_copy_last = stl::helper::stable_partition(
        std::begin(vec4_copy), std::end(vec4_copy),
        [](const int n) { return n > 0; });

    REQUIRE(std::equal(std::begin(vec4), vec4_last, std::begin(vec4_copy),
                       vec4_copy_last));
  }
}

TEST_CASE(
    "std::pair<BidirIterType, BidirIterType> stable_gather(BidirIterType "
    "first, BidirIterType last, const BidirIterType target, BinaryPredicate p",
    "Testing global function template stl::helper::stable_gather") {
  std::srand(std::time(nullptr));

  std::vector<int> vec_b1{};

  const auto target_iter_b1 =
      std::find(std::begin(vec_b1), std::end(vec_b1), 8);

  const auto [vec_first_b1, vec_last_b1] = stl::helper::stable_gather(
      std::begin(vec_b1), std::end(vec_b1), target_iter_b1,
      [](const int x, const int y) { return std::abs(x - y) <= 5; });

  REQUIRE(vec_first_b1 == std::begin(vec_b1));
  REQUIRE(std::begin(vec_b1) == vec_last_b1);
  REQUIRE(vec_last_b1 == std::end(vec_b1));

  std::vector<int> vec_b2{1};

  const auto target_iter_b2 =
      std::find(std::begin(vec_b2), std::end(vec_b2), 1);

  const auto [vec_first_b2, vec_last_b2] = stl::helper::stable_gather(
      std::begin(vec_b2), std::end(vec_b2), target_iter_b2,
      [](const int x, const int y) { return std::abs(x - y) <= 5; });

  REQUIRE(vec_first_b2 == std::begin(vec_b2));
  REQUIRE(vec_last_b2 == std::end(vec_b2));

  const auto target_iter_b3 =
      std::find(std::begin(vec_b2), std::end(vec_b2), 8);

  const auto [vec_first_b3, vec_last_b3] = stl::helper::stable_gather(
      std::begin(vec_b2), std::end(vec_b2), target_iter_b3,
      [](const int x, const int y) { return std::abs(x - y) <= 5; });

  REQUIRE(vec_first_b3 == vec_last_b3);
  REQUIRE(vec_first_b3 == std::end(vec_b2));

  std::vector<int> vec{1, 0, -1, -3, -2, 2, 8, 3, 5, -7, 4, -9, 7, -10};
  std::vector<int> vec2{vec};

  const auto target_iter1 = std::find(std::begin(vec), std::end(vec), 8);

  const auto [vec_first1, vec_last1] = stl::helper::stable_gather(
      std::begin(vec), std::end(vec), target_iter1,
      [](const int x, const int y) { return std::abs(x - y) <= 5; });

  REQUIRE((std::vector<int>(vec_first1, vec_last1) ==
           std::vector<int>{8, 3, 5, 4, 7}));

  const auto target_iter2 = std::find(std::begin(vec2), std::end(vec2), 8);
  const auto target_value = 8;

  const auto vec_first2 = std::stable_partition(
      std::begin(vec2), target_iter2,
      [&](const auto n) { return !(std::abs(n - target_value) <= 5); });

  const auto vec_last2 = std::stable_partition(
      target_iter2, std::end(vec2),
      [&](const auto n) { return std::abs(n - target_value) <= 5; });

  REQUIRE(std::equal(vec_first1, vec_last1, vec_first2, vec_last2));

  const int number_of_test_cases = 10 + std::rand() % 100;

  for (int i{}; i < number_of_test_cases; ++i) {
    std::vector<int> vec{generate_sequence_of_random_values(
        -1000, 1000, 10 + std::rand() % 1000)};

    const auto offset = std::rand() % (vec.size() - 1);

    const auto target_iter1 = std::begin(vec) + offset;

    const int target = *target_iter1;
    const int low = target - std::rand() % 100;
    const int high = target + std::rand() % 100;

    std::vector<int> vec_copy{vec};
    const auto target_iter2 = std::begin(vec_copy) + offset;

    const auto [vec_first1, vec_last1] = stl::helper::stable_gather(
        std::begin(vec), std::end(vec), target_iter1,
        [&](const auto x, const auto y) {
          const auto min_element = std::min(x, y);
          const auto max_element = std::max(x, y);
          return min_element >= low && max_element <= high;
        });

    const auto vec_first2 = std::stable_partition(
        std::begin(vec_copy), target_iter2, [&](const auto n) {
          const auto min_element = std::min(n, target);
          const auto max_element = std::max(n, target);
          return !(min_element >= low && max_element <= high);
        });

    const auto vec_last2 = std::stable_partition(
        target_iter2, std::end(vec_copy), [&](const auto n) {
          const auto min_element = std::min(target, n);
          const auto max_element = std::max(target, n);
          return min_element >= low && max_element <= high;
        });

    REQUIRE(std::equal(vec_first1, vec_last1, vec_first2, vec_last2));
  }
}
