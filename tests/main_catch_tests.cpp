#define CATCH_CONFIG_MAIN

#include "..\include\catch.hpp"
#include "..\include\stl_helper_functions.hpp"

#if defined(_MSC_VER)
#include <crtdbg.h>
#define ASSERT _ASSERTE_
#else
#include <cassert>
#define ASSERT assert
#endif

#include <chrono>
#include <cstring>
#include <iterator>
#include <map>
#include <random>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;
using namespace std::chrono;
using namespace std::string_literals;
using namespace stl::helper;

long long get_random_number(const long long lower_bound,
                            const long long upper_bound) {
  static mt19937 rand_engine{static_cast<unsigned>(
      high_resolution_clock::now().time_since_epoch().count())};
  static uniform_int_distribution<long long> num_distr{lower_bound,
                                                       upper_bound};

  return num_distr(rand_engine);
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

TEST_CASE("void swap(T& first, T& second)",
          "Testing global function template void swap(T& first, T& second)") {
  struct no_move_type {
    int id;
    no_move_type(const int id_num = -1) : id{id_num} {}
    no_move_type(no_move_type const&) = default;
    no_move_type& operator=(no_move_type const&) = default;
    no_move_type(no_move_type&&) = delete;
    no_move_type& operator=(no_move_type&&) = delete;
  };

  string first{"first"}, second{"second"};
  REQUIRE(first == "first"s);
  REQUIRE(second == "second"s);
  stl::helper::swap(first, second);
  REQUIRE(first == "second"s);
  REQUIRE(second == "first"s);

  no_move_type a{1}, b{2};
  REQUIRE(1 == a.id);
  REQUIRE(2 == b.id);
  stl::helper::swap(a, b);
  REQUIRE(2 == a.id);
  REQUIRE(1 == b.id);
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
TEST_CASE("1. split function template",
          "std::vector<std::basic_string<char_type>> split(const T& src, const "
          "U& needle, const bool split_on_whole_needle = true, const bool "
          "ignore_empty_string = true, const size_t max_count = "
          "std::basic_string<char_type>::npos)") {
  const char* source{"apple|banana|cabbage|lemon|orange|pepper|plum"};
  const auto parts{split(source, '|', true)};

  REQUIRE(parts.front() == "apple");

  REQUIRE(parts[3] == "lemon");

  REQUIRE(parts.back() == "plum");
}

TEST_CASE("2. split function template",
          "std::vector<std::basic_string<typename "
          "std::iterator_traits<IteratorType>::value_type>> split(IteratorType "
          "first,teratorType last, const NeedleType& needle, const bool "
          "split_on_whole_needle = true, const bool ignore_empty_string = "
          "true, const size_t max_count = std::numeric_limits<size_t>::max()") {
  const wstring source{L"apple|banana|cabbage|lemon|orange|pepper|plum"};
  const auto parts{split(cbegin(source), cend(source), L'|', true)};

  REQUIRE(parts.front() == L"apple");

  REQUIRE(parts[3] == L"lemon");

  REQUIRE(parts.back() == L"plum");
}

TEST_CASE(
    "3. split function template",
    "std::vector<std::pair<SrcIterType, SrcIterType>> split(const SrcIterType "
    "src_first, const SrcIterType src_last, const DstIterType needle_first, "
    "const DstIterType needle_last, const bool split_on_whole_sequence = true, "
    "const bool ignore_empty_sequence = true, const size_t max_count = "
    "std::numeric_limits<size_t>::max())") {
  const u32string source{
      U"apple|-|banana|-|cabbage|-|lemon|-|orange|-|pepper|-|plum"};
  const char32_t needle[]{U"|-|"};

  const auto parts{
      split(cbegin(source), cend(source), cbegin(needle), cend(needle), true)};

  REQUIRE(parts.front() == U"apple");

  REQUIRE(parts[3] == U"lemon");

  REQUIRE(parts.back() == U"plum");
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

// TEST_CASE(
//    "typename StringType::size_type index_of(const StringType& text,
// const typename StringType::value_type needle_char, const size_t start_pos =
// 0u, bool ignore_case = false,\ const std::locale& loc = std::locale{})"
//    ,
//    "Testing global template function typename StringType::size_type
// index_of(const StringType& text, const typename StringType::value_type
// needle_char, const size_t start_pos = 0u, bool ignore_case = false,\ const
// std::locale& loc = std::locale{})"
//)
//{
//    const wstring
// src{L"apple,banana,cabbage,lemon,orange,pepper,plum"};
//
//    wstring::size_type correct_index = src.find(L'b');
//
//    REQUIRE(index_of(src, L'b') == correct_index);
//
//    correct_index = src.find(L'b');
//
//    REQUIRE(index_of(src, L'B', 0, true) == correct_index);
//}
//
// TEST_CASE(
//    "typename StringType::size_type index_of(const StringType& text,
// const typename StringType::const_pointer needle, const size_t start_pos = 0u,
// bool ignore_case = false,\ const std::locale& loc = std::locale{})"
//    ,
//    "Testing global template function typename StringType::size_type
// index_of(const StringType& text, const typename StringType::const_pointer
// needle, const size_t start_pos = 0u, bool ignore_case = false,\ const
// std::locale& loc = std::locale{})"
//)
//{
//    const wstring
// src{L"apple,banana,cabbage,lemon,orange,pepper,plum"};
//
//    wstring::size_type correct_index = src.find(L"banana");
//
//    REQUIRE(index_of(src, L"banana") == correct_index);
//
//    correct_index = src.find(L"cabbage");
//
//    REQUIRE(index_of(src, L"CaBbaGE", 0, true) == correct_index);
//}
//
// TEST_CASE(
//    "typename StringType::size_type index_of(const StringType& text,
// const StringType& needle, bool ignore_case = false, const std::locale& loc =
// std::locale{})"
//    ,
//    "Testing global template function typename StringType::size_type
// index_of(const StringType& text, const StringType& needle, bool ignore_case =
// false, const std::locale& loc = std::locale{})"
//)
//{
//    const wstring
// src{L"apple,banana,cabbage,lemon,orange,pepper,plum"};
//
//    const wstring needle{L"banana"};
//
//    wstring::size_type correct_index = src.find(needle);
//
//    REQUIRE(index_of(src, needle) == correct_index);
//
//    correct_index = src.find(L"cabbage");
//
//    REQUIRE(index_of(src, wstring{ L"cabbage" }) == correct_index);
//
//    REQUIRE(index_of(src, wstring{ L"CaBbaGe" }, 0, true) ==
// correct_index);
//}
//
// TEST_CASE(
//    "bool contains(const StringType& text, const typename
// StringType::value_type needle_char, const size_t start_pos = 0u, bool
// ignore_case = false, const std::locale& loc = std::locale{})"
//    ,
//    "Testing global template function bool contains(const
// StringType& text, const typename StringType::value_type needle_char, const
// size_t
// start_pos = 0u,bool ignore_case = false, const std::locale& loc =
// std::locale{})"
//)
//{
//    const wstring
// src{L"apple,banana,cabbage,lemon,orange,pepper,plum"};
//
//    REQUIRE(contains(src, L'b'));
//
//    REQUIRE(!contains(src, L'x'));
//
//    REQUIRE(contains(src, L'B', 0, true));
//
//    REQUIRE(!contains(src, L'X', 0, true));
//}
//
// TEST_CASE(
//    "bool contains(const StringType& text, typename
// StringType::const_pointer needle, const size_t start_pos = 0u, bool
// ignore_case = false, const std::locale& loc = std::locale{})"
//    ,
//    "Testing global template function bool contains(const
// StringType& text, typename StringType::const_pointer needle, const size_t
// start_pos = 0u,
// bool ignore_case = false, const std::locale& loc = std::locale{})"
//)
//{
//    const wstring
// src{L"apple,banana,cabbage,lemon,orange,pepper,plum"};
//
//    REQUIRE(contains(src, L"banana"));
//
//    REQUIRE(contains(src, L"CaBbaGE", 0, true));
//
//    REQUIRE(!contains(src, L"pear"));
//
//    REQUIRE(!contains(src, L"PEAR", 0, true));
//}
//
// TEST_CASE(
//    "bool contains(const StringType& text, const StringType& needle,
// bool ignore_case = false, const std::locale& loc = std::locale{})"
//    ,
//    "Testing global template function bool contains(const
// StringType& text, const StringType& needle, bool ignore_case = false, const
// std::locale&
// loc = std::locale{})"
//)
//{
//    const wstring
// src{L"apple,banana,cabbage,lemon,orange,pepper,plum"};
//
//    const wstring needle{L"banana"};
//
//    REQUIRE(contains(src, needle));
//
//    REQUIRE(contains(src, wstring{L"CaBbAgE"}, true));
//
//    REQUIRE(!contains(src, wstring{ L"pear" }));
//}
//
// TEST_CASE(
//    "bool ends_with(const StringType& text, const typename
// StringType::value_type end_char, bool ignore_case = false, const std::locale&
// loc = std::locale{})"
//    ,
//    "Testing global template function bool ends_with(const
// StringType& text, const typename StringType::value_type end_char, bool
// ignore_case =
// false, const std::locale& loc = std::locale{})"
//)
//{
//    const wstring src{L"Apples"};
//
//    REQUIRE(ends_with(src, L's'));
//
//    REQUIRE(ends_with(src, L'S', true));
//}
//
// TEST_CASE(
//    "bool ends_with(const StringType& src, const typename
// StringType::const_pointer end_tag, bool ignore_case = false, const
// std::locale& loc = std::locale{})"
//    ,
//    "Testing global template function bool ends_with(const
// StringType& src, const typename StringType::const_pointer end_tag, bool
// ignore_case =
// false, const std::locale& loc = std::locale{})"
//)
//{
//    const u32string src{U"Apple is one my favorite, most beloved
// fruits."};
//
//    REQUIRE(ends_with(src, U"fruits."));
//
//    REQUIRE(ends_with(src, U"FrUiTs.", true));
//}
//
// TEST_CASE(
//    "bool ends_with(const StringType& src, const StringType&
// end_tag, bool ignore_case = false, const std::locale& loc = std::locale{})"
//    ,
//    "Testing global template function bool ends_with(const
// StringType& src, const StringType& end_tag, bool ignore_case = false, const
// std::locale&
// loc = std::locale{})"
//)
//{
//    const u32string src{U"Apple is one my favorite, most beloved
// fruits."};
//
//    const u32string needle{U"fruits."};
//
//    REQUIRE(ends_with(src, needle));
//
//    REQUIRE(ends_with(src, u32string{ U"FrUiTs." }, true));
//}
//
// TEST_CASE("void unused_args(Args&&... args)",
//    "Testing global template function void unused_args(Args&&...
// args)")
//{
//    const int number{42};
//
//    const wchar_t* important_message = L"Number 42 is the meaning of
// life.";
//
//    struct NumberInfo
//    {
//        NumberInfo() : number{42}, message{L"Number 42
// is the meaning of life."}
//        {
//        }
//
//        NumberInfo(const int num, const wchar_t* msg) :
// number{num}, message{msg}
//        {
//        }
//
//        const int number;
//
//        const wchar_t* message;
//    } num_info;
//
//    unused_args(number, important_message, num_info);
//}
//
// TEST_CASE("bool has_key(const map<KeyType, ValueType>& container, const
// typename map<KeyType, ValueType>::key_type& key)", "Testing global template
// function bool has_key(const map<KeyType, ValueType>& container, const
// typename map<KeyType, ValueType>::key_type& key)")
//{
//    const wstring
// src{L"apple:10:banana:20:cabbage:30:lemon:40:orange:50:pepper:60:plum:70"};
//
//    const auto parts{split(src, L':')};
//
//    const map<wstring, size_t> fruit_count = [&]()
//    {
//        map<wstring, size_t> fruits{};
//
//        for (size_t i = 0; i < parts.size(); i += 2)
//        {
//            fruits[parts[i]] = stoul(parts[i
//+ 1]);
//        }
//
//        return fruits;
//    }();
//
//    const vector<wstring> random_fruits{
//        L"apple", L"apricot", L"banana", L"orange",
// L"grapefruit", L"lemon", L"pear", L"pineapple", L"plum", L"walnut"
//    };
//
//    mt19937 rand_engine{rd()};
//
//    auto const num_distr = uniform_int_distribution<unsigned>(0,
// random_fruits.size() - 1);
//
//    const auto random_fruit{random_fruits[num_distr(rand_engine)]};
//
//    if (fruit_count.find(random_fruit) != cend(fruit_count))
//    {
//        REQUIRE(has_key(fruit_count, random_fruit));
//    }
//    else
//    {
//        REQUIRE(!has_key(fruit_count, random_fruit));
//    }
//
//    REQUIRE(has_key(fruit_count, wstring{ L"orange" }));
//
//    REQUIRE(!has_key(fruit_count, L"grapefruit"));
//}
//
// TEST_CASE("bool has_key(map<KeyType, ValueType>& container, const typename
// map<KeyType, ValueType>::key_type& key)", "Testing global template function
// bool has_key(map<KeyType, ValueType>& container, const typename map<KeyType,
// ValueType>::key_type& key)")
//{
//    const wstring src{
// L"apple:10:banana:20:cabbage:30:lemon:40:orange:50:pepper:60:plum:70" };
//
//    const auto parts{ split(src, L':') };
//
//    auto fruit_count = map<wstring, size_t>{};
//
//    for (size_t i = 0; i < parts.size(); i += 2)
//    {
//        fruit_count[parts[i]] = std::stoul(parts[i +
// 1]);
//    }
//
//    const vector<wstring> random_fruits{
//        L"apple", L"apricot", L"banana", L"orange",
// L"grapefruit", L"lemon", L"pear", L"pineapple", L"plum", L"walnut"
//    };
//
//    mt19937 rand_engine{ rd() };
//
//    auto const num_distr = uniform_int_distribution<unsigned>(0,
// random_fruits.size() - 1);
//
//    const auto random_fruit{ random_fruits[num_distr(rand_engine)]
//};
//
//    if (fruit_count.find(random_fruit) != end(fruit_count))
//    {
//        REQUIRE(has_key(fruit_count, random_fruit));
//    }
//    else
//    {
//        REQUIRE(!has_key(fruit_count, random_fruit));
//    }
//
//    REQUIRE(has_key(fruit_count, L"orange"));
//
//    REQUIRE(!has_key(fruit_count, L"grapefruit"));
//}
//
// TEST_CASE("bool has_key(const multimap<KeyType, ValueType>& container, const
// typename multimap<KeyType, ValueType>::key_type& key)", "Testing global
// template function bool has_key(const multimap<KeyType, ValueType>& container,
// const typename multimap<KeyType, ValueType>::key_type& key)")
//{
//    const wstring
// src{L"apple:10:banana:20:cherries:30:lemon:40:orange:50:pepper:60:plum:70"};
//
//    const auto parts{split(src, L':')};
//
//    const multimap<wstring, size_t> fruit_count = [&]()
//    {
//        multimap<wstring, size_t> fruits{};
//
//        for (size_t i = 0; i < parts.size(); i += 2)
//        {
//            fruits.insert(make_pair(parts[i],
// stoul(parts[i + 1])));
//        }
//
//        return fruits;
//    }();
//
//    const vector<wstring> random_fruits{
//        L"apple", L"apricot", L"banana", L"orange",
// L"grapefruit", L"lemon", L"pear", L"pineapple", L"plum", L"walnut"
//    };
//
//    mt19937 rand_engine{rd()};
//
//    auto const num_distr = uniform_int_distribution<unsigned>(0,
// random_fruits.size() - 1);
//
//    const auto random_fruit{random_fruits[num_distr(rand_engine)]};
//
//    if (fruit_count.find(random_fruit) != cend(fruit_count))
//    {
//        REQUIRE(has_key(fruit_count, random_fruit));
//    }
//    else
//    {
//        REQUIRE(!has_key(fruit_count, random_fruit));
//    }
//
//    REQUIRE(has_key(fruit_count, wstring{ L"orange" }));
//
//    REQUIRE(!has_key(fruit_count, wstring{ L"grapefruit" }));
//}
//
// TEST_CASE("bool has_key(multimap<KeyType, ValueType>& container, const
// typename multimap<KeyType, ValueType>::key_type& key)", "Testing global
// template function bool has_key(multimap<KeyType, ValueType>& container, const
// typename multimap<KeyType, ValueType>::key_type& key)")
//{
//    const wstring src{
// L"apple:10:banana:20:cherries:30:lemon:40:orange:50:pepper:60:plum:70" };
//
//    const auto parts{ split(src, L':') };
//
//
//    auto fruit_count = multimap<wstring, size_t>{};
//
//    for (size_t i = 0; i < parts.size(); i += 2)
//    {
//        fruit_count.insert(make_pair(parts[i],
// stoul(parts[i
//+ 1])));
//    }
//
//    const vector<wstring> random_fruits{
//        L"apple", L"apricot", L"banana", L"orange",
// L"grapefruit", L"lemon", L"pear", L"pineapple", L"plum", L"walnut"
//    };
//
//    mt19937 rand_engine{ rd() };
//
//    auto const num_distr = uniform_int_distribution<unsigned>(0,
// random_fruits.size() - 1);
//
//    const auto random_fruit{ random_fruits[num_distr(rand_engine)]
//};
//
//    if (fruit_count.find(random_fruit) != end(fruit_count))
//    {
//        REQUIRE(has_key(fruit_count, random_fruit));
//    }
//    else
//    {
//        REQUIRE(!has_key(fruit_count, random_fruit));
//    }
//
//    REQUIRE(has_key(fruit_count, wstring{ L"orange" }));
//
//    REQUIRE(!has_key(fruit_count, wstring{ L"grapefruit" }));
//}
//
//
// TEST_CASE("bool has_key(const unordered_map<KeyType, ValueType>& container,
// const typename unordered_map<KeyType, ValueType>::key_type& key)", "Testing
// global template function bool has_key(const unordered_map<KeyType,
// ValueType>& container, const typename unordered_map<KeyType,
// ValueType>::key_type& key)"
//)
//{
//    const wstring
// src{L"apple:10:banana:20:cabbage:30:lemon:40:orange:50:pepper:60:plum:70"};
//
//    const auto parts{split(src, L':')};
//
//    const unordered_map<wstring, size_t> fruit_count = [&]()
//    {
//        unordered_map<wstring, size_t> fruits{};
//
//        for (size_t i = 0; i < parts.size(); i += 2)
//        {
//            fruits[parts[i]] = stoul(parts[i
//+ 1]);
//        }
//
//        return fruits;
//    }();
//
//    const vector<wstring> random_fruits{
//        L"apple", L"apricot", L"banana", L"orange",
// L"grapefruit", L"lemon", L"pear", L"pineapple", L"plum", L"walnut"
//    };
//
//    mt19937 rand_engine{rd()};
//
//    auto const num_distr = uniform_int_distribution<unsigned>(0,
// random_fruits.size() - 1);
//
//    const auto random_fruit{random_fruits[num_distr(rand_engine)]};
//
//    if (fruit_count.find(random_fruit) != cend(fruit_count))
//    {
//        REQUIRE(has_key(fruit_count, random_fruit));
//    }
//    else
//    {
//        REQUIRE(!has_key(fruit_count, random_fruit));
//    }
//
//    REQUIRE(has_key(fruit_count, wstring{ L"orange" }));
//
//    REQUIRE(!has_key(fruit_count, L"grapefruit" ));
//}
//
// TEST_CASE("bool has_key(unordered_map<KeyType, ValueType>& container, const
// typename unordered_map<KeyType, ValueType>::key_type& key)", "Testing global
// template function bool has_key(unordered_map<KeyType, ValueType>& container,
// const typename unordered_map<KeyType, ValueType>::key_type& key)")
//{
//    const wstring src{
// L"apple:10:banana:20:cabbage:30:lemon:40:orange:50:pepper:60:plum:70" };
//
//    const auto parts{ split(src, L':') };
//
//    auto fruit_count = unordered_map<wstring, size_t>{};
//
//    for (size_t i = 0; i < parts.size(); i += 2)
//    {
//        fruit_count[parts[i]] = std::stoul(parts[i +
// 1]);
//    }
//
//    const vector<wstring> random_fruits{
//        L"apple", L"apricot", L"banana", L"orange",
// L"grapefruit", L"lemon", L"pear", L"pineapple", L"plum", L"walnut"
//    };
//
//    mt19937 rand_engine{ rd() };
//
//    auto const num_distr = uniform_int_distribution<unsigned>(0,
// random_fruits.size() - 1);
//
//    const auto random_fruit{ random_fruits[num_distr(rand_engine)]
//};
//
//    if (fruit_count.find(random_fruit) != end(fruit_count))
//    {
//        REQUIRE(has_key(fruit_count, random_fruit));
//    }
//    else
//    {
//        REQUIRE(!has_key(fruit_count, random_fruit));
//    }
//
//    REQUIRE(has_key(fruit_count, L"orange" ));
//
//    REQUIRE(!has_key(fruit_count, wstring{ L"grapefruit" }));
//}
//
//
// TEST_CASE("bool has_key(const unordered_multimap<KeyType, ValueType>&
// container, const typename unordered_multimap<KeyType, ValueType>::key_type&
// key)", "Testing global template function bool has_key(const
// unordered_multimap<KeyType, ValueType>& container, const typename
// unordered_multimap<KeyType, ValueType>::key_type& key)"
//)
//{
//    const wstring
// src{L"apple:10:banana:20:cabbage:30:lemon:40:orange:50:pepper:60:plum:70"};
//
//    const auto parts{split(src, L':')};
//
//    const unordered_multimap<wstring, size_t> fruit_count = [&]()
//    {
//        unordered_multimap<wstring, size_t> fruits{};
//
//        for (size_t i = 0; i < parts.size(); i += 2)
//        {
//            fruits.insert(make_pair(parts[i],
// stoul(parts[i + 1])));
//        }
//
//        return fruits;
//    }();
//
//    const vector<wstring> random_fruits{
//        L"apple", L"apricot", L"banana", L"orange",
// L"grapefruit", L"lemon", L"pear", L"pineapple", L"plum", L"walnut"
//    };
//
//    mt19937 rand_engine{rd()};
//
//    auto const num_distr = uniform_int_distribution<unsigned>(0,
// random_fruits.size() - 1);
//
//    const auto random_fruit{random_fruits[num_distr(rand_engine)]};
//
//    if (fruit_count.find(random_fruit) != cend(fruit_count))
//    {
//        REQUIRE(has_key(fruit_count, random_fruit));
//    }
//    else
//    {
//        REQUIRE(!has_key(fruit_count, random_fruit));
//    }
//
//    REQUIRE(has_key(fruit_count, wstring{ L"orange" }));
//
//    REQUIRE(!has_key(fruit_count, L"grapefruit" ));
//}
//
// TEST_CASE("bool has_key(unordered_multimap<KeyType, ValueType>& container,
// const typename unordered_multimap<KeyType, ValueType>::key_type& key)",
// "Testing global template function bool has_key(unordered_multimap<KeyType,
// ValueType>& container, const typename unordered_multimap<KeyType,
// ValueType>::key_type& key)")
//{
//    const wstring
// src{L"apple:10:banana:20:cabbage:30:lemon:40:orange:50:pepper:60:plum:70"};
//
//    const auto parts{split(src, L':')};
//
//    auto fruit_count = unordered_multimap<wstring, size_t>{};
//
//    for (size_t i = 0; i < parts.size(); i += 2)
//    {
//        fruit_count.insert(make_pair(parts[i],
// std::stoul(parts[i + 1])));
//    }
//
//    const vector<wstring> random_fruits{
//        L"apple", L"apricot", L"banana", L"orange",
// L"grapefruit", L"lemon", L"pear", L"pineapple", L"plum", L"walnut"
//    };
//
//    mt19937 rand_engine{rd()};
//
//    auto const num_distr = uniform_int_distribution<unsigned>(0,
// random_fruits.size() - 1);
//
//    const auto random_fruit{random_fruits[num_distr(rand_engine)]};
//
//    if (fruit_count.find(random_fruit) != end(fruit_count))
//    {
//        REQUIRE(has_key(fruit_count, random_fruit));
//    }
//    else
//    {
//        REQUIRE(!has_key(fruit_count, random_fruit));
//    }
//
//    REQUIRE(has_key(fruit_count, wstring{ L"orange" }));
//
//    REQUIRE(!has_key(fruit_count, L"grapefruit" ));
//}
//
// TEST_CASE("bool has_value(const ContainerType& container, const typename
// ContainerType::value_type& search_value)", "Testing global template function
// bool has_value(const ContainerType& container, const typename
// ContainerType::value_type& search_value)"
//)
//{
//    const wstring
// src{L"apple:|:banana:|:cabbage:|:lemon:|:orange:|:pepper:|:pineapple:|:plum:|:walnut"};
//
//    const wstring needle{L":|:"};
//
//    const auto parts{split(src, needle)};
//
//    REQUIRE(has_value(parts, L"orange"));
//
//    REQUIRE(!has_value(parts, wstring{ L"grapefruit" }));
//
//    const vector<wstring> random_fruits{
//        L"apple", L"apricot", L"banana", L"orange",
// L"grapefruit", L"lemon", L"pear", L"pineapple", L"plum", L"walnut"
//    };
//
//    mt19937 rand_engine{rd()};
//
//    auto const num_distr = uniform_int_distribution<unsigned>(0,
// random_fruits.size() - 1);
//
//    const auto random_fruit{random_fruits[num_distr(rand_engine)]};
//
//    if (find(cbegin(parts), cend(parts), random_fruit) !=
// cend(parts))         REQUIRE(has_value(parts,
// random_fruit));
//
//    else
//        REQUIRE(!has_value(parts, random_fruit));
//}
//
// TEST_CASE("bool has_value(ContainerType& container, const typename
// ContainerType::value_type& search_value)", "Testing global template function
// bool has_value(ContainerType& container, const typename
// ContainerType::value_type& search_value)"
//)
//{
//    const wstring
// src{L"apple:|:banana:|:cabbage:|:lemon:|:orange:|:pepper:|:pineapple:|:plum:|:walnut"};
//
//    const wstring needle{L":|:"};
//
//    auto parts{split(src, needle)};
//
//    REQUIRE(has_value(parts, L"orange"));
//
//    REQUIRE(!has_value(parts, wstring{ L"grapefruit" }));
//
//    const vector<wstring> random_fruits{
//        L"apple", L"apricot", L"banana", L"orange",
// L"grapefruit", L"lemon", L"pear", L"pineapple", L"plum", L"walnut"
//    };
//
//    mt19937 rand_engine{rd()};
//
//    auto const num_distr = uniform_int_distribution<unsigned>(0,
// random_fruits.size() - 1);
//
//    const auto random_fruit{random_fruits[num_distr(rand_engine)]};
//
//    if (find(begin(parts), end(parts), random_fruit) != end(parts))
//        REQUIRE(has_value(parts, random_fruit));
//
//    else
//        REQUIRE(!has_value(parts, random_fruit));
//}
//
// TEST_CASE("bool has_key(const set<ValueType>& container, const typename
// set<ValueType>::key_type& item)", "Testing global template function bool
// has_key(const set<ValueType>& container, const typename
// set<ValueType>::key_type& item)")
//{
//    const wstring src{
//        L"apple:|:banana:|:cabbage:|:lemon:|:orange:|:pepper:|:pineapple:|:plum:|:walnut:|:lemon:|:apricot:|:plum"
//    };
//
//    const wstring needle{L":|:"};
//
//    const auto parts{split(src, needle)};
//
//    const set<wstring> all_fruits = [&]()
//    {
//        set<wstring> fruits{};
//
//        for (const auto& fruit : parts)
//        {
//            fruits.insert(fruit);
//        }
//
//        return fruits;
//    }();
//
//    REQUIRE(has_key(all_fruits, wstring{ L"orange" }));
//
//    REQUIRE(!has_key(all_fruits, L"grapefruit" ));
//
//    const vector<wstring> random_fruits{
//        L"apple", L"apricot", L"banana", L"orange",
// L"grapefruit", L"lemon", L"pear", L"pineapple", L"plum", L"walnut"
//    };
//
//    mt19937 rand_engine{rd()};
//
//    auto const num_distr = uniform_int_distribution<unsigned>(0,
// random_fruits.size() - 1);
//
//    const auto random_fruit{random_fruits[num_distr(rand_engine)]};
//
//    if (all_fruits.find(random_fruit) != cend(all_fruits))
//        REQUIRE(has_key(all_fruits, random_fruit));
//
//    else
//        REQUIRE(!has_key(all_fruits, random_fruit));
//}
//
// TEST_CASE("bool has_value(const multiset<ValueType>& container, const
// typename multiset<ValueType>::key_type& item)", "Testing global template
// function bool has_value(const multiset<ValueType>& container, const typename
// multiset<ValueType>::key_type& item)")
//{
//    const wstring src{
//        L"apple:|:banana:|:cabbage:|:lemon:|:orange:|:pepper:|:pineapple:|:plum:|:walnut:|:lemon:|:apricot:|:plum"
//    };
//
//    const wstring needle{L":|:"};
//
//    const auto parts{split(src, needle)};
//
//    const multiset<wstring> all_fruits = [&]()
//    {
//        multiset<wstring> fruits{};
//
//        for (const auto& fruit : parts)
//        {
//            fruits.insert(fruit);
//        }
//
//        return fruits;
//    }();
//
//    REQUIRE(has_key(all_fruits, wstring{ L"orange" }));
//
//    REQUIRE(!has_key(all_fruits, L"grapefruit" ));
//
//    const vector<wstring> random_fruits{
//        L"apple", L"apricot", L"banana", L"orange",
// L"grapefruit", L"lemon", L"pear", L"pineapple", L"plum", L"walnut"
//    };
//
//    mt19937 rand_engine{rd()};
//
//    auto const num_distr = uniform_int_distribution<unsigned>(0,
// random_fruits.size() - 1);
//
//    const auto random_fruit{random_fruits[num_distr(rand_engine)]};
//
//    if (all_fruits.find(random_fruit) != cend(all_fruits))
//        REQUIRE(has_key(all_fruits, random_fruit));
//
//    else
//        REQUIRE(!has_key(all_fruits, random_fruit));
//}
//
// TEST_CASE("bool has_key(const unordered_set<ValueType>& container, const
// typename unordered_set<ValueType>::key_type& item)", "Testing global template
// function bool has_key(const unordered_set<ValueType>& container, const
// typename unordered_set<ValueType>::key_type& item)")
//{
//    const wstring src{
//        L"apple:|:banana:|:cabbage:|:lemon:|:orange:|:pepper:|:pineapple:|:plum:|:walnut:|:lemon:|:apricot:|:plum"
//    };
//
//    const wstring needle{L":|:"};
//
//    const auto parts{split(src, needle)};
//
//    const unordered_set<wstring> all_fruits = [&]()
//    {
//        unordered_set<wstring> fruits{};
//
//        for (const auto& fruit : parts)
//        {
//            fruits.insert(fruit);
//        }
//
//        return fruits;
//    }();
//
//    REQUIRE(has_key(all_fruits, wstring{ L"orange" }));
//
//    REQUIRE(!has_key(all_fruits, L"grapefruit" ));
//
//    const vector<wstring> random_fruits{
//        L"apple", L"apricot", L"banana", L"orange",
// L"grapefruit", L"lemon", L"pear", L"pineapple", L"plum", L"walnut"
//    };
//
//    mt19937 rand_engine{rd()};
//
//    auto const num_distr = uniform_int_distribution<unsigned>(0,
// random_fruits.size() - 1);
//
//    const auto random_fruit{random_fruits[num_distr(rand_engine)]};
//
//    if (all_fruits.find(random_fruit) != cend(all_fruits))
//        REQUIRE(has_key(all_fruits, random_fruit));
//
//    else
//        REQUIRE(!has_key(all_fruits, random_fruit));
//}
//
// TEST_CASE("bool has_key(const unordered_multiset<ValueType>& container, const
// typename unordered_multiset<ValueType>::key_type&  item)", "Testing global
// template function bool has_key(const unordered_multiset<ValueType>&
// container, const typename unordered_multiset<ValueType>::key_type& item)"
//)
//{
//    const wstring src{
//        L"apple:|:banana:|:cabbage:|:lemon:|:orange:|:pepper:|:pineapple:|:plum:|:walnut:|:lemon:|:apricot:|:plum"
//    };
//
//    const wstring needle{L":|:"};
//
//    const auto parts{split(src, needle)};
//
//    const unordered_multiset<wstring> all_fruits = [&]()
//    {
//        unordered_multiset<wstring> fruits{};
//
//        for (const auto& fruit : parts)
//        {
//            fruits.insert(fruit);
//        }
//
//        return fruits;
//    }();
//
//    REQUIRE(has_key(all_fruits, L"orange"));
//
//    REQUIRE(!has_key(all_fruits, wstring{ L"grapefruit" }));
//
//    const vector<wstring> random_fruits{
//        L"apple", L"apricot", L"banana", L"orange",
// L"grapefruit", L"lemon", L"pear", L"pineapple", L"plum", L"walnut"
//    };
//
//    mt19937 rand_engine{rd()};
//
//    auto const num_distr = uniform_int_distribution<unsigned>(0,
// random_fruits.size() - 1);
//
//    const auto random_fruit{random_fruits[num_distr(rand_engine)]};
//
//    if (all_fruits.find(random_fruit) != cend(all_fruits))
//        REQUIRE(has_key(all_fruits, random_fruit));
//
//    else
//        REQUIRE(!has_key(all_fruits, random_fruit));
//}
//
// TEST_CASE(
//    "string get_type_name(T&& arg) | wstring get_type_name_w(T&&
// arg) | void show_var_info(const T& arg) | void show_var_info_w(const T& arg)
//||
// bool check_data_types_for_equality(Args&&... args)"
//    ,
//    "Testing global template functions: get_type_name,
// get_type_name_w, show_var_info, show_var_info_w and
// check_data_types_for_equality"
//)
//{
//    const wstring
// src{L"apple:|:banana:|:cabbage:|:lemon:|:orange:|:pepper:|:plum"};
//
//    const wstring needle{L":|:"};
//
//    const auto parts{split(src, needle)};
//
//    cout << '\n' << get_type_name(src) << '\n';
//
//    wcout << get_type_name_w(needle) << L'\n';
//
//    const string info_message{"Hello World!"};
//
//    show_var_info(info_message);
//
//    show_var_info_w(src);
//
//    show_var_info_w(needle);
//
//    cout << "\ncheck_data_types_for_equality(src : wstring, needle :
// wstring) -> " << boolalpha << check_data_types_for_equality(src, needle) <<
//'\n';
//
//    cout << "\ncheck_data_types_for_equality(src : wstring, parts :
// vector<wstring>) -> " << check_data_types_for_equality(src, parts) << '\n';
//}
//
// TEST_CASE("u16string to_u16string(const short value)", "Testing correct
// functionality of global conversion function: u16string to_u16string(const
// short value)")
//{
//    auto const result_u16string{
// to_u16string(static_cast<short>(12345)) };
//
//
//
//    string result_string(cbegin(result_u16string),
// cend(result_u16string));
//
//
//
//    cout << "\nto_u16string(12345) = \"" << result_string << "\"\n";
//
//    REQUIRE(u16string{ u"12345" } == result_u16string);
//
//    const auto float_to_u16string{ to_u16string(7.51735f) };
//
//    REQUIRE(u16string{ u"7.51735" } == float_to_u16string);
//
//    result_string.assign(cbegin(float_to_u16string),
// cend(float_to_u16string));
//
//    cout << "to_u16string(7.51735f) = \"" << result_string <<
//"\"\n";
//
//}
//
// TEST_CASE("u16string to_u16string(const unsigned short value)", "Testing
// correct functionality of global conversion function: u16string
// to_u16string(const unsigned short value)")
//{
//    auto const result_u16string{ to_u16string(static_cast<unsigned
// short>(12345)) };
//
//    const string result_string(cbegin(result_u16string),
// cend(result_u16string));
//
//    cout << "\nto_u16string(12345) = \"" << result_string << "\"\n";
//
//    REQUIRE(u16string{ u"12345" } == result_u16string);
//
//}
//
// TEST_CASE("float stof(const u16string& str, size_t* pos = nullptr, int base =
// 10, bool ignore_leading_white_space_characters = true), u16string
// to_u16string(float value)", "Testing correct functionality of global
// conversion functions: stof, to_u16string")
//{
//    size_t end_pos{};
//    // add code (function) for rounding to N decimal digits
//    auto const float_value { stof(u"7.53", &end_pos, 10) };
//
//    cout << "\nstof(u\"7.53\") = " << float_value << '\n' <<
//"end_pos = " << end_pos << '\n';
//
//    REQUIRE(float_value == 7.53);
//
//    const auto float_to_u16string{ to_u16string(float_value) };
//
//    REQUIRE(float_to_u16string == u"7.53");
//
//
//}

// TEST_CASE("u16string to_u16string(const short value)", "Testing correct
// functionality of global conversion function: u16string to_u16string(const
// short value)")
//{
//  auto const result_u16string{ to_u16string(static_cast<short>(12345)) };
//
//  string result_string(cbegin(result_u16string), cend(result_u16string));
//
//  cout << "\nto_u16string(12345)=\"" << result_string << "\"\n";
//
//  REQUIRE(u16string{ u"12345" } ==
// to_u16string(static_cast<short>(12345)));
//
//  const auto float_to_u16string{ to_u16string(7.51735f) };
//
//  REQUIRE(u16string{ u"7.51735" } == float_to_u16string);
//
//  result_string.assign(cbegin(float_to_u16string),
// cend(float_to_u16string));
//
//  cout << "to_u16string(7.51735f)=\"" << result_string << "\"\n";
//
//
//}
//
// TEST_CASE("u16string to_u16string(const short value)", "Testing correct
// functionality of global conversion function: u16string to_u16string(const
// short value)")
//{
//  auto const result_u16string{ to_u16string(static_cast<short>(12345)) };
//
//  string result_string(cbegin(result_u16string), cend(result_u16string));
//
//  cout << "\nto_u16string(12345)=\"" << result_string << "\"\n";
//
//  REQUIRE(u16string{ u"12345" } ==
// to_u16string(static_cast<short>(12345)));
//
//  const auto float_to_u16string{ to_u16string(7.51735f) };
//
//  REQUIRE(u16string{ u"7.51735" } == float_to_u16string);
//
//  result_string.assign(cbegin(float_to_u16string),
// cend(float_to_u16string));
//
//  cout << "to_u16string(7.51735f)=\"" << result_string << "\"\n";
//
//
//}
//
// TEST_CASE("u16string to_u16string(const short value)", "Testing correct
// functionality of global conversion function: u16string to_u16string(const
// short value)")
//{
//  auto const result_u16string{ to_u16string(static_cast<short>(12345)) };
//
//  string result_string(cbegin(result_u16string), cend(result_u16string));
//
//  cout << "\nto_u16string(12345)=\"" << result_string << "\"\n";
//
//  REQUIRE(u16string{ u"12345" } ==
// to_u16string(static_cast<short>(12345)));
//
//  const auto float_to_u16string{ to_u16string(7.51735f) };
//
//  REQUIRE(u16string{ u"7.51735" } == float_to_u16string);
//
//  result_string.assign(cbegin(float_to_u16string),
// cend(float_to_u16string));
//
//  cout << "to_u16string(7.51735f)=\"" << result_string << "\"\n";
//
//
//}
//
// TEST_CASE("u16string to_u16string(const short value)", "Testing correct
// functionality of global conversion function: u16string to_u16string(const
// short value)")
//{
//  auto const result_u16string{ to_u16string(static_cast<short>(12345)) };
//
//  string result_string(cbegin(result_u16string), cend(result_u16string));
//
//  cout << "\nto_u16string(12345)=\"" << result_string << "\"\n";
//
//  REQUIRE(u16string{ u"12345" } ==
// to_u16string(static_cast<short>(12345)));
//
//  const auto float_to_u16string{ to_u16string(7.51735f) };
//
//  REQUIRE(u16string{ u"7.51735" } == float_to_u16string);
//
//  result_string.assign(cbegin(float_to_u16string),
// cend(float_to_u16string));
//
//  cout << "to_u16string(7.51735f)=\"" << result_string << "\"\n";
//
//
//}
//
// TEST_CASE("u16string to_u16string(const short value)", "Testing correct
// functionality of global conversion function: u16string to_u16string(const
// short value)")
//{
//  auto const result_u16string{ to_u16string(static_cast<short>(12345)) };
//
//  string result_string(cbegin(result_u16string), cend(result_u16string));
//
//  cout << "\nto_u16string(12345)=\"" << result_string << "\"\n";
//
//  REQUIRE(u16string{ u"12345" } ==
// to_u16string(static_cast<short>(12345)));
//
//  const auto float_to_u16string{ to_u16string(7.51735f) };
//
//  REQUIRE(u16string{ u"7.51735" } == float_to_u16string);
//
//  result_string.assign(cbegin(float_to_u16string),
// cend(float_to_u16string));
//
//  cout << "to_u16string(7.51735f)=\"" << result_string << "\"\n";
//
//
//}
//
// TEST_CASE("u16string to_u16string(const short value)", "Testing correct
// functionality of global conversion function: u16string to_u16string(const
// short value)")
//{
//  auto const result_u16string{ to_u16string(static_cast<short>(12345)) };
//
//  string result_string(cbegin(result_u16string), cend(result_u16string));
//
//  cout << "\nto_u16string(12345)=\"" << result_string << "\"\n";
//
//  REQUIRE(u16string{ u"12345" } ==
// to_u16string(static_cast<short>(12345)));
//
//  const auto float_to_u16string{ to_u16string(7.51735f) };
//
//  REQUIRE(u16string{ u"7.51735" } == float_to_u16string);
//
//  result_string.assign(cbegin(float_to_u16string),
// cend(float_to_u16string));
//
//  cout << "to_u16string(7.51735f)=\"" << result_string << "\"\n";
//
//
//}
//
// TEST_CASE("u16string to_u16string(const short value)", "Testing correct
// functionality of global conversion function: u16string to_u16string(const
// short value)")
//{
//  auto const result_u16string{ to_u16string(static_cast<short>(12345)) };
//
//  string result_string(cbegin(result_u16string), cend(result_u16string));
//
//  cout << "\nto_u16string(12345)=\"" << result_string << "\"\n";
//
//  REQUIRE(u16string{ u"12345" } ==
// to_u16string(static_cast<short>(12345)));
//
//  const auto float_to_u16string{ to_u16string(7.51735f) };
//
//  REQUIRE(u16string{ u"7.51735" } == float_to_u16string);
//
//  result_string.assign(cbegin(float_to_u16string),
// cend(float_to_u16string));
//
//  cout << "to_u16string(7.51735f)=\"" << result_string << "\"\n";
//
//
//}
//
// TEST_CASE("u16string to_u16string(const short value)", "Testing correct
// functionality of global conversion function: u16string to_u16string(const
// short value)")
//{
//  auto const result_u16string{ to_u16string(static_cast<short>(12345)) };
//
//  string result_string(cbegin(result_u16string), cend(result_u16string));
//
//  cout << "\nto_u16string(12345)=\"" << result_string << "\"\n";
//
//  REQUIRE(u16string{ u"12345" } ==
// to_u16string(static_cast<short>(12345)));
//
//  const auto float_to_u16string{ to_u16string(7.51735f) };
//
//  REQUIRE(u16string{ u"7.51735" } == float_to_u16string);
//
//  result_string.assign(cbegin(float_to_u16string),
// cend(float_to_u16string));
//
//  cout << "to_u16string(7.51735f)=\"" << result_string << "\"\n";
//
//
//}
//
// TEST_CASE("u16string to_u16string(const short value)", "Testing correct
// functionality of global conversion function: u16string to_u16string(const
// short value)")
//{
//  auto const result_u16string{ to_u16string(static_cast<short>(12345)) };
//
//  string result_string(cbegin(result_u16string), cend(result_u16string));
//
//  cout << "\nto_u16string(12345)=\"" << result_string << "\"\n";
//
//  REQUIRE(u16string{ u"12345" } ==
// to_u16string(static_cast<short>(12345)));
//
//  const auto float_to_u16string{ to_u16string(7.51735f) };
//
//  REQUIRE(u16string{ u"7.51735" } == float_to_u16string);
//
//  result_string.assign(cbegin(float_to_u16string),
// cend(float_to_u16string));
//
//  cout << "to_u16string(7.51735f)=\"" << result_string << "\"\n";
//
//
//}
//
// TEST_CASE("u16string to_u16string(const short value)", "Testing correct
// functionality of global conversion function: u16string to_u16string(const
// short value)")
//{
//  auto const result_u16string{ to_u16string(static_cast<short>(12345)) };
//
//  string result_string(cbegin(result_u16string), cend(result_u16string));
//
//  cout << "\nto_u16string(12345)=\"" << result_string << "\"\n";
//
//  REQUIRE(u16string{ u"12345" } ==
// to_u16string(static_cast<short>(12345)));
//
//  const auto float_to_u16string{ to_u16string(7.51735f) };
//
//  REQUIRE(u16string{ u"7.51735" } == float_to_u16string);
//
//  result_string.assign(cbegin(float_to_u16string),
// cend(float_to_u16string));
//
//  cout << "to_u16string(7.51735f)=\"" << result_string << "\"\n";
//
//
//}
//
// TEST_CASE("u16string to_u16string(const short value)", "Testing correct
// functionality of global conversion function: u16string to_u16string(const
// short value)")
//{
//  auto const result_u16string{ to_u16string(static_cast<short>(12345)) };
//
//  string result_string(cbegin(result_u16string), cend(result_u16string));
//
//  cout << "\nto_u16string(12345)=\"" << result_string << "\"\n";
//
//  REQUIRE(u16string{ u"12345" } ==
// to_u16string(static_cast<short>(12345)));
//
//  const auto float_to_u16string{ to_u16string(7.51735f) };
//
//  REQUIRE(u16string{ u"7.51735" } == float_to_u16string);
//
//  result_string.assign(cbegin(float_to_u16string),
// cend(float_to_u16string));
//
//  cout << "to_u16string(7.51735f)=\"" << result_string << "\"\n";
//
//
//}
//
// TEST_CASE("u16string to_u16string(const short value)", "Testing correct
// functionality of global conversion function: u16string to_u16string(const
// short value)")
//{
//  auto const result_u16string{ to_u16string(static_cast<short>(12345)) };
//
//  string result_string(cbegin(result_u16string), cend(result_u16string));
//
//  cout << "\nto_u16string(12345)=\"" << result_string << "\"\n";
//
//  REQUIRE(u16string{ u"12345" } ==
// to_u16string(static_cast<short>(12345)));
//
//  const auto float_to_u16string{ to_u16string(7.51735f) };
//
//  REQUIRE(u16string{ u"7.51735" } == float_to_u16string);
//
//  result_string.assign(cbegin(float_to_u16string),
// cend(float_to_u16string));
//
//  cout << "to_u16string(7.51735f)=\"" << result_string << "\"\n";
//
//
//}
//
// TEST_CASE("u16string to_u16string(const short value)", "Testing correct
// functionality of global conversion function: u16string to_u16string(const
// short value)")
//{
//  auto const result_u16string{ to_u16string(static_cast<short>(12345)) };
//
//  string result_string(cbegin(result_u16string), cend(result_u16string));
//
//  cout << "\nto_u16string(12345)=\"" << result_string << "\"\n";
//
//  REQUIRE(u16string{ u"12345" } ==
// to_u16string(static_cast<short>(12345)));
//
//  const auto float_to_u16string{ to_u16string(7.51735f) };
//
//  REQUIRE(u16string{ u"7.51735" } == float_to_u16string);
//
//  result_string.assign(cbegin(float_to_u16string),
// cend(float_to_u16string));
//
//  cout << "to_u16string(7.51735f)=\"" << result_string << "\"\n";
//
//
//}
//
// TEST_CASE("u16string to_u16string(const short value)", "Testing correct
// functionality of global conversion function: u16string to_u16string(const
// short value)")
//{
//  auto const result_u16string{ to_u16string(static_cast<short>(12345)) };
//
//  string result_string(cbegin(result_u16string), cend(result_u16string));
//
//  cout << "\nto_u16string(12345)=\"" << result_string << "\"\n";
//
//  REQUIRE(u16string{ u"12345" } ==
// to_u16string(static_cast<short>(12345)));
//
//  const auto float_to_u16string{ to_u16string(7.51735f) };
//
//  REQUIRE(u16string{ u"7.51735" } == float_to_u16string);
//
//  result_string.assign(cbegin(float_to_u16string),
// cend(float_to_u16string));
//
//  cout << "to_u16string(7.51735f)=\"" << result_string << "\"\n";
//
//
//}
//
// TEST_CASE("u16string to_u16string(const short value)", "Testing correct
// functionality of global conversion function: u16string to_u16string(const
// short value)")
//{
//  auto const result_u16string{ to_u16string(static_cast<short>(12345)) };
//
//  string result_string(cbegin(result_u16string), cend(result_u16string));
//
//  cout << "\nto_u16string(12345)=\"" << result_string << "\"\n";
//
//  REQUIRE(u16string{ u"12345" } ==
// to_u16string(static_cast<short>(12345)));
//
//  const auto float_to_u16string{ to_u16string(7.51735f) };
//
//  REQUIRE(u16string{ u"7.51735" } == float_to_u16string);
//
//  result_string.assign(cbegin(float_to_u16string),
// cend(float_to_u16string));
//
//  cout << "to_u16string(7.51735f)=\"" << result_string << "\"\n";
//
//
//}
//
// TEST_CASE("u16string to_u16string(const short value)", "Testing correct
// functionality of global conversion function: u16string to_u16string(const
// short value)")
//{
//  auto const result_u16string{ to_u16string(static_cast<short>(12345)) };
//
//  string result_string(cbegin(result_u16string), cend(result_u16string));
//
//  cout << "\nto_u16string(12345)=\"" << result_string << "\"\n";
//
//  REQUIRE(u16string{ u"12345" } ==
// to_u16string(static_cast<short>(12345)));
//
//  const auto float_to_u16string{ to_u16string(7.51735f) };
//
//  REQUIRE(u16string{ u"7.51735" } == float_to_u16string);
//
//  result_string.assign(cbegin(float_to_u16string),
// cend(float_to_u16string));
//
//  cout << "to_u16string(7.51735f)=\"" << result_string << "\"\n";
//
//
//}
//
// TEST_CASE("u16string to_u16string(const short value)", "Testing correct
// functionality of global conversion function: u16string to_u16string(const
// short value)")
//{
//  auto const result_u16string{ to_u16string(static_cast<short>(12345)) };
//
//  string result_string(cbegin(result_u16string), cend(result_u16string));
//
//  cout << "\nto_u16string(12345)=\"" << result_string << "\"\n";
//
//  REQUIRE(u16string{ u"12345" } ==
// to_u16string(static_cast<short>(12345)));
//
//  const auto float_to_u16string{ to_u16string(7.51735f) };
//
//  REQUIRE(u16string{ u"7.51735" } == float_to_u16string);
//
//  result_string.assign(cbegin(float_to_u16string),
// cend(float_to_u16string));
//
//  cout << "to_u16string(7.51735f)=\"" << result_string << "\"\n";
//
//
//}
//
// TEST_CASE("u16string to_u16string(const short value)", "Testing correct
// functionality of global conversion function: u16string to_u16string(const
// short value)")
//{
//  auto const result_u16string{ to_u16string(static_cast<short>(12345)) };
//
//  string result_string(cbegin(result_u16string), cend(result_u16string));
//
//  cout << "\nto_u16string(12345)=\"" << result_string << "\"\n";
//
//  REQUIRE(u16string{ u"12345" } ==
// to_u16string(static_cast<short>(12345)));
//
//  const auto float_to_u16string{ to_u16string(7.51735f) };
//
//  REQUIRE(u16string{ u"7.51735" } == float_to_u16string);
//
//  result_string.assign(cbegin(float_to_u16string),
// cend(float_to_u16string));
//
//  cout << "to_u16string(7.51735f)=\"" << result_string << "\"\n";
//
//
//}
//
// TEST_CASE("u16string to_u16string(const short value)", "Testing correct
// functionality of global conversion function: u16string to_u16string(const
// short value)")
//{
//  auto const result_u16string{ to_u16string(static_cast<short>(12345)) };
//
//  string result_string(cbegin(result_u16string), cend(result_u16string));
//
//  cout << "\nto_u16string(12345)=\"" << result_string << "\"\n";
//
//  REQUIRE(u16string{ u"12345" } ==
// to_u16string(static_cast<short>(12345)));
//
//  const auto float_to_u16string{ to_u16string(7.51735f) };
//
//  REQUIRE(u16string{ u"7.51735" } == float_to_u16string);
//
//  result_string.assign(cbegin(float_to_u16string),
// cend(float_to_u16string));
//
//  cout << "to_u16string(7.51735f)=\"" << result_string << "\"\n";
//
//
//}
